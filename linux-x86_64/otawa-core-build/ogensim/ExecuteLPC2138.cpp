#include "ExecuteLPC2138.h"

//#include <cstdio>
//#include <stdio.h>
//
//

namespace otawa { namespace gensim {


ExecuteStageLPC2138::ExecuteStageLPC2138(sc_module_name name, int width, GenericState * gen_state,
										elm::genstruct::AllocatedTable<rename_table_t> * _rename_tables
										)
		: ExecuteStage(name) {
	stage_width = width;
	sim_state = gen_state;
	rename_tables = _rename_tables;
	in_instruction = new sc_in<SimulatedInstruction *>[width];

	// no instruction running at the beginning
	currentExecutingInstructionCount = 0;
	SC_METHOD(action);
	sensitive << in_clock.pos();
}

void ExecuteStageLPC2138::action() {
	TRACEX(4,
		elm::cout << __SOURCE_INFO__
			<< "[" << __FILE__ << ":" << __LINE__ << "] " << "ExecuteStageLPC2138::action() is called\n";
	)



	SimulatedInstruction* inst;
	int issued = 0;
	TRACE(elm::cout << "ExecuteStage->action()\n";)
	TRACE(elm::cout << "\tin_number_of_ins=" << in_number_of_ins.read() << "\n";)



	// here we control whether a instruction can be fed into this stage or not
	while (
			(issued < in_number_of_ins.read()) // only read the available instructions
			&& (issued < (stage_width - currentExecutingInstructionCount)) // make sure we have enough space to keep the coming instruction
	){
		inst = in_instruction[issued].read() ;
		assert(inst->state() == READY);

		TRACEX(2,
			elm::cout << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Executing instruction at address "
					<< inst->inst()->address() // print out the address of the instruction
					<< " ("
					<< inst->inst() // print out the instruction
					<< ")\n";
		);

		// once the instruction enters the stage, set it to executing
		inst->setState(EXECUTING);

	    // use to track where the instruction is
		inst->incLocation();


		// this is the place to decide how it the instruction is going to take to finish.........
		// refer to the datasheet, e.g. MUL takes cycles depending on the operands
		// TRAVAILLE
		// we set it to to 40 to see what happens

		int cyclesNeeded = 0;
		otawa::Inst* instToExecute = inst->inst();

		// B and BL
		if(instToExecute->isControl())
		{
			// taken or not ?
			if(inst->branchTaken()) { cyclesNeeded = SCycle + 2*NCycle; }         // B/BL taken
			else { cyclesNeeded = SCycle; } // B/BL not taken
		}
		else
		{
			cyclesNeeded = SCycle; // normal ALU
		}



		inst->setTimeToFinish(cyclesNeeded);



		// of course, add it to the queue
		executing_instructions.addLast(inst);
		// move to the next instruction
		issued++;
		// now we have a new instruction comes and gets runnning!
		currentExecutingInstructionCount++;

	} // end of while ( ok && (issued < in_number_of_ins.read()) ){

	// we create a list for terminated instructions
	elm::genstruct::SLList<SimulatedInstruction *> terminated_instructions;

	// now look at each executing instruction
	// this code might not be necessary because we dont have functional units
	// and only one instruction is entered at a time....
	for (elm::genstruct::SLList<SimulatedInstruction *>::Iterator exec(executing_instructions) ; exec ; exec++) {
		// now dec. the number of cycle still needed to complete this instruction
		if (exec->decrementTimeToFinish() == 0) {
			// instruction completes, get it out
			currentExecutingInstructionCount--;
			exec->incLocation();
			terminated_instructions.addLast(exec);
		}
	}

	// now we check the terminated instruction
	while (!terminated_instructions.isEmpty()) {
		// get the first one out
		inst = terminated_instructions.first();

		// update the dependency table of the instructions
		inst->notifyResult(rename_tables);

		// something needs to be done for terminating an instruction ? this is overriden in the main file
		sim_state->driver->terminateInstruction(*sim_state, inst->inst());

		// ok now we can remove this instruction from the executing queue
		executing_instructions.remove(inst);

		// and remove this from the terminated queue
		terminated_instructions.removeFirst();
		TRACE(elm::cout << "\tterminating execution at " << inst->inst()->address() << " \n";)
		delete inst;
	}
	TRACE(elm::cout << "\tout_number_of_accepted_ins=" << in_number_of_ins.read() << "\n";)
	out_number_of_accepted_ins.write(issued);
}

} } // otawa::gensim
