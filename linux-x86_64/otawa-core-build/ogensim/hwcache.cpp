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
    cache_config_assoc(assoc),
    cacheHitCycles(0),
    cacheMissCycles(3),
    cacheWritethroughCycles(5),
    cacheWritebackCycles(5)
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
    ss << "Cache config: lines=" << cache_config_nlines << " each " << cache_config_linesize
       << "bytes (" << cache_offsetbits << "bits), assoc=" << cache_config_assoc
       << ", sets=" << cache_config_nsets << ", policy=LRU";
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
    cache_entry_t* checked_item = cache_model_sets[set].begin;  ///< begin is the dummy item
    unsigned int size = 0;
    for (int k = 0; k < cache_config_assoc; ++k) {
        if (NULL == checked_item->next) break;
        size++;
        checked_item = checked_item->next;
        fprintf(fp, " [t=0x%x, d=%d]", checked_item->tag, checked_item->dirty);
    }
    fprintf(fp, "\n");
    assert(size == cache_model_sets[set].num_entries);
}

void HWCache::print_stats(void) {
    std::string strstat = get_stats();
    elm::cout << strstat.c_str() << io::endl;
}

/**
 * @brief update given set by loading tag, if not loaded. Possibly evict another one.
 * @param accessed_item pointer to item, in case tag is already in set. Otherwise NULL.
 * @param checked_item the last (=oldest) item in the set that was checked
 * @param prev_item the one previous to last
 **/
inline int HWCache::_update_set_lru
(unsigned set, cache_entry_t* prev_item, cache_entry_t* accessed_item, cache_entry_t* checked_item,
 unsigned tag, bool write)
{
    int cycles = 0;
    if (NULL == accessed_item) {
        // not in cache
        if (cache_model_sets[set].num_entries == cache_config_assoc) {
            // eviction needed: throw out oldest (LRU)
            assert(checked_item);
            assert(NULL == checked_item->next);
            trace("E s=%d, t=0x%x", set, checked_item->tag);
            if (opMode == OPMODE_WRITEBACK && checked_item->dirty) {
                cycles += cacheWritebackCycles;
                stats.num_writeback++;
                trace("WB s=%d, t=0x%x", set, checked_item->tag);
            }
            // take its line
            accessed_item = checked_item;
            assert(prev_item != cache_model_sets[set].begin);
            prev_item->next = NULL; // prev is now the oldest
            stats.num_evict++;
        } else {
            // space left in set: take free line
            cache_model_sets[set].num_entries++;
            accessed_item = cache_model_sets[set].begin + cache_model_sets[set].num_entries;
        }
        accessed_item->tag = tag;
        accessed_item->next = cache_model_sets[set].begin->next; // formerly youngest ages now

    } else {
        // is in cache. just update LRU sorting. accessed
        if (prev_item != cache_model_sets[set].begin) {
            prev_item->next = accessed_item->next;
            accessed_item->next = cache_model_sets[set].begin->next;
        }
    }

    // accessed is the youngest in the set now
    cache_model_sets[set].begin->next = accessed_item;
    assert(accessed_item != accessed_item->next);

    // finally, set bits
    accessed_item->dirty = (write && opMode == OPMODE_WRITEBACK);

    //if (traceFile)
    //    fprint_set(traceFile, set);
    return cycles;
}

inline int HWCache::_access_set
(unsigned int set, unsigned int tag, bool write, bool allow_update)
{
    int cycles = 0;
    assert(set < cache_config_nsets);
    cache_entry_t* checked_item = cache_model_sets[set].begin;  ///< begin is the dummy item

    // linear search for tag in set
    cache_entry_t* prev_item;
    cache_entry_t* found_item = NULL;
    int k;
    for (k = 0; k < cache_config_assoc; ++k) {
        prev_item = checked_item;
        if (NULL == checked_item->next) break;

        checked_item = checked_item->next;
        if (checked_item->tag == tag) {
            found_item = checked_item;
            break;
        }
    }
    assert(k <= cache_model_sets[set].num_entries);

    // hit/miss penalties
    if (found_item) {
        assert(found_item != cache_model_sets[set].begin);
        cycles = cacheHitCycles;
    } else {
        cycles = cacheMissCycles;
        stats.num_miss++;
        trace("M s=%d t=0x%x", set, tag);
    }
    if (write && opMode == OPMODE_WRITETHROUGH) {
        cycles += cacheWritethroughCycles;
    }

    if (allow_update) {
        cycles += _update_set_lru(set, prev_item, found_item, checked_item, tag, write);
    }

    stats.num_access++;
    return cycles;
}

/**
 * @brief read/write item at [addr, addr + len[.
 * @param allow_update if true, accessed item is cached thereafter, otherwise cache is bypassed
 */
int HWCache::_serve_access
(hwcache_addr_t addr, unsigned char len, bool write, bool allow_update)
{
    assert(len <= cache_config_linesize);
    int cycles = 0;
    // compute set & check alignment
    const unsigned block = addr >> cache_offsetbits;
    const unsigned offset = addr - (block << cache_offsetbits);
    const unsigned set = block % cache_config_nsets;
    cycles += _access_set(set, block, write, allow_update);

    const bool unaligned = offset + len > cache_config_linesize;
    trace("%c 0x%x +%d (s=%d)%s", !write ? 'R' : 'W', addr, len, set, unaligned ? " U" : "");

    if (unaligned) {
        // unaligned access
        const unsigned next_block = block + 1;
        const unsigned next_set = next_block % cache_config_nsets;
        cycles += _access_set(next_set, next_block, write, allow_update);
        stats.num_unaligned++;
    }
    return cycles;
}

int HWCache::access(hwcache_addr_t addr, unsigned char len, bool write) {
    int cycles = 0;
    if (opState == OPSTATE_ENABLED || opState == OPSTATE_LOCKED) {
        cycles = _serve_access(addr, len, write, opState != OPSTATE_LOCKED);
    }
    return cycles;
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
