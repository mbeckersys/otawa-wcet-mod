/*
 *	$Id$
 *	exegraph module implementation
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

#include "Memory.h"
#include "GenericState.h"
#include "GenericSimulator.h"
#include <elm/string/String.h>
#include <otawa/sim/CacheDriver.h>

namespace otawa { namespace gensim {

// TODOs:
//	manage exclusive access to bus
//	recall that data access has priority over instruction stage
//	replace cache class by SystemC component (Cache.cpp)

/**
 * Constructor.
 */
MemorySystem::MemorySystem(sc_module_name name, GenericState *gen_state,
	const hard::Memory *memory,
	const hard::CacheConfiguration *caches):
	mem(memory),
	_inst_cache_state(READY),
	_data_cache_state(READY),
	_inst_fill_latency(0),
	_data_fill_latency(0),
	_inst_cache(NULL),
	_data_cache(NULL)
{
	sim_state = gen_state;

	_verbose_config();
	_make_caches(caches);

	SC_METHOD(action);
	sensitive_neg << in_clock;
}

void MemorySystem::_verbose_config(void) const {
	elm::cout << "Memory:" << io::endl;
	const Table<const otawa::hard::Bank*> & banks = mem->banks();
	for(Table<const otawa::hard::Bank*>::Iterator it(banks); it; ++it) {
		elm::cout << " - bank '" << it->name() << "': "
				  << "size=" << it->size() << " B, "
				  << "latency=" << it->latency() << ", "
				  << "cached=" << it->isCached()
				  << io::endl;
	}
}

void MemorySystem::_make_caches_icache(const hard::Cache *cc, const std::string& name) {
	assert(!cc->nextLevel() && "no support for multi-level cache");
	const hard::Cache::replace_policy_t pol = cc->replacementPolicy();
	_icache_miss_penalty = cc->missPenalty();

	assert(pol == hard::Cache::LRU && "only supporting LRU");
	assert(cc->setCount() == cc->blockCount() / cc->wayCount());
	const bool do_trace = TRACE_CACHES(sim_state->workspace());
	const unsigned total_size = cc->cacheSize();
	assert(total_size == cc->blockCount() * cc->blockSize());
	_inst_cache = new HWCache(sim_state, name,
								cc->blockCount(),
								cc->blockSize(),
								cc->wayCount(),
								do_trace);
}

void MemorySystem::_make_caches_dcache(const hard::Cache *cconfig, const std::string& name) {
	assert(false && "Not implemented");
}

void MemorySystem::_make_caches(const hard::CacheConfiguration *caches) {
	if (caches->hasInstCache() && caches->hasDataCache()) {
		assert(!caches->isUnified() && "No support for unified L1 cache");
	}

	if (caches->hasInstCache()) {
		const otawa::hard::Cache* icc = caches->instCache();
		const std::string cname = caches->cacheName(icc).chars();
		_make_caches_icache(icc, cname);
	} else {
		TRACEX(0, elm::cout << "No instruction cache specified" << io::endl;)
	}

	if (caches->hasDataCache()) {
		const otawa::hard::Cache* dcc = caches->dataCache();
		const std::string cname = caches->cacheName(dcc).chars();
		_make_caches_dcache(dcc, cname);
	} else {
		TRACEX(0, elm::cout << "No data cache specified" << io::endl;)
	}
}

void MemorySystem::printStats(void) const {
	if (_inst_cache) {
		std::string stats = _inst_cache->get_stats();
		elm::cout << stats.c_str() << io::endl;
	}
	if (_data_cache) {
		std::string stats = _data_cache->get_stats();
		elm::cout << stats.c_str() << io::endl;
	}
}

MemorySystem::~MemorySystem()
{
	if (_inst_cache) delete _inst_cache;
	if (_data_cache) delete _data_cache;
}

/**
 * Process access from the instruction port.
 * MBe/Comment: instruction fetch latency
 */
void MemorySystem::processInstPort(void) {
	switch (_inst_cache_state) {

	// evaluate state
	case READY:
		if(in_inst_request.read() == true) {
			address_t address = in_inst_address.read();
			TRACE10(elm::cout << "\trequest for " << address << io::endl;)
			const unsigned size = 4; // FIXME: read instruction length from somewhere
			_inst_fill_latency = getInstLatency(address, size);
			if (_inst_fill_latency > 0) {
				_inst_cache_state = BUSY;
				TRACE10(elm::cout << "\twait" << address << io::endl;) // basically only when cache hit
			} else {
				TRACE10(elm::cout << "\tpresent" << io::endl;)
			}
		}
		break;

	case BUSY:
		_inst_fill_latency--;
		if(_inst_fill_latency <= 0) {
			_inst_cache_state = READY;
			TRACE10(elm::cout << "\tREADY again" << io::endl;)
		} else {
			TRACE10(elm::cout << "\twait" << io::endl;)
		}
		break;
	}

	// handle state (signalling to fetch stage)
	switch (_inst_cache_state) {
	case READY:
		out_inst_wait.write(false);
		break;
	default:
		out_inst_wait.write(true);
		break;
	}
}


/**
 * Process access from the data port.
 */
void MemorySystem::processDataPort(void) {
	switch (_data_cache_state) {

	case READY:
		if(in_data_request.read() == true) {
			address_t address = in_data_address.read();
			int size = in_data_size.read();
			//otawa::sim::CacheDriver::action_t type = in_data_access_type.read();
			_data_fill_latency = getDataLatency(address, size);
			_data_cache_state = BUSY;
			out_data_wait.write(true);
		}
		break;

	case BUSY:
		_data_fill_latency--;
		if(_data_fill_latency == 0) {
			out_data_wait.write(false);
			_data_cache_state = READY;
		}
		break;
	}
}


/**
 */
void MemorySystem::action() {
	TRACE10(elm::cout << "Memory->action():" << io::endl;)
	processInstPort();
	processDataPort();
}

void MemorySystem::reset() {
	if (_inst_cache) _inst_cache->Reset();
	if (_data_cache) _data_cache->Reset();
}

/**
 * Get the latency of whole access to the memory.
 * @param address	Accessed address.
 * @return			Matching latency.
 */
int MemorySystem::getInstLatency(Address address, size_t size) {
	const hard::Bank *bank = mem->get(address);
	if(!bank)
		throw Exception(_ << "latency : access out of defined banks for address " << address);
	int lat;
	if (bank->isCached() && _inst_cache) {
		HWCache::access_info_t rinfo;
		HWCache::access_type_t ret = _inst_cache->access(rinfo, address, size, false);
		switch (ret) {
			case HWCache::ACCESS_HIT:
				lat = 0;
				break;
			case HWCache::ACCESS_MISS:
				lat = bank->latency();
				if (lat != _icache_miss_penalty) {
					elm::cerr << "Bank latency (" << lat
								<< ") and i-cache miss penalty ("
								<< _icache_miss_penalty << ") disagree. Taking max." << io::endl;
					lat = lat > _icache_miss_penalty ? lat : _icache_miss_penalty;
				}
				break;
			default:
				// unaligned, etc.
				assert(false && "unexpected access for an i-cache");
				break;
			}
	} else {
		lat = bank->latency(); // this is the default latency. FIXME: size > word width => multiple?
	}
	return lat;
}


int MemorySystem::getDataLatency(Address address, size_t size) {
	const hard::Bank *bank = mem->get(address);
	if(!bank)
		throw Exception(_ << "latency : access out of defined banks for address " << address);
	int lat;
	if (bank->isCached() && _data_cache) {
		lat = bank->latency(); // TODO: add d-cache model
	} else {
		lat = bank->latency(); // this is the default latency
	}
	return lat;
}

} } // otawa::gensim
