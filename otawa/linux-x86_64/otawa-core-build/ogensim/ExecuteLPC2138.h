#ifndef OTAWA_GENSIM_EXECUTE_LPC2138_H
#define OTAWA_GENSIM_EXECUTE_LPC2138_H

#include <systemc.h> // for the SystemC interface
#include "PipelineStage.h" // for pipeline stage
#include "SimulatedInstruction.h"
#include "Execute.h"
#include "debug.h"


#include "GenericState.h"

#include <elm/util/Pair.h>
#include <elm/genstruct/Vector.h>

namespace otawa { namespace gensim {


class ExecuteStageLPC2138 : public ExecuteStage {
	// Refer to datasheet DDI 0210C, from page 148
	// The cycle types are in Page 75, section 3.3
	//  nMREQ   SEQ   type   description
	//      0     0      N   Non-sequential cycle
	//      0     1      S   Sequential cycle
	//      1     0      I   Internal cycle
	//      1     1      C   Co-processor cycle
	static const int SCycle = 1;
	static const int NCycle = 1;
	static const int ICycle = 1;
	static const int CCycle = 1;


//	public:
//		// signals
//		// synchronized clock with other modules
//		sc_in<bool> in_clock;
//		// feeds in the instructions
//		sc_in<SimulatedInstruction *> * in_instruction;
//		sc_in<int> in_number_of_ins;
//		sc_out<int> out_number_of_accepted_ins;

	private:
		// variables
		int stage_width;
		int currentExecutingInstructionCount;
		GenericState * sim_state;
		elm::genstruct::AllocatedTable<rename_table_t> * rename_tables;
		//elm::genstruct::AllocatedTable<elm::Pair<unsigned long, FunctionalUnit *> > * fu_bindings;
		elm::genstruct::SLList<SimulatedInstruction *> executing_instructions;

	public:
		ExecuteStageLPC2138(sc_module_name name, int width, GenericState * gen_state,
								elm::genstruct::AllocatedTable<rename_table_t> * _rename_tables
								);
		inline int stageWidth() { return stage_width; }

		SC_HAS_PROCESS(ExecuteStageLPC2138); // put the constructor in it
		void action();

};



} } // otawa::gensim

#endif // OTAWA_GENSIM_EXECUTE_H
