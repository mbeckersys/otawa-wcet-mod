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

// TODO
//	manage exclusive access to bus
//	recall that data access has priority over instruction stage

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
	dumpDataAccess = false;
	dumpInstAccess = false;
	SC_METHOD(action);
	sensitive_neg << in_clock;
}

/**
 * Process access from the instruction port.
 */
void MemorySystem::processInstPort(void) {
	switch (_inst_cache_state) {

	case READY:
		if(in_inst_request.read() == true) {
			address_t address = in_inst_address.read();
			_inst_fill_latency =  getLatency(address);
			_inst_cache_state = BUSY;
			out_inst_wait.write(true);
		}
		break;

	case BUSY:
		_inst_fill_latency--;
		TRACEX(3, elm::cout << __SOURCE_INFO__ << "tick" << io::endl;)
		if(_inst_fill_latency == 0) {
			TRACEX(3, elm::cout << __SOURCE_INFO__ << "    tack" << io::endl;)
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
			_data_fill_latency = getLatency(address);
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

/**
 * Get the latency of whole access to the memory.
 * @param address	Accessed address.
 * @return			Matching latency.
 */
int MemorySystem::getLatency(Address address) const {
	const hard::Bank *bank = mem->get(address);
	if(!bank)
		throw Exception(_ << "latency : access out of defined banks for address " << address);
	return bank->latency();
}


bool MemorySystem::isCached(Address address) const {
	const hard::Bank *bank = mem->get(address);
	if(!bank)
		throw Exception(_ << "isCached : access out of defined banks for address " << address);
	return bank->isCached();
}

} } // otawa::gensim
