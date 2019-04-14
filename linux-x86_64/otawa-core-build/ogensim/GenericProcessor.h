/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS
 *
 * otawa/gensim/GenericProcessor.h -- GenericProcessor class interface
 */
#ifndef OTAWA_GENSIM_GENERIC_PROCESSOR_H
#define OTAWA_GENSIM_GENERIC_PROCESSOR_H

#include <elm/genstruct/SLList.h>
#include <systemc.h>
#include "PipelineStage.h"
#include "Fetch.h"
#include "Execute.h"
#include "SimulatedInstruction.h"
#include "Cache.h"
#include "FunctionalUnit.h"


namespace otawa { namespace gensim {

// External class
class GenericState;
class MemorySystem;

// ProcessirConfiguration class
class ProcessorConfiguration {
	elm::genstruct::SLList<PipelineStageConfiguration *> pipeline_stages;
	elm::genstruct::SLList<InstructionQueueConfiguration *> instruction_queues;
	elm::genstruct::SLList<FunctionalUnitConfiguration *> functional_units;
	public:
		void addPipelineStage(PipelineStageConfiguration * new_stage) {
			pipeline_stages.addLast(new_stage);
		}
		void addInstructionQueue(InstructionQueueConfiguration * new_queue) {
			instruction_queues.addLast(new_queue);
		}
		void addFunctionalUnit(FunctionalUnitConfiguration * new_fu) {
			functional_units.addLast(new_fu);
		}
		elm::genstruct::SLList<InstructionQueueConfiguration *> * instructionQueuesList() {
			return &instruction_queues;
		}
		elm::genstruct::SLList<PipelineStageConfiguration *> * pipelineStagesList() {
			return &pipeline_stages;
		}
		elm::genstruct::SLList<FunctionalUnitConfiguration *> * functionalUnitsList() {
			return &functional_units;
		}

		void dump(elm::io::Output& out_stream);
};

SC_MODULE(GenericProcessor)
{
public:
	bool isEmpty(void);
	void step(void);
	void reset(void);
	void Flush(void);
	bool endOfExecution(void);

  	GenericProcessor(
  		sc_module_name name,
  		ProcessorConfiguration * conf,
  		GenericState * sim_state,
  		otawa::hard::Platform *pf,
  		const hard::Memory *mem,
  		const hard::CacheConfiguration *cache);
  	~GenericProcessor();


	void clearCaches(void);
	void printStats(void) const;

private:

	/************
	 * METHODS
	 ************/
	InstructionQueue * _find_queue(const elm::genstruct::SLList<InstructionQueue*> li,
								   const InstructionQueueConfiguration* iqc) const;

	/************
	 * ATTRS
	 ************/
	// signals
	sc_signal<bool> clock;

	// state
	elm::genstruct::AllocatedTable<rename_table_t> * rename_tables;
	elm::genstruct::SLList<SimulatedInstruction *> active_instructions;

	// structure
	elm::genstruct::SLList<InstructionQueue *> instruction_queues;
	elm::genstruct::SLList<PipelineStage *> pipeline_stages;
	MemorySystem *memory;
};

} } // otawa::gensim

#endif // OTAWA_GENSIM_GENERIC_PROCESSOR_H

