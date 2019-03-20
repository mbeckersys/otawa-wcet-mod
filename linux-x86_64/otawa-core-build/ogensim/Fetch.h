/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS
 *
 * otawa/gensim/Fetch.h -- FetchStage class interface
 */
#ifndef OTAWA_GENSIM_FETCH_H
#define OTAWA_GENSIM_FETCH_H

#include "PipelineStage.h"
#include "InstructionQueue.h"
#include "SimulatedInstruction.h"
//#include <emul.h>
//#include <iss_include.h>
#include <otawa/otawa.h>
#include <vector>
#include <utility> // for pair


namespace otawa { namespace gensim {

// External class
class GenericState;

#define NB_INT_REGS 32
#define NB_FP_REGS 32
	// FIXME: should be learned from gliss

class FetchStage : public PipelineStage {
public:
	// interface to next stage
	sc_in<bool> in_clock;
	sc_out<SimulatedInstruction *> * out_fetched_instruction;
	sc_out<int> out_number_of_fetched_instructions;
	sc_in<int>in_number_of_accepted_instructions;

	// interface to instruction port
	sc_out<address_t> out_address;
	sc_out<bool> out_request;
	sc_in<bool> in_wait;

	FetchStage(sc_module_name name, int number_of_out_ports, GenericState *gen_state,
			elm::genstruct::AllocatedTable<rename_table_t> *rename_tables,
			elm::genstruct::SLList<SimulatedInstruction *> *_active_instructions);

	SC_HAS_PROCESS(FetchStage);
	void fetch();


private:

	std::vector<std::pair <otawa::Inst *,int* > > vMonitoringFetchedInstructions;

	// parameters
	GenericState *sim_state;
	int out_ports;
	elm::genstruct::SLList<SimulatedInstruction *> fetched_instructions;
	elm::genstruct::SLList<SimulatedInstruction *> *active_instructions;

	// state
	otawa::Inst* _nextInstructionToFetch;
	otawa::Inst* _currentInstructionToFetch;

    SimulatedInstruction* _inst;
	//bool *_ended;
	elm::genstruct::AllocatedTable<rename_table_t> *rename_tables;
    typedef enum {
        READY = 0,
        WAITING = 1,
        BRANCH_PEN = 2
    } fetch_state_t;
    fetch_state_t _fetch_state;

	// tool function
	void doInstRequest(Address addr);
	void fetchInstruction(void);
};

} } // otawa::gensim

#endif // OTAWA_GENSIM_FETCH_H
