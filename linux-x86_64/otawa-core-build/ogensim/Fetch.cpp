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
 	_currentInstructionToFetch(0),
 	_nextInstructionToFetch(0),
	_fetch_state(READY)
{
	out_fetched_instruction = new sc_out<SimulatedInstruction *>[number_of_out_ports];
	out_ports = number_of_out_ports;
	sim_state = gen_state;
	rename_tables = _rename_tables;
	active_instructions = _active_instructions;
	SC_METHOD(fetch);
	sensitive_pos << in_clock;
}

void FetchStage::fetch() {


	TRACEX(10,
		for(std::vector<std::pair <otawa::Inst *,int* > >::iterator it = vMonitoringFetchedInstructions.begin();
				it != vMonitoringFetchedInstructions.end();
				it++ )
		{
			elm::cout 	<< __SOURCE_INFO__
						<< "[" << (it-vMonitoringFetchedInstructions.begin()) << "]" // the index
						<< "Checking instruction "
						<< it->first << " @ " << (it->first)->address()
						<< " is located at "
						<< *(it->second)
						<< "\n";
		}
	);


	SimulatedInstruction *inst;
	int nb_fetched;
	bool stop = false;

	TRACE(elm::cout << "Fetchstage->fetch():\n";)
	TRACE(elm::cout << "\tin_number_of_accepted_instructions=" << in_number_of_accepted_instructions.read() << "\n";)

	// remove accepted instructions, if there is any
	for (int i = 0 ; i < in_number_of_accepted_instructions.read() ; i++)
	{
		fetched_instructions.removeFirst();
	}

	// now we need to know how many fetched instruction that we have now
	nb_fetched = fetched_instructions.count();


	// if we have fetched than the size of the output queue then dont fetch
	if(nb_fetched >= out_ports) { }

	// reset port request (to memory)
	// we only set this to high for one cycle whenever a new instruction needed
	// to fetch from the memory
	out_request.write(false);


	// now the main body of Fetch stage divided into two parts depending on the its state
	if(_fetch_state == READY)
	{

		if(!_currentInstructionToFetch)
		{
			// this only return the first instruction, does not execute anything
			_currentInstructionToFetch = sim_state->driver->nextInstruction(*sim_state, _currentInstructionToFetch);
		}
		else
		{
			// from the 2nd instruction...
			_currentInstructionToFetch = _nextInstructionToFetch;
		}

		// FUNCTIONAL: now we get the next instruction (by executing the ISS with the current instruction)
		_nextInstructionToFetch = sim_state->driver->nextInstruction(*sim_state, _currentInstructionToFetch);

		// if the next instruction is NULL that means nothing to execute and hence we have to stop the execution
		if(!_nextInstructionToFetch)
		{
			sim_state->stop();
			// waiting for the execution to finish.....
			_fetch_state = WAITING;
		}
		else
		{
			TRACEX(4,
				elm::cout << __SOURCE_INFO__
						<< "_currentInstructionToFetch =  " << _currentInstructionToFetch
						<< " @ " << _currentInstructionToFetch->address()
						<< ", _nextInstructionToFetch = " << _nextInstructionToFetch
						<< " @ " << _nextInstructionToFetch->address()
						<< io::endl;
			)
		}


		// create the SimulatedInstruction for the other stages
		fetchInstruction();

		// TIMING part starts

		// we get the address of the current instruction
		Address addr = _currentInstructionToFetch->address();

		// and then we request this code from the memory
		doInstRequest(addr);

	} // end if(_fetch_state == READY)
	else if(_fetch_state == WAITING)
	{
		// In the WAITING state, the Fetch waits the instruction
		// is received from the Memory, depending on the latency
		// of the memory.
		if(in_wait.read())
		{
			// means still waiting, do nothing......
		}
		else
		{
			// Willie: when instruction is ready, we can fetch the next one
			_fetch_state = READY;
		}
	} // end else if(_fetch_state == WAITING)


	// now we see if we can put the already fetched instruction to the next stage...
	int outs = 0;
	for(elm::genstruct::SLList<SimulatedInstruction *>::Iterator inst(fetched_instructions);
	inst && outs < out_ports;
	inst++)
		out_fetched_instruction[outs++] = inst;
	out_number_of_fetched_instructions.write(outs);
	TRACE(elm::cout << "\tout_number_of_fetched_instructions=" << nb_fetched << "\n";)
}


/**
 * Perform an instruction request to memory.
 * @param addr	Requested address.
 */
void FetchStage::doInstRequest(Address addr) {
    out_address.write(addr);
    out_request.write(true);
	/*_last_line_address = (addr / (out_ports * INST_CODE_SIZE)) * (out_ports
            * INST_CODE_SIZE);*/
    _fetch_state = WAITING;
}


/**
 * Fetch an instruction and add it to the pipeline.
 */
void FetchStage::fetchInstruction(void) {
	int * intInstructionInitialLocation = new int(0);

	TRACEX(2,
		if(_nextInstructionToFetch)
		{
			elm::cout << __SOURCE_INFO__
					<< "Fetching and creating SI with " << _currentInstructionToFetch->address()
					<< " for next address " << _nextInstructionToFetch->address()
					<< " [" << _nextInstructionToFetch << "]" << io::endl;
		}
	)


	_inst = new SimulatedInstruction(_currentInstructionToFetch, _nextInstructionToFetch, active_instructions, intInstructionInitialLocation);
    _inst->renameOperands(rename_tables);
    if(_currentInstructionToFetch->isMem()) {
    	if(_currentInstructionToFetch->isLoad())
    		_inst->setReadMem(MemArea(sim_state->driver->lowerRead(), sim_state->driver->upperRead()));
    	if(_currentInstructionToFetch->isStore())
    		_inst->setWrittenMem(MemArea(sim_state->driver->lowerWrite(), sim_state->driver->upperWrite()));
    }
    // Willie asks:
    // I thought renameOperands will handle the state, so we don't have
    // to set it to WAITING manually, otherwise it might get stuck
    //_inst->setState(gensim::WAITING);
    // HUG: ok!
    fetched_instructions.addLast(_inst);

    // use to track where the instruction is
    _inst->incLocation();

    vMonitoringFetchedInstructions.push_back(std::make_pair(_inst->inst(), intInstructionInitialLocation));
}

} } // otawa::gensim
