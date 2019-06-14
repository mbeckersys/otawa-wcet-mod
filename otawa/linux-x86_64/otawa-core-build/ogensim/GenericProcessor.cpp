#include "GenericProcessor.h"
#include "ExecuteLPC2138.h"
#include "Memory.h"
#include "debug.h"
#include <otawa/hard/Platform.h>
#include <iostream>

namespace otawa { namespace gensim {

void ProcessorConfiguration::dump(elm::io::Output& out_stream) {
	out_stream << "---- Processor configuration ----\n";
	out_stream << " Instruction queues:\n";
	for (elm::genstruct::SLList<InstructionQueueConfiguration *>::Iterator iqc(instruction_queues) ; iqc ; iqc++) {
		iqc->dump(out_stream);
	}
	out_stream << " Pipeline stages:\n";
	for (elm::genstruct::SLList<PipelineStageConfiguration *>::Iterator psc(pipeline_stages) ; psc ; psc++) {
		psc->dump(out_stream);
	}
	out_stream << "---- end of configuration ----\n";

}

InstructionQueue*
GenericProcessor::_find_queue(const elm::genstruct::SLList<InstructionQueue *> li,
const InstructionQueueConfiguration* iqc) const
{
	assert(iqc);
	InstructionQueue* q = NULL;
	for (elm::genstruct::SLList<InstructionQueue *>::Iterator iq(li); iq ; iq++) {
		if (iq->configuration() == iqc) {
			q = iq;
			break;
		}
	}
	return q;
}

GenericProcessor::GenericProcessor(
	sc_module_name name,
	ProcessorConfiguration * conf,
	GenericState * sim_state, otawa::hard::Platform *pf,
	const hard::Memory *mem,
    const hard::CacheConfiguration *cache
):	memory(0) {

	int iports,oports;
	InstructionQueue * input_queue;
	InstructionQueue * output_queue;
	sc_signal<int> * nb;

	/************************
	 * memory
	 ************************/
	memory = new MemorySystem("memory", sim_state,
                              mem ? mem : &pf->memory(),
                              cache ? cache : &pf->cache());
	memory->in_clock(clock);

	// interface to data port
	sc_signal<address_t> * in_data_address_sc = new sc_signal<address_t>;
	memory->in_data_address(*in_data_address_sc);
	sc_signal<otawa::sim::CacheDriver::action_t> * in_data_access_type_sc = new sc_signal<otawa::sim::CacheDriver::action_t>;
	memory->in_data_access_type(*in_data_access_type_sc);
	sc_signal<int> * in_data_size_sc = new sc_signal<int>;
	memory->in_data_size(*in_data_size_sc);
	sc_signal<bool> * in_data_request_sc = new sc_signal<bool>;
	memory->in_data_request(*in_data_request_sc);
	sc_signal<bool> * out_data_wait_sc = new sc_signal<bool>;
	memory->out_data_wait(*out_data_wait_sc);

	/************************
	 * rename tables
	 ************************/
	rename_tables = new elm::genstruct::AllocatedTable<rename_table_t>(pf->banks().count());
	int reg_bank_count = pf->banks().count();
	for(int i = 0; i <reg_bank_count ; i++) {
		(*rename_tables)[i].reg_bank = (otawa::hard::RegBank *) pf->banks()[i];
		(*rename_tables)[i].table =
			new elm::genstruct::AllocatedTable<SimulatedInstruction *>((*rename_tables)[i].reg_bank->count());
		for (int j=0 ; j<(*rename_tables)[i].reg_bank->count() ; j++)
			(*rename_tables)[i].table->set(j,NULL);
	}

	/************************
	 * queues between stages
	 ************************/
	std::cout << "================ Creating queues =============" << std::endl;
	for (elm::genstruct::SLList<InstructionQueueConfiguration *>::Iterator queue_conf(*(conf->instructionQueuesList())) ;
			queue_conf ; queue_conf++) {
		std::cout << "INFO: queue " << &(queue_conf->name()) << " ..." << std::endl;
		InstructionQueue * new_queue = new InstructionQueue((sc_module_name) (queue_conf->name().toCString()), *queue_conf);
		instruction_queues.addLast(new_queue);
		new_queue->in_clock(clock);
	}

	for (elm::genstruct::SLList<PipelineStageConfiguration *>::Iterator stage_conf(*(conf->pipelineStagesList())) ;
			stage_conf ; stage_conf++)
	{
		std::cout << "================ Stage " <<  *(stage_conf->name()) << " =====================" << std::endl;
		switch(stage_conf->type()) {
			case FETCH:	{
				output_queue = _find_queue(instruction_queues, stage_conf->outputQueue());
				assert(output_queue);
				std::cout << "INFO: output queue: "
						  << &(output_queue->configuration()->nameOfTheQueue()) << std::endl;
				oports = output_queue->configuration()->numberOfWritePorts();

				FetchStage * fetch_stage = new FetchStage((sc_module_name) (stage_conf->name()),
															oports, sim_state, rename_tables, &active_instructions);
				pipeline_stages.addLast(fetch_stage);
				fetch_stage->in_clock(clock);

				// binding between the queue and the stage
				for (int i=0 ; i<oports ; i++) {
					sc_signal<SimulatedInstruction *> * fetched_instruction = new sc_signal<SimulatedInstruction *>;
					fetch_stage->out_fetched_instruction[i](*fetched_instruction);
					output_queue->in_instruction[i](*fetched_instruction);
				}
				nb = new sc_signal<int>;
				nb->write(0);
				fetch_stage->out_number_of_fetched_instructions(*nb);
				output_queue->in_number_of_ins(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				fetch_stage->in_number_of_accepted_instructions(*nb);
				output_queue->out_number_of_accepted_ins(*nb);

				// interface with memory
				sc_signal<address_t> * addr = new sc_signal<address_t>;
				fetch_stage->out_address(*addr);
				memory->in_inst_address(*addr);
				sc_signal<bool> * req  = new sc_signal<bool>;
				fetch_stage->out_request(*req);
				memory->in_inst_request(*req);
				req->write(0);
				sc_signal<bool> *wait = new sc_signal<bool>;
				fetch_stage->in_wait(*wait);
				memory->out_inst_wait(*wait);
			} break;

			case LAZYIQIQ: {
				input_queue = _find_queue(instruction_queues, stage_conf->inputQueue());
				assert(input_queue);
				std::cout << "INFO: input queue: "
						  << &(input_queue->configuration()->nameOfTheQueue()) << std::endl;
				iports = input_queue->configuration()->numberOfReadPorts();
				output_queue = _find_queue(instruction_queues, stage_conf->outputQueue());
				assert(output_queue);
				std::cout << "INFO: output queue: "
						  << &(output_queue->configuration()->nameOfTheQueue()) << std::endl;
				oports = output_queue->configuration()->numberOfWritePorts();

				LazyStageIQIQ * lazy_stage = new LazyStageIQIQ((sc_module_name) (stage_conf->name()), stage_conf->width());
				pipeline_stages.addLast(lazy_stage);

				lazy_stage->in_clock(clock);

				for (int i=0 ; i<iports ; i++) {
					sc_signal<SimulatedInstruction *> * instruction = new sc_signal<SimulatedInstruction *>;
					lazy_stage->in_instruction[i](*instruction);
					input_queue->out_instruction[i](*instruction);
				}

				for (int i=0 ; i<oports ; i++) {
					sc_signal<SimulatedInstruction *> * instruction = new sc_signal<SimulatedInstruction *>;
					lazy_stage->out_instruction[i](*instruction);
					output_queue->in_instruction[i](*instruction);
				}
				nb = new sc_signal<int>;
				nb->write(0);
				lazy_stage->in_number_of_ins(*nb);
				input_queue->out_number_of_outs(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				lazy_stage->out_number_of_accepted_ins(*nb);
				input_queue->in_number_of_accepted_outs(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				lazy_stage->out_number_of_outs(*nb);
				output_queue->in_number_of_ins(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				lazy_stage->in_number_of_accepted_outs(*nb);
				output_queue->out_number_of_accepted_ins(*nb);
			} break;

			case EXECUTE_IN_ORDER: {
				input_queue = _find_queue(instruction_queues, stage_conf->inputQueue());
				assert(input_queue);
				std::cout << "INFO: input queue: "
						  << &(input_queue->configuration()->nameOfTheQueue()) << std::endl;
				iports = input_queue->configuration()->numberOfReadPorts();

				ExecuteStage * execute_stage;

				if((stage_conf->name()).compare("EX_LPC2138") == 0)
				{
					std::cout << "INFO: using LPC2138 execution stage" << std::endl << std::flush;
					execute_stage = new ExecuteStageLPC2138((sc_module_name) (stage_conf->name()), iports, sim_state,
																rename_tables);
				}
				else
				{
					std::cout << "INFO: using generic in-order execution" << std::endl << std::flush;
					execute_stage = new ExecuteInOrderStageIQ((sc_module_name) (stage_conf->name()), iports, sim_state,
											rename_tables, conf->functionalUnitsList());
				}
				pipeline_stages.addLast(execute_stage);
				execute_stage->in_clock(clock);


				for (int i=0 ; i<iports ; i++) {
					sc_signal<SimulatedInstruction *> * instruction = new sc_signal<SimulatedInstruction *>;
					execute_stage->in_instruction[i](*instruction);
					input_queue->out_instruction[i](*instruction);
				}

				// ================== the extra wiring
				output_queue = _find_queue(instruction_queues, stage_conf->outputQueue());
				assert(output_queue);
				std::cout << "INFO: output queue: "
						  << &(output_queue->configuration()->nameOfTheQueue()) << std::endl;
				oports = output_queue->configuration()->numberOfWritePorts();

				for (int i=0 ; i<oports ; i++) {
					sc_signal<SimulatedInstruction *> * instruction = new sc_signal<SimulatedInstruction *>;
					//execute_stage->out_instruction[i](*instruction);
					output_queue->in_instruction[i](*instruction);
				}

				nb = new sc_signal<int>;
				nb->write(0);
				output_queue->in_number_of_ins(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				output_queue->out_number_of_accepted_ins(*nb);
				// ==========================================================

				nb = new sc_signal<int>;
				nb->write(0);
				execute_stage->in_number_of_ins(*nb);
				input_queue->out_number_of_outs(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				execute_stage->out_number_of_accepted_ins(*nb);
				input_queue->in_number_of_accepted_outs(*nb);
			} break;

			case EXECUTE_OUT_OF_ORDER: {
				InstructionQueue * rob;
#if 1
				rob = _find_queue(instruction_queues, stage_conf->instructionBuffer());
				assert(rob);
				std::cout << "INFO: input queue: "
						  << &(rob->configuration()->nameOfTheQueue()) << std::endl;

#else
				found = false;
				for (elm::genstruct::SLList<InstructionQueue *>::Iterator iq(instruction_queues) ; iq ; iq++) {
					if (iq->configuration() == stage_conf->instructionBuffer()) {
						rob = iq;
						found = true;
					}
				}
				assert(found);
#endif

				ExecuteOOOStage * execute_stage =
					new ExecuteOOOStage((sc_module_name) (stage_conf->name()), (stage_conf->width()), rob,
										rename_tables, conf->functionalUnitsList());
				pipeline_stages.addLast(execute_stage);
				execute_stage->in_clock(clock);
			} break;

			case COMMIT: {
				input_queue = _find_queue(instruction_queues, stage_conf->inputQueue());
				assert(input_queue);
				std::cout << "INFO: input queue: "
						  << &(input_queue->configuration()->nameOfTheQueue()) << std::endl;
				iports = input_queue->configuration()->numberOfReadPorts();
				CommitStage * commit_stage =
					new CommitStage((sc_module_name) (stage_conf->name()), iports, sim_state);
				pipeline_stages.addLast(commit_stage);
				commit_stage->in_clock(clock);

				for (int i=0 ; i<iports ; i++) {
					sc_signal<SimulatedInstruction *> * instruction = new sc_signal<SimulatedInstruction *>;
					commit_stage->in_instruction[i](*instruction);
					input_queue->out_instruction[i](*instruction);
				}
				nb = new sc_signal<int>;
				nb->write(0);
				commit_stage->in_number_of_ins(*nb);
				input_queue->out_number_of_outs(*nb);
				nb = new sc_signal<int>;
				nb->write(0);
				commit_stage->out_number_of_accepted_ins(*nb);
				input_queue->in_number_of_accepted_outs(*nb);
			} break;


			default:
				break;
		}
	}
	std::cout << "==============================================" << std::endl;
	clock.write(0);
}

GenericProcessor::~GenericProcessor() {
	delete memory;
}

bool GenericProcessor::isEmpty() {
	return (active_instructions.count() == 0);
}

void GenericProcessor::printStats(void) const {
    memory->printStats();
}

void GenericProcessor::clearCaches(void) {
	memory->clear();
}

void GenericProcessor::step() {
	TRACE(elm::cout << "----- GenericProcessor->Step() : rising edge \n";)
	clock.write(1);
	sc_start(0.5, sc_core::SC_US);
	TRACE(elm::cout << "----- GenericProcessor->Step() : falling edge \n";)
	clock.write(0);
	sc_start(0.5, sc_core::SC_US);
}

void GenericProcessor::reset() {
    memory->reset();
    // TODO: clear pipeline
}

void GenericProcessor::Flush() {
	for(int i = 0; i <rename_tables->count() ; i++) {
		for (int j=0 ; j<(*rename_tables)[i].reg_bank->count() ; j++)
			(*rename_tables)[i].table->set(j,NULL);
	}

}

bool GenericProcessor::endOfExecution() {
	return isEmpty();
}

} } // otawa::gensim
