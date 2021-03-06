/*
 *	$Id$
 *	gensim module interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2007-08, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OTAWA_GENSIM_MEMORY_H
#define OTAWA_GENSIM_MEMORY_H

/* #include "PipelineStage.h" */
/* #include "InstructionQueue.h" */
/* #include "SimulatedInstruction.h" */
#include <otawa/otawa.h>
#include <otawa/hard/Memory.h>
#include <otawa/hard/CacheConfiguration.h>
#include "GenericState.h"
#include "hwcache.h"
#include <otawa/sim/CacheDriver.h>
#include <otawa/sim/AbstractCacheDriver.h>

namespace otawa {

namespace hard { class Memory; }

namespace gensim {

class GenericState;

class MemorySystem : public sc_module {
public:
	/***********
	 * ATTRS
	 ***********/
	sc_in<bool> in_clock;

	// interface to instruction port
	sc_in<address_t> in_inst_address;
	sc_in<bool> in_inst_request;
	sc_out<bool> out_inst_wait;

	// interface to data port
	sc_in<address_t> in_data_address;
	sc_in<otawa::sim::CacheDriver::action_t> in_data_access_type;
	sc_in<int> in_data_size;
	sc_in<bool> in_data_request;
	sc_out<bool> out_data_wait;

	/***********
	 * METHODS
	 ***********/
	MemorySystem(sc_module_name name,
				 GenericState * gen_state,
	             const hard::Memory *mem,
	             const hard::CacheConfiguration *cache);
	~MemorySystem();
	void processInstPort(void);
	void processDataPort(void);

	void printStats(void) const;

	SC_HAS_PROCESS(MemorySystem);
	void action(void);
	void reset(void); // simulate HW reset
	void clear(void); // drop buffers and caches

private:
	/***********
	 * ATTRS
	 ***********/
	GenericState *sim_state;
	typedef enum { READY = 0, BUSY = 1 } memory_state_t;
	const hard::Memory *mem;
	memory_state_t _inst_cache_state;
	memory_state_t _data_cache_state;
	int _inst_fill_latency;
	int _data_fill_latency;
	int _icache_miss_penalty;
	HWCache* _inst_cache;
	HWCache* _data_cache;

	/***********
	 * METHODS
	 ***********/
	int getDataLatency(Address address, size_t size);
	int getInstLatency(Address address, size_t size);

	void _make_caches_icache(const hard::Cache *cconfig, const std::string& name);
	void _make_caches_dcache(const hard::Cache *cconfig, const std::string& name);
	void _make_caches(const hard::CacheConfiguration *caches);
	void _verbose_config(void) const;
};

}
} // otawa::gensim

#endif // OTAWA_GENSIM_FETCH_H
