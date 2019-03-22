#include "hwcache.h"

#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <cmath>
#include <sstream>

#include "otawa/otawa.h"
#include "debug.h"

namespace otawa { namespace gensim {

/**
 * Cache model (LRU):
 *
 * we allocate a continuous chunk of memory for all lines
 * each line has: tag, dirty, valid, next*
 * lines within set are stored as NULL-terminated linked lists, using the next* pointer
 * each cache set is simply the ptr to the head of the list (=newest)
 */

static inline bool powerof_two(int n) {
    return n && !(n & (n - 1));
}

HWCache::HWCache(GenericState *gen_state,
                 const std::string& name,
                 unsigned int lines,
                 unsigned int linesize,
                 unsigned int assoc,
                 bool trace_on):
    sim_state(gen_state),
    cache_name(name),
    opState(OPSTATE_ENABLED),
    opMode(OPMODE_WRITEBACK),
    irqSystem(NULL),
    cache_config_nlines(lines),
    cache_config_linesize(linesize),
    cache_config_assoc(assoc)
{
    if (trace_on) {
        std::string fname = "trace";
        fname += ".cache";
        traceFile = fopen(fname.c_str(), "w");
        elm::cout << "Writing cache trace to " << fname.c_str() << io::endl;
    } else {
        traceFile = NULL;
    }

    if(opMode == OPMODE_WRITETHROUGH) {
        cacheClearTime = 1500000LL; // 1.5ms - just drops data
    } else {
        cacheClearTime = 8500000LL; // 8.5ms - writeback needs to store to backing memory
    }
    if(NULL == irqSystem) {
        ccr_mask = ~CTRL_IRQ;  // ignore IRQ bit if system is not set up
    }
    ccr = CTRL_UNINITIALIZED;
    Reset();
    _init_cache_model();
}

void HWCache::Reset() {
    cpuHoldCycles = 0;

    // by default: cache ON
    ccr = CTRL_ENABLE;
    if (irqSystem)
        ccr |= CTRL_IRQ;
    opState = OPSTATE_ENABLED;
    opMode = OPMODE_WRITEBACK;
}

HWCache::~HWCache() {
    print_stats();
    if (traceFile) {
        fprint_stats(traceFile);
        fclose(traceFile);
    }
    _cleanup_cache_model();
}

void HWCache::_cleanup_cache_model(void) {
    delete [] cache_model_lines;
    delete [] cache_model_sets;
}

void HWCache::_init_cache_model(void) {
    assert(powerof_two(cache_config_linesize));
    assert(powerof_two(cache_config_nlines));
    cache_offsetbits = (int)(log(cache_config_linesize) / log(2.));
    cache_config_nsets = cache_config_nlines / cache_config_assoc;
    cache_config_totalbytes = cache_config_nlines * cache_config_linesize;

    memset((void*)&stats, 0, sizeof(stats));

    // set up contiguous memory chunk to model cache; each set has one additional dummy entry
    cache_model_sets = new cache_set_t[cache_config_nsets];
    cache_model_lines = new cache_entry_t[cache_config_nsets * (cache_config_assoc + 1)];
    cache_entry_t* ce = cache_model_lines;
    for (int k = 0; k < cache_config_nsets; ++k, ce += (cache_config_assoc + 1)) {
        cache_model_sets[k].begin = ce;
    }
    _clear_cache();

    // verbose config
    std::stringstream ss;
    ss << "Cache '" << cache_name << "' config: lines="
       << cache_config_nlines << " each " << cache_config_linesize
       << "bytes (" << cache_offsetbits << "bits), assoc=" << cache_config_assoc
       << ", sets=" << cache_config_nsets
       << ", total=" << cache_config_totalbytes << " bytes"
       << ", policy=LRU";
    const char* msg = ss.str().c_str();
    trace(msg);
    elm::cerr << msg << io::endl;
}

std::string HWCache::get_stats(void)
{
    std::stringstream ss;
    unsigned lines_used = 0;
    for (int set = 0; set < cache_config_nsets; ++set) {
        unsigned ne = cache_model_sets[set].num_entries;
        lines_used += ne;
    }
    ss << cache_name << " statistics:" << std::endl
       << "  usage%:      " << 100.f*(((float)lines_used) / cache_config_nlines) << std::endl
       << "  accesses:    " << stats.num_access << std::endl
       << "  misses/%:    " << stats.num_miss << " / "
                            << 100.f*(((float)stats.num_miss) / stats.num_access) << std::endl
       << "  evictions:   " << stats.num_evict << std::endl
       << "  unaligned/%: " << stats.num_unaligned << " / "
                            << 100.f*(((float)stats.num_unaligned) / stats.num_access) << std::endl
       << "  writeback:   " << stats.num_writeback << std::endl
       << "  clears:      " << stats.num_clears << std::endl;
    return ss.str();
}

void HWCache::fprint_stats(FILE* fp) {
    std::string strstat = get_stats();
    fprintf(fp, "%s\n", strstat.c_str());
}

void HWCache::fprint_set(FILE* fp, unsigned set) const {
    assert(set < cache_config_nsets);
    fprintf(fp, "SET %d:", set);
    cache_entry_t* oldest_item = cache_model_sets[set].begin;  ///< begin is the dummy item
    unsigned int size = 0;
    for (int k = 0; k < cache_config_assoc; ++k) {
        if (NULL == oldest_item->next) break;
        size++;
        oldest_item = oldest_item->next;
        fprintf(fp, " [t=0x%x, d=%d]", oldest_item->tag, oldest_item->dirty);
    }
    fprintf(fp, "\n");
    assert(size == cache_model_sets[set].num_entries);
}

void HWCache::print_stats(void) {
    std::string strstat = get_stats();
    elm::cout << strstat.c_str() << io::endl;
}

void HWCache::_clear_retinfo(access_info_t& ret_info) {
    memset((void*)&ret_info, 0, sizeof(ret_info));
}

void HWCache::_update_retinfo(access_info_t& ret_info, const access_type_t& ret)
{
    if (ACCESS_HIT == ret) {
        ret_info.hit++;
    } else if (ACCESS_MISS == ret) {
        ret_info.miss++;
    } else {
        // internally, anything else means writeback
        ret_info.writeback++;
    }
}

/**
 * @brief update given set by loading tag, if not loaded. Possibly evict another one.
 * @param accessed_item pointer to item, in case tag is already in the set. Otherwise NULL.
 * @param oldest_item the last (=oldest) item in the set that was checked
 * @param prev_item the one previous to last
 **/
inline HWCache::access_type_t HWCache::_update_set_lru
(unsigned set, cache_entry_t* prev_item, cache_entry_t* accessed_item, cache_entry_t* oldest_item,
 unsigned tag, bool write)
{
    access_type_t ret;
    if (NULL == accessed_item) {
        // not in cache. find a spot
        ret = ACCESS_MISS;
        if (cache_model_sets[set].num_entries == cache_config_assoc) {
            // eviction needed: throw out oldest (LRU)
            assert(oldest_item);
            assert(NULL == oldest_item->next); // end of list
            trace("E s=%d, t=0x%x", set, oldest_item->tag);
            if (opMode == OPMODE_WRITEBACK && oldest_item->dirty) {
                stats.num_writeback++;
                ret = ACCESS_OTHER;
                trace("WB s=%d, t=0x%x", set, oldest_item->tag);
            }
            // claim its line
            accessed_item = oldest_item;

            // previously second-to-oldest is now oldest/end of list
            if (cache_config_assoc > 1) {
                assert(prev_item != cache_model_sets[set].begin);
                prev_item->next = NULL;
            }
            stats.num_evict++;
        } else {
            // space left in set: take free line
            cache_model_sets[set].num_entries++;
            accessed_item = cache_model_sets[set].begin + cache_model_sets[set].num_entries;
        }
        // have a line. update the entry
        accessed_item->tag = tag;
    } else {
        // already in cache. just update LRU sorting (connect predecessor and successor)
        ret = ACCESS_HIT;
        if (prev_item != cache_model_sets[set].begin) {
            prev_item->next = accessed_item->next;
        }
    }

    // formerly youngest, if any, ages now
    if (prev_item != cache_model_sets[set].begin) {
        accessed_item->next = cache_model_sets[set].begin->next;
    }

    // accessed is the youngest in the set now
    cache_model_sets[set].begin->next = accessed_item;
    assert(accessed_item != accessed_item->next);

    // finally, set bits
    accessed_item->dirty = (write && opMode == OPMODE_WRITEBACK);

    //if (traceFile)
    //    fprint_set(traceFile, set);
    return ret;
}

inline HWCache::access_type_t HWCache::_access_set
(unsigned set, unsigned tag, bool write, bool allow_update)
{
    access_type_t ret;
    assert(set < cache_config_nsets);
    cache_entry_t* oldest_item = cache_model_sets[set].begin;  ///< begin is the dummy item

    // linear search (ascendingly by age) for tag in the set ...
    cache_entry_t* prev_item;
    cache_entry_t* found_item = NULL;
    int k;
    for (k = 0; k < cache_config_assoc; ++k) {
        prev_item = oldest_item;
        if (NULL == oldest_item->next) break;

        oldest_item = oldest_item->next;
        if (oldest_item->tag == tag) {
            found_item = oldest_item;
            break;
        }
    }
    assert(k <= cache_model_sets[set].num_entries);

    // hit/miss
    if (found_item) {
        ret = ACCESS_HIT;
        assert(found_item != cache_model_sets[set].begin);
    } else {
        ret = ACCESS_MISS;
        stats.num_miss++;
        trace("M s=%d t=0x%x", set, tag);
    }

    if (allow_update) {
        ret = _update_set_lru(set, prev_item, found_item, oldest_item, tag, write);
    }

    stats.num_access++;
    return ret;
}

/**
 * @brief read/write item at [addr, addr + len[.
 * @param allow_update if true, accessed item is cached thereafter, otherwise cache is bypassed
 */
HWCache::access_type_t
HWCache::_serve_access
(access_info_t& ret_info, hwcache_addr_t addr, unsigned char len, bool write, bool allow_update)
{
    assert(len <= cache_config_linesize);
    access_type_t ret1;
    // compute set & check alignment
    const unsigned block = addr >> cache_offsetbits;
    const unsigned offset = addr - (block << cache_offsetbits);
    const unsigned set = block % cache_config_nsets;
    ret1 = _access_set(set, block, write, allow_update);
    if (ret1 == ACCESS_OTHER) {
        _clear_retinfo(ret_info);
        _update_retinfo(ret_info, ret1);
    }

    const bool unaligned = offset + len > cache_config_linesize;
    trace("%c 0x%x +%d (s=%d)%s", !write ? 'R' : 'W', addr, len, set, unaligned ? " U" : "");

    if (unaligned) {
        // unaligned access - another access is required
        const unsigned next_block = block + 1;
        const unsigned next_set = next_block % cache_config_nsets;
        access_type_t ret2 = _access_set(next_set, next_block, write, allow_update);
        // exended return value
        if (ret1 != ACCESS_OTHER) {
            _clear_retinfo(ret_info);
            _update_retinfo(ret_info, ret1);
            ret1 = ACCESS_OTHER; // because its the return value of this function
        }
        _update_retinfo(ret_info, ret2);
        stats.num_unaligned++;
    }
    return ret1;
}

HWCache::access_type_t HWCache::access
(access_info_t& ret_info, hwcache_addr_t addr, unsigned char len, bool write)
{
    if (opState == OPSTATE_ENABLED || opState == OPSTATE_LOCKED) {
        return _serve_access(ret_info, addr, len, write, opState != OPSTATE_LOCKED);
    } else {
        _clear_retinfo(ret_info);
        ret_info.ignored = 1;
        return ACCESS_OTHER;
    }
}

void HWCache::_clear_cache(void) {
    for (int k = 0; k < cache_config_nsets; ++k) {
        cache_model_sets[k].num_entries = 0;
    }
    // each set has one leading dummy entry
    const unsigned nbytes = sizeof(cache_entry_t) * cache_config_nsets * (cache_config_assoc + 1);
    memset((void*)cache_model_lines, 0, nbytes);
    stats.num_clears++;
}

void HWCache::SetCcr(unsigned char newval) {
    trace("CCR=0x%x", newval);

    ccr = newval & ccr_mask;

    switch(opState) {

        case OPSTATE_LOCKED:
        case OPSTATE_ENABLED:
            if ((ccr & CTRL_ENABLE) != CTRL_ENABLE) {
                cpuHoldCycles = 1;
                opState = OPSTATE_DISABLED;
                trace("DISABLE");
                break;
            }

            if ((ccr & CTRL_CLEAR) == CTRL_CLEAR) {
                cpuHoldCycles = 4;
                // start timer ...
                //SystemClockOffset t = cacheClearTime;
                //clearDoneTime = SystemClock::Instance().GetCurrentTime() + t;
                opState = OPSTATE_CLEARING;
                _clear_cache();
                ccr &= ~CTRL_CLEAR;  // immediately revoke bit
                trace("CL start");
                break; // to ignore any other requests
            }

            if ((ccr & CTRL_LOCK) == CTRL_LOCK) {
                // lock request
                if (opState == OPSTATE_ENABLED) {
                    cpuHoldCycles = 1;
                    opState = OPSTATE_LOCKED;
                    trace("LOCK");
                }
            } else {
                // unlock request
                if (opState == OPSTATE_LOCKED) {
                    cpuHoldCycles = 1;
                    // abort enable state, switch to write state
                    opState = OPSTATE_ENABLED;
                    trace("UNLOCK");
                }
            }
            break;

        case OPSTATE_DISABLED:
            if (ccr & CTRL_ENABLE == CTRL_ENABLE) {
                cpuHoldCycles = 1;
                opState = OPSTATE_ENABLED;
                trace("ENABLE");
            }
            break;

        default:
            if (ccr & CTRL_MODE_WRITEBACK == CTRL_MODE_WRITEBACK) {
                if (opMode != OPMODE_WRITEBACK) {
                    opMode = OPMODE_WRITEBACK;
                    trace("MODE=WB");
                }
            } else {
                if (opMode != OPMODE_WRITETHROUGH) {
                    opMode = OPMODE_WRITETHROUGH;
                    trace("MODE=WT");
                }
            }
            break;
    }
}

unsigned int HWCache::CpuHoldCycle() {

    // handle clear state
    if(opState == OPSTATE_CLEARING) {
        //if(SystemClock::Instance().GetCurrentTime() >= clearDoneTime) {
        if (true) { // TODO: cache clear time
            // go back to ready state
            opState = OPSTATE_ENABLED;
            // process operation
            trace("CL done");
            // now raise irq if enabled and available
            if((NULL != irqSystem) && ((ccr & CTRL_IRQ) == CTRL_IRQ)) {
                //irqSystem->SetIrqFlag(this, irqVectorNo);
            }
        }
    }

    // deactivate engine, if not used
    //if((opState == OPSTATE_READY) && (cpuHoldCycles == 0) && (opEnableCycles == 0))
    //    core->RemoveFromCycleList(this);

    // handle cpu hold state
    if(cpuHoldCycles > 0) {
        cpuHoldCycles--;
        return 1;
    } else
        return 0;

}

void HWCache::trace(const char *fmt, ...) {
    if (!traceFile)
        return;

    fprintf(traceFile, "%ld: ", sim_state->cycle());
    va_list args;
    va_start(args,fmt);
    vfprintf(traceFile, fmt, args);
    va_end(args);
    fprintf(traceFile, "\n");
}

} } // otawa::gensim
