/*
 *	$Id$
 *	Copyright (c) 2006, IRIT-UPS <rochange@irit.fr>.
 *
 *	GenericSimulator.cpp -- GenericSimulator class implementation.
 */

#include "GenericProcessor.h"
#include "GenericSimulator.h"
#include "GenericState.h"
#include "SimulatedInstruction.h"
#include <otawa/otawa.h>
#include "debug.h"
#include <otawa/hard/Processor.h>
#include <otawa/hard/Platform.h>
#include <otawa/hard/Memory.h>
#include <otawa/hard/CacheConfiguration.h>

int sc_main(int argc, char *argv[]) {
	int err = dup(2);
	close(2);
	sc_core::sc_elab_and_sim(argc, argv);
	dup2(err,2);
	close(err);
	return 0;
}



namespace otawa { namespace gensim {


Identifier<int> DEGREE("otawa::gensim::degree", 1);


/**
 * Instruction execution time. Default to 5.
 */
Identifier<int> INSTRUCTION_TIME("otawa::gensim::instruction_time");


/**
 * @class GenericSimulator
 * The Generic simulator simulates a generic processor.
 */


/**
 * Build an Generic simulator.
 */
GenericSimulator::GenericSimulator(void)
: Simulator("gensim", Version(0, 3, 0), OTAWA_SIMULATOR_VERSION) {
}

/**
 */
sim::State *GenericSimulator::instantiate(WorkSpace *fw, const PropList& props) {
	static GenericState* state;
	static bool initialized = false;
	if(!initialized){
		state = new GenericState(fw);
		state->init();
		initialized = true;
	}
	assert(fw == state->fw);
	return state;
}

void GenericState::init() {
	ProcessorConfiguration conf;

	#if 0
	int degree = DEGREE(fw->process());
	int cache_line_size = 8;

	// config. 3 stages, in-order execution

	InstructionQueueConfiguration *fetch_queue =
		new InstructionQueueConfiguration("FetchQueue", degree + 1, NONE);
	conf.addInstructionQueue(fetch_queue);

	InstructionQueueConfiguration *issue_queue =
		new InstructionQueueConfiguration("IssueQueue", degree + 1, READY);
	conf.addInstructionQueue(issue_queue);

	PipelineStageConfiguration * fetch_stage =
		new PipelineStageConfiguration("FetchStage", FETCH, NULL, fetch_queue, cache_line_size);
	conf.addPipelineStage(fetch_stage);

	PipelineStageConfiguration * decode_stage =
		new PipelineStageConfiguration("DecodeStage", LAZYIQIQ, fetch_queue, issue_queue, degree);
	conf.addPipelineStage(decode_stage);

	PipelineStageConfiguration * execute_stage =
		new PipelineStageConfiguration("ExecuteStage", EXECUTE_IN_ORDER, issue_queue, NULL, degree);
	conf.addPipelineStage(execute_stage);

	// config. 	5 stages, ooo execution

	InstructionQueueConfiguration *fetch_queue =
		new InstructionQueueConfiguration("FetchQueue", degree + 1, NONE);
	conf.addInstructionQueue(fetch_queue);

	InstructionQueueConfiguration * rob =
		new InstructionQueueConfiguration("ROB", degree + 3, EXECUTED);
	conf.addInstructionQueue(rob);

	PipelineStageConfiguration * fetch_stage =
		new PipelineStageConfiguration("FetchStage", FETCH, NULL, fetch_queue, 1 << (degree + 1));
	conf.addPipelineStage(fetch_stage);

	PipelineStageConfiguration * decode_stage =
		new PipelineStageConfiguration("DecodeStage", LAZYIQIQ, fetch_queue, rob, 1 << degree);
	conf.addPipelineStage(decode_stage);

	PipelineStageConfiguration * execute_stage =
		new PipelineStageConfiguration("ExecuteStage", EXECUTE_OUT_OF_ORDER, rob, 1 << degree);
	conf.addPipelineStage(execute_stage);

	PipelineStageConfiguration * commit_stage =
		new PipelineStageConfiguration("CommitStage", COMMIT, rob, NULL, 1 << degree);
	conf.addPipelineStage(commit_stage);

	FunctionalUnitConfiguration * functional_unit =
		new FunctionalUnitConfiguration(true, 5, 1);
	functional_unit->addInstructionType(LOAD);
	functional_unit->addInstructionType(STORE);
	conf.addFunctionalUnit(functional_unit);

	functional_unit =
		new FunctionalUnitConfiguration(false, 1, 2);
	functional_unit->addInstructionType(COND_BRANCH);
	functional_unit->addInstructionType(UNCOND_BRANCH);
	functional_unit->addInstructionType(CALL);
	functional_unit->addInstructionType(RETURN);
	functional_unit->addInstructionType(TRAP);
	functional_unit->addInstructionType(IALU);
	functional_unit->addInstructionType(OTHER);
	conf.addFunctionalUnit(functional_unit);

	functional_unit =
		new FunctionalUnitConfiguration(true, 3, 1);
	functional_unit->addInstructionType(FALU);
	conf.addFunctionalUnit(functional_unit);

	functional_unit =
		new FunctionalUnitConfiguration(true, 6, 1);
	functional_unit->addInstructionType(MUL);
	conf.addFunctionalUnit(functional_unit);

	functional_unit =
		new FunctionalUnitConfiguration(false, 15, 1);
	functional_unit->addInstructionType(DIV);
	conf.addFunctionalUnit(functional_unit);
	#endif // 0

	// Get the processor description
	const hard::Processor *oproc = otawa::hard::PROCESSOR(fw);
	 if(!oproc)
	 	throw LoadException("no processor description available.");

	// Build the queues
	elm::genstruct::Vector<InstructionQueueConfiguration *> queues;
	const elm::genstruct::Table<hard::Queue *>& oqueues = oproc->getQueues();
	for(int i = 0; i< oqueues.count(); i++) {
		/**
		 * !!TODO!! Fix it according last processing stage
		 */
		simulated_instruction_state_t condition = NONE;
		if(oqueues[i]->getOutput()
		&& oqueues[i]->getOutput()->getType() == hard::Stage::EXEC) {
			if(oqueues[i]->getOutput()->isOrdered())
				condition = READY;
			else
				condition = EXECUTED;
		}
		if(oqueues[i]->getIntern())
			condition = EXECUTED;
		InstructionQueueConfiguration *queue =
			new InstructionQueueConfiguration(
				&oqueues[i]->getName(),
				oqueues[i]->getSize(),
				condition);	// Fix it according output stage.
		conf.addInstructionQueue(queue);
		queues.add(queue);
	}

	// Build the stages
	const elm::genstruct::Table<hard::Stage *>& stages = oproc->getStages();
	hard::Stage *exec_stage = 0;
	InstructionQueueConfiguration *prev_queue = 0;
	for(int i = 0; i< stages.count(); i++) {

		// Compute in and out queues
		InstructionQueueConfiguration *inqueue = 0, *outqueue = 0;
		for(int j = 0; j < oqueues.count(); j++) {
			if(oqueues[j]->getInput() == stages[i])
				outqueue = queues[j];
			if(oqueues[j]->getOutput() == stages[i])
				inqueue = queues[j];
			const elm::genstruct::Table<hard::Stage *>& intern = oqueues[j]->getIntern();
			if(intern)
				for(int k = 0; k < intern.count(); k++)
					if(intern[k] == stages[i])
						outqueue = inqueue = queues[j];
		}

		// missing input queue: look for queue from previous stage
		if(i != 0 && !inqueue) {
			std::cout << "creating input: buffer_" << &(stages[i]->getName()) << std::endl;
			if(!prev_queue)
				throw otawa::Exception(_ << "cannot find input queue for " << stages[i]->getName());
			inqueue = prev_queue;
			prev_queue = 0;
		}

		// missing output queue: create a new one
		if(i + 1 != stages.count() && !outqueue) {
			simulated_instruction_state_t condition = NONE;
			if(stages[i]->getType() == hard::Stage::EXEC) {
				if(stages[i]->isOrdered())
					condition = READY;
				else
					condition = EXECUTED;
			}
			std::cout << "creating output: buffer_" << &(stages[i]->getName()) << " width = " << (int)(stages[i]->getWidth()) << std::endl;
			outqueue = new InstructionQueueConfiguration(_ << "buffer_" << stages[i]->getName(), stages[i]->getWidth(), condition);	// Fix it according output stage.
			conf.addInstructionQueue(outqueue);
			queues.add(outqueue);
		}
		prev_queue = outqueue;

		// Compute the type
		pipeline_stage_t type;
		switch(stages[i]->getType()) {
		case hard::Stage::FETCH:
			type = FETCH;
			break;
		case hard::Stage::LAZY:
			type = LAZYIQIQ;
			break;
		case hard::Stage::EXEC:
			if(stages[i]->isOrdered())
				type = EXECUTE_IN_ORDER;
			else
				type = EXECUTE_OUT_OF_ORDER;
			exec_stage = stages[i];
			break;
		case hard::Stage::COMMIT:
			type = COMMIT;
			break;
		default:
			assert(0);
		}

		// Build the stage
		PipelineStageConfiguration *stage;
		stage = new PipelineStageConfiguration(
			&stages[i]->getName(),
			type,
			inqueue,
			outqueue,
			stages[i]->getWidth(),
			0);
		conf.addPipelineStage(stage);
	}

	// Build functional units
	assert(exec_stage);		// !!TODO!! Replace it with an exception throw !
	const elm::genstruct::Table<hard::FunctionalUnit *>& fus = exec_stage->getFUs();
	for(int i = 0; i < fus.count(); i++) {

		// Configure the FU
		FunctionalUnitConfiguration *fu =
			new FunctionalUnitConfiguration(
				fus[i]->isPipelined(),
				fus[i]->getLatency(),
				fus[i]->getWidth());

		// Add supported instructions
		const elm::genstruct::Table<hard::Dispatch *>& dispatch = exec_stage->getDispatch();
		for(int j = 0; j < dispatch.count(); j++)
			if(dispatch[j]->getFU() == fus[i])
				fu->addInstructionType(dispatch[j]->getType());

		// Build the FU
		conf.addFunctionalUnit(fu);
	}

	// Create the processor
	processor = new GenericProcessor("GenericProcessor",&conf, this, fw->platform(),
                                     hard::MEMORY(fw), hard::CACHE_CONFIGURATION(fw));
}


// mmmmmm, this implements the step() from GenericState.h
void GenericState::step(void) {
	TRACE(elm::cout << "Cycle " << _cycle << "\n";)
	processor->step();
	_cycle ++;
	// Willie says: if Fetch fetches a NULL instruction
	// it will set the running to false, we dont have to constantly
	// check if the activeInstruction is empty or not....
	//running = running & (! processor->isEmpty()); // bit-update fashion

}

void GenericState::stop(void)
{
    running = false;
    elm::cerr << "Simulation stopped" << io::endl;
    processor->printStats();
}

GenericState::~GenericState() {
    delete processor;
}

} } // otawa::gensim


/**
 * Plugin hook.
 */
otawa::gensim::GenericSimulator OTAWA_SIMULATOR_HOOK;


/**
 * The entry point to use generic simulators.
 */
otawa::sim::Simulator& gensim_simulator = OTAWA_SIMULATOR_HOOK;


