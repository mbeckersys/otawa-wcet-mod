/*
 *	$Id$
 *	Copyright (c) 2006, IRIT-UPS <casse@irit.fr>.
 *
 *	otawa/gensim/SimulatedInstruction.h -- SimulatedInstruction class interface.
 */
#ifndef OTAWA_GENSIM_SIMULATED_INSTRUCTION_H
#define OTAWA_GENSIM_SIMULATED_INSTRUCTION_H

#include <assert.h>
#include <otawa/otawa.h>
#include <otawa/hard/Register.h>
#include <elm/genstruct/Table.h>
#include "debug.h"

namespace otawa { namespace gensim {

typedef enum {NONE, WAITING, READY, EXECUTING, EXECUTED, NOTIFIED} simulated_instruction_state_t; // ordered set

typedef enum {
	COND_BRANCH,
	UNCOND_BRANCH,
	TRAP,
	CALL,
	RETURN,
	LOAD,
	STORE,
	IALU,
	FALU,
	MUL,
	DIV,
	OTHER
} instruction_type_t;
#define INST_TYPE_NUMBER 12
	// FIXME : should be read from framework
instruction_type_t convertInstType(Inst::kind_t kind);

class SimulatedInstruction;

typedef struct rename_table_t {
	otawa::hard::RegBank * reg_bank;
	elm::genstruct::AllocatedTable<SimulatedInstruction *> *table;
} rename_table_t;

class SimulatedInstruction {
public:
	inline SimulatedInstruction(otawa::Inst* inst, /*code_t code, instruction_t* emul_inst,*/
								otawa::Inst* prev_inst,
								elm::genstruct::SLList<SimulatedInstruction *> * _active_instructions,
								int * _intInstructionInitialLocation
								);
	inline ~SimulatedInstruction();
	inline otawa::Inst * inst();
	//inline instruction_t * emulatedInst();
	inline void setState(simulated_instruction_state_t new_state);
	inline simulated_instruction_state_t state();
	inline void incLocation();
	inline int location();
	inline elm::genstruct::SLList<SimulatedInstruction *> * sourceInstructions();
	inline void renameOperands(elm::genstruct::AllocatedTable<rename_table_t> * rename_tables);
	inline void notifyResult(elm::genstruct::AllocatedTable<rename_table_t> * rename_tables);
	inline int timeToFinish();
	inline void setTimeToFinish(int time);
	inline int decrementTimeToFinish();
	inline void dump(elm::io::Output& out_stream);
	inline void dumpState(elm::io::Output& out_stream);
	inline void dumpType(elm::io::Output& out_stream);
	Inst::kind_t type();

	inline void setReadMem(const MemArea& area) { ra = area; }
	inline void setWrittenMem(const MemArea& area) { wa = area; }
	inline const MemArea& readMem(void) const { return ra; }
	inline const MemArea& writtenMem(void) const { return wa; }
	inline bool branchTaken(void);
	inline Address currentAddress(void);
	inline Address nextAddress(void);
	inline bool cacheMiss(void);
	inline void markCacheMiss(void);

private:
	elm::genstruct::SLList<SimulatedInstruction *> * active_instructions;
	otawa::Inst * instruction;
	otawa::Inst * nextInstruction;
	simulated_instruction_state_t instruction_state;
	int * instruction_location;
	bool had_cache_miss;
	elm::genstruct::SLList<SimulatedInstruction *> source_instructions;
	int time_to_finish_execution;
	Inst::kind_t _type;
	MemArea ra, wa;

	inline void addSourceInstruction(SimulatedInstruction * source_inst);
	inline void removeSourceInstruction(SimulatedInstruction * source_inst);

};

inline SimulatedInstruction::SimulatedInstruction(
	otawa::Inst* inst,
	otawa::Inst* next_inst,
	elm::genstruct::SLList<SimulatedInstruction *> * _active_instructions,
	int * _intInstructionInitialLocation = (int*)0
):	active_instructions(_active_instructions),
	instruction(inst),
	nextInstruction(next_inst),
	instruction_state(READY),
	instruction_location(_intInstructionInitialLocation),
	had_cache_miss(false)
{
	active_instructions->addLast(this);
	_type = inst->kind();
}

inline SimulatedInstruction::~SimulatedInstruction() {
	active_instructions->remove(this);
}

inline otawa::Inst * SimulatedInstruction::inst() {
	return instruction;
}

/*inline instruction_t * SimulatedInstruction::emulatedInst() {
	return emulated_inst;
}*/

inline void SimulatedInstruction::setState(simulated_instruction_state_t new_state) {
	instruction_state = new_state;
}

inline simulated_instruction_state_t SimulatedInstruction::state() {
	return instruction_state;
}

inline void SimulatedInstruction::incLocation() {
	(*instruction_location)++;
}

inline int SimulatedInstruction::location() {
	return *instruction_location;
}

inline Inst::kind_t SimulatedInstruction::type() {
	return _type;
}

inline void SimulatedInstruction::addSourceInstruction(SimulatedInstruction * source_inst) {
	source_instructions.addLast(source_inst);
}

inline void SimulatedInstruction::removeSourceInstruction(SimulatedInstruction * source_inst) {
	source_instructions.remove(source_inst);
}

inline elm::genstruct::SLList<SimulatedInstruction *> * SimulatedInstruction::sourceInstructions() {
	return &source_instructions;
}

inline void SimulatedInstruction::renameOperands(elm::genstruct::AllocatedTable<rename_table_t> * rename_tables) {
	//elm::cout << inst() << io::endl;
	const elm::genstruct::Table<otawa::hard::Register *> &reads =
			this->inst()->readRegs();
	for(int i = 0; i < reads.count(); i++) {
		for (int b=0 ; b<rename_tables->count() ; b++) {
			if ((*rename_tables)[b].reg_bank == reads[i]->bank()) {
				SimulatedInstruction * producing_inst = (*rename_tables)[b].table->get(reads[i]->number());
				if (producing_inst != NULL) {
					if (this->sourceInstructions()->contains(producing_inst)) {
						// MBe: does this implicitly push element to end of list?
						this->removeSourceInstruction(producing_inst);
						this->addSourceInstruction(producing_inst);
					}
					this->setState(WAITING);
				}
			}
		}
	}
	const elm::genstruct::Table<otawa::hard::Register *>& writes =
		this->inst()->writtenRegs();
	for(int i = 0; i < writes.count(); i++) {
		for (int b=0 ; b<rename_tables->count() ; b++) {
			if ((*rename_tables)[b].reg_bank == writes[i]->bank()) {
				(*rename_tables)[b].table->set(writes[i]->number(),this);
			}
		}
	}

}

inline void SimulatedInstruction::notifyResult(elm::genstruct::AllocatedTable<rename_table_t> * rename_tables) {
	// for all instructions in flight: remove their dep on this one and set state to READY if finished
	for (elm::genstruct::SLList<SimulatedInstruction *>::Iterator inst(*active_instructions) ; inst ; inst++) {
		if (inst->state() == WAITING) {
			if (inst->sourceInstructions()->contains(this))
				inst->sourceInstructions()->remove(this); // notify that this finished
			if (inst->sourceInstructions()->isEmpty()) {
				inst->setState(READY);
				TRACE(elm::cout << "\t\tinst " << inst->inst()->address() << " is ready now \n");
			}
		}
	}
	this->setState(EXECUTED);
	const elm::genstruct::Table<otawa::hard::Register *>& writes =
		this->inst()->writtenRegs();
	for(int i = 0; i < writes.count(); i++) {
		for (int b=0 ; b<rename_tables->count() ; b++) {
			if ((*rename_tables)[b].reg_bank == writes[i]->bank()) {
				if ((*rename_tables)[b].table->get(writes[i]->number()) == this )
					(*rename_tables)[b].table->set(writes[i]->number(),NULL);
			}
		}
	}

}

inline int SimulatedInstruction::timeToFinish() {
	return time_to_finish_execution;
}

inline void SimulatedInstruction::setTimeToFinish(int time) {
	time_to_finish_execution = time;
}

inline int SimulatedInstruction::decrementTimeToFinish() {
	time_to_finish_execution--;
	TRACEX(2,
	elm::cout
		<< "\ttime to finish executing "
		<< inst() // print out the instruction
		<< " = "
		<< time_to_finish_execution
		<< "\n";
	);
	assert(time_to_finish_execution >= 0);
	return time_to_finish_execution;
}


inline void SimulatedInstruction::dump(elm::io::Output& out_stream) {
	out_stream << inst()->address() << ": " ;
	inst()->dump(out_stream);
	out_stream << " [";
	dumpType(out_stream);
	out_stream << "] - ";
	dumpState(out_stream);
	if (instruction_state == WAITING) {
		out_stream << " - waits for ";
		for (elm::genstruct::SLList<SimulatedInstruction *>::Iterator inst(source_instructions) ; inst ; inst++) {
			out_stream << inst->inst()->address() << ", ";
		}
	}
	out_stream << "\n";
}

inline void SimulatedInstruction::dumpState(elm::io::Output& out_stream) {
	switch(instruction_state) {
		case NONE:
			out_stream << "NONE";
			break;
		case WAITING:
			out_stream << "WAITING";
			break;
		case READY:
			out_stream << "READY";
			break;
		case EXECUTING:
			out_stream << "EXECUTING";
			break;
		case EXECUTED:
			out_stream << "EXECUTED";
			break;
		case NOTIFIED:
			out_stream << "NOTIFIED";
			break;
	}
}

inline void SimulatedInstruction::dumpType(elm::io::Output& out_stream) {
	switch(_type) {
		case COND_BRANCH:
			out_stream << "COND_BRANCH";
			break;
		case UNCOND_BRANCH:
			out_stream << "UNCOND_BRANCH";
			break;
		case TRAP:
			out_stream << "TRAP";
			break;
		case CALL:
			out_stream << "CALL";
			break;
		case RETURN:
			out_stream << "RETURN";
			break;
		case LOAD:
			out_stream << "LOAD";
			break;
		case STORE:
			out_stream << "STORE";
			break;
		case IALU:
			out_stream << "IALU";
			break;
		case FALU:
			out_stream << "FALU";
			break;
		case MUL:
			out_stream << "MUL";
			break;
		case DIV:
			out_stream << "DIV";
			break;
		case OTHER:
			out_stream << "OTHER";
			break;
	}
}

inline void SimulatedInstruction::markCacheMiss(void) {
	had_cache_miss = true;
}

inline bool SimulatedInstruction::cacheMiss(void)
{
	return had_cache_miss;
}

inline bool SimulatedInstruction::branchTaken(void)
{
	if(nextInstruction)
	{
		TRACEX(2,
			elm::cout << __SOURCE_INFO__
					<< "next_adjuscent_inst "
					<< (instruction->address()) << " + " << instruction->size()
					<< " = " << (instruction->address()+instruction->size()) << " vs next_to_run "
					<< nextInstruction->address()
					<< ", taking branch = " << (nextInstruction->address() != (instruction->address()+instruction->size()))
					<< io::endl;
		);

		if(nextInstruction->address() != (instruction->address()+instruction->size()))
		{
			return true;
		}
	}
	return false;
}

inline Address SimulatedInstruction::currentAddress(void) { return instruction->address(); }
inline Address SimulatedInstruction::nextAddress(void) { return nextInstruction->address(); }

} } // otawa::gensim

#endif // OTAWA_GENSIM_SIMULATED_INSTRUCTION_H
