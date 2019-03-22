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
#include <otawa/hard/Memory.h>
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
MemorySystem::MemorySystem(sc_module_name name, GenericState * gen_state, const hard::Memory *memory):
	_inst_cache_state(READY),
	_inst_fill_latency(0),
	_data_cache_state(READY),
	_data_fill_latency(0),
	mem(memory)
{
	sim_state = gen_state;

	_inst_cache = new HWCache(sim_state, "i-cache", 128, 64, 4);  // TODO: from hard::Cache

	dumpDataAccess = false;
	dumpInstAccess = false;
	SC_METHOD(action);
	sensitive_neg << in_clock;
}

void MemorySystem::printStats(void) const {
	if (_inst_cache) {
		std::string stats = _inst_cache->get_stats();
		elm::cout << stats.c_str() << io::endl;
	}
}

MemorySystem::~MemorySystem()
{
	if (_inst_cache) delete _inst_cache;
}

/**
 * Process access from the instruction port.
 * MBe/Comment: instruction fetch latency
 */
void MemorySystem::processInstPort(void) {
	switch (_inst_cache_state) {

	case READY:
		if(in_inst_request.read() == true) {
			address_t address = in_inst_address.read();
			const unsigned size = 4; // FIXME: instruction length
			_inst_fill_latency =  getInstLatency(address, size);
			_inst_cache_state = BUSY;
			out_inst_wait.write(true);
		}
		break;

	case BUSY:
		_inst_fill_latency--;
		TRACEX(3, elm::cout << __SOURCE_INFO__ << "i-stall" << io::endl;)
		if(_inst_fill_latency == 0) {
			TRACEX(3, elm::cout << __SOURCE_INFO__ << "    i-ready" << io::endl;)
			out_inst_wait.write(false);
			_inst_cache_state = READY;
		}
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
			otawa::sim::CacheDriver::action_t type = in_data_access_type.read();
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
	processInstPort();
	processDataPort();
}

void MemorySystem::reset() {
	if (_inst_cache) _inst_cache->Reset();
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
	if (bank->isCached()) {
		lat = _inst_cache->access(address, size, false); // lat defined by cache access
	} else {
		lat = bank->latency(); // this is the default latency. FIXME: size > word width = multiple?
	}
	return lat > 0 ? lat : 1;
}


int MemorySystem::getDataLatency(Address address, size_t size) {
	const hard::Bank *bank = mem->get(address);
	if(!bank)
		throw Exception(_ << "latency : access out of defined banks for address " << address);
	int lat;
	if (bank->isCached()) {
		lat = bank->latency(); // TODO: add d-cache model
	} else {
		lat = bank->latency(); // this is the default latency
	}
	if (lat == 0) lat = 1;
	return lat > 0 ? lat : 1;
}

} } // otawa::gensim
