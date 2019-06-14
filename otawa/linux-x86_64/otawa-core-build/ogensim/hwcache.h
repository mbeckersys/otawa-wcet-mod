#ifndef HWCACHE
#define HWCACHE

#include <string>
#include <stdio.h>
#include "GenericState.h"

namespace otawa {

namespace gensim {

typedef unsigned long hwcache_addr_t;

/**
 * @brief abstract cache model copied from HWEeprom.
 * Does *not* track contents, only addresses and states.
 *
 * IRQ: raised when after cache clear request has been processed.
 */
class HWCache {
    public:
        /*************
         * TYPES
         *************/

        //! return info short type
        typedef enum {
          ACCESS_HIT,  ///< exactly one hit
          ACCESS_MISS,  ///< exactly one miss
          ACCESS_OTHER,  ///< something else happened. see access_stats_t.
        } access_type_t;

        //! return information about access
        typedef struct {
          unsigned short hit; ///< number of hits
          unsigned short miss;
          unsigned short writeback;
          unsigned short stall; ///< e.g., on clear. The number of cycles are given by CpuCycles()
          unsigned short ignored;
        } access_info_t;

        //! bits in ctrl register
        enum {
          CTRL_UNINITIALIZED = 0,
          CTRL_ENABLE = 1,  ///< cache enable
          CTRL_LOCK = 2,    ///< lock cache
          CTRL_CLEAR = 4,   ///< cache is cleared if set
          CTRL_IRQ = 8,     ///< interrupt enable
          CTRL_MODE_WRITEBACK = 16,  ///< 0=writethrough
          CTRL_MODE_OTHER = 32,
          CTRL_MODES = 48,
        };

        //! cache operational state machine:
        typedef enum {
          OPSTATE_DISABLED = 0, ///< all misses
          OPSTATE_ENABLED,
          OPSTATE_LOCKED,
          OPSTATE_CLEARING
        } op_state_e;

        //! if enabled, we have the following modes:
        typedef enum {
          OPMODE_WRITEBACK = 0,
          OPMODE_WRITETHROUGH  ///< implies write-allocate
        } op_mode_e;

        typedef struct {
            unsigned long num_access;
            unsigned long num_miss;
            unsigned long num_evict;
            unsigned long num_writeback;
            unsigned long num_unaligned;
            unsigned long num_clears;
        } cache_stats_t;

    protected:
        /*************
         * TYPES
         *************/

        //! one cache item of a set
        typedef struct cache_entry_s {
            unsigned int tag;
            bool dirty;
            cache_entry_s* next; ///< NULL if no older entries than this
        } cache_entry_t;

        /**
         * @brief each set points to a linked list which is contiguous in memory and has
         * length assoc+1, whereas the first element of the list is always present and a DUMMY.
         * Dummy points to the actual list, whereas the items in the list are sorted by their age.
         */
        typedef struct cache_set_s {
            cache_entry_t* begin;  ///< points to NULL-terminated list of
            unsigned int num_entries;
        } cache_set_t;

        /*************
         * ATTRS
         *************/

        // simulation stuff
        GenericState* sim_state;
        std::string cache_name;

        // device state:
        op_state_e opState;  ///< state machine
        op_mode_e opMode;
        int cpuHoldCycles;
        // register
        unsigned char ccr;
        unsigned char ccr_mask;
        // IRQ stuff
        void* irqSystem;

        // user params:
        unsigned int cache_config_nlines;
        unsigned int cache_config_linesize;
        unsigned int cache_config_assoc;
        // model properties:
        int cacheClearTime;  ///< time, not clocks
        // computed:
        unsigned int cache_config_nsets;
        unsigned int cache_config_totalbytes;
        unsigned int cache_offsetbits;
        // data for model:
        cache_entry_t* cache_model_lines;
        cache_set_t* cache_model_sets;

        // for stats
        cache_stats_t stats;

        /*************
         * METHODS
         *************/

        void _init_cache_model(void);
        inline access_type_t _serve_access(access_info_t& ret_info, hwcache_addr_t addr,
                                           unsigned char len, bool write, bool allow_update);
        inline access_type_t _access_set(unsigned set, unsigned tag, bool write, bool allow_update);
        inline access_type_t _update_set_lru(unsigned set, cache_entry_t* prev_item,
                                             cache_entry_t* accessed_item,
                                             cache_entry_t* checked_item,
                                             unsigned tag, bool write);
        inline void _clear_retinfo(access_info_t& ret_info);
        inline void _update_retinfo(access_info_t& ret_info, const access_type_t& ret);
        void _clear_cache(void);
        void _cleanup_cache_model(void);
        void trace(const char *fmt, ...);

    public:

        /*************
         * METHODS
         *************/

        HWCache(GenericState *gen_state,
                const std::string& name,
                unsigned int lines,  ///< total number of cache lines
                unsigned int linesize, ///< bytes in each line (= block size)
                unsigned int assoc,  ///< associativity/ways
                bool trace_on=false);

        virtual ~HWCache();

        //! returns >0 if CPU shall be halted
        unsigned int CpuHoldCycle();

        //! consult ret iff return value is ACCESS_OTHER
        access_type_t access
        (access_info_t& ret_info, hwcache_addr_t addr, unsigned char len, bool write=false);

        std::string get_stats(void);
        void print_stats(void);
        void fprint_stats(FILE* fp);
        void fprint_set(FILE* fp, unsigned set) const;

        void Reset(void); // simulates hardware reset
        void Clear(void); // evict/flush everything

        void SetCcr(unsigned char);
        unsigned char GetCcr() { return ccr; }
        FILE* traceFile;
};

} } // otawa::gensim

#endif
