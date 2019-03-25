#include "Fetch.h"
#include "GenericState.h"
#include "debug.h"


namespace otawa { namespace gensim {

FetchStage::FetchStage(
	sc_module_name name,
	int number_of_out_ports,
	GenericState * gen_state,
	elm::genstruct::AllocatedTable<rename_table_t> * _rename_tables,
	elm::genstruct::SLList<SimulatedInstruction *> * _active_instructions)
:	PipelineStage(name),
	_nextInstructionToFetch(0),
	_currentInstructionToFetch(0),
	_fetch_state(READY)
{
	out_fetched_instruction = new sc_out<SimulatedInstruction *>[number_of_out_ports];
	out_ports = number_of_out_ports;
	sim_state = gen_state;
	rename_tables = _rename_tables;
	active_instructions = _active_instructions;
	SC_METHOD(action);
	sensitive_pos << in_clock;
}

/**
 * @brief this actually triggers the functional execution (although it should go in the execute
 * stage), because we need to know the successor instruction to be fetched
 */
void FetchStage::action()
{
	TRACE10(elm::cout << "Fetch->action(): \n";)

#ifdef DEBUG_TRACK_INSN
	TRACEX(10,
		for(std::vector<std::pair <otawa::Inst *,int* > >::iterator it = vMonitoringFetchedInstructions.begin();
				it != vMonitoringFetchedInstructions.end();
				it++ )
		{
			elm::cout << "\t[" << (it-vMonitoringFetchedInstructions.begin()) << "]" // the index
						<< "Checking instruction "
						<< it->first << " @ " << (it->first)->address()
						<< " is located at "
						<< *(it->second)
						<< "\n";
		}
	);
#endif

	/*********************************
	 * manage out queue of prev cycle
	 *********************************/
	// remove any instructions that have been accepted by decode queue
	for (int i = 0; i < in_number_of_accepted_instructions.read(); i++) {
		fetchBuffer.removeFirst();
	}

	// we only set this to high for one cycle whenever a new instruction needed
	// to fetch from the memory
	out_request.write(false);

	/***************
	 * decide state
	 ***************/
	if (_fetch_state == WAITING)
	{
		// In the WAITING state, the Fetch waits the instruction
		// is received from the Memory, depending on the latency
		// of the memory.
		if(in_wait.read()) {
			// means still waiting for mem, do nothing......
			TRACE10(elm::cout << "\tstall" << io::endl;)
		} else {
			_fetch_state = READY;
			TRACE10(elm::cout << "\tREADY again" << io::endl;)

			// create the SimulatedInstruction for the other stages
			_makeSimulatedInstruction(_currentInstructionToFetch, _nextInstructionToFetch);
		}
	} else // TODO: removing this "else" requires to save _currentInsn and _nextInsn before we overwrite

	if (_fetch_state == READY)
	{
		const int nbuffered = fetchBuffer.count();
		if (true || nbuffered < 2*out_ports) {
			if(!_currentInstructionToFetch) {
				// the very first instruction does not execute anything...skip ahead
				_currentInstructionToFetch = sim_state->driver->nextInstruction(*sim_state, _currentInstructionToFetch);
			} else {
				// the one we executed before has given us the next one. TODO: so we have no branch penalty or anything.
				_currentInstructionToFetch = _nextInstructionToFetch;
			}

			// FUNCTIONAL: now we get the next instruction (by executing the ISS with the current instruction)
			_nextInstructionToFetch = sim_state->driver->nextInstruction(*sim_state, _currentInstructionToFetch);

			if(!_nextInstructionToFetch) {
				sim_state->stop();
				_fetch_state = END;
			} else {
				TRACEX(4,
					elm::cout
							<< "\t_currentInstructionToFetch= [" << _currentInstructionToFetch
							<< "] @" << _currentInstructionToFetch->address()
							<< ", _nextInstructionToFetch=[" << _nextInstructionToFetch
							<< "] @" << _nextInstructionToFetch->address()
							<< io::endl;
				)
			}

			// start to simulate memory access for fetch
			_doInstRequest(_currentInstructionToFetch->address());
			_fetch_state = WAITING;

		} else {
			TRACE10(elm::cout << "\tnot fetching (enough in buffer)" << io::endl;)
		}
	}

	/******************
	 * write out queue
	 ******************/
	int outs = 0;
	for(elm::genstruct::SLList<SimulatedInstruction *>::Iterator inst(fetchBuffer);
		inst && outs < out_ports;
		inst++)
	{
		out_fetched_instruction[outs++] = inst;
	}
	out_number_of_fetched_instructions.write(outs);
	TRACE10(elm::cout << "\tnumber_of_outs=" << outs << "\n";)
}


/**
 * Perform an instruction request to memory.
 * @param addr	Requested address.
 */
void FetchStage::_doInstRequest(Address addr) {
	out_address.write(addr);
	out_request.write(true);
}


/**
 * Fetch an instruction and add it to the pipeline.
 */
void FetchStage::_makeSimulatedInstruction(otawa::Inst*this_insn, otawa::Inst*next_insn) {
	int * intInstructionInitialLocation = new int(0);

	_inst = new SimulatedInstruction(this_insn, next_insn,
										active_instructions, intInstructionInitialLocation);
	_inst->renameOperands(rename_tables);
	if(this_insn->isMem()) {
		if(this_insn->isLoad()) {
			_inst->setReadMem(MemArea(sim_state->driver->lowerRead(),
										sim_state->driver->upperRead()));
		}
		if(this_insn->isStore()) {
			_inst->setWrittenMem(MemArea(sim_state->driver->lowerWrite(),
											sim_state->driver->upperWrite()));
		}
	}
	fetchBuffer.addLast(_inst);

#ifdef DEBUG_TRACK_INSN
	_inst->incLocation();
	vMonitoringFetchedInstructions.push_back(std::make_pair(_inst->inst(), intInstructionInitialLocation));
#endif
}

} } // otawa::gensim
