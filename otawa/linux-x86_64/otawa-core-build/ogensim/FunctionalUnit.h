#ifndef OTAWA_GENSIM_FUNCTIONAL_UNIT_H
#define OTAWA_GENSIM_FUNCTIONAL_UNIT_H

#include <elm/genstruct/SLList.h>
#include <otawa/prog/Inst.h>

namespace otawa { namespace gensim {

class FunctionalUnitConfiguration {
	bool _is_pipelined;
	int _latency;
	int _width;
	elm::genstruct::SLList<Inst::kind_t> instruction_types;

	public:
		FunctionalUnitConfiguration(bool is_pipelined, int latency, int width);
		bool isPipelined();
		int latency();
		int width();
		void addInstructionType(Inst::kind_t type);
		elm::genstruct::SLList<Inst::kind_t> * instructionTypes();
};

class FunctionalUnit {
	bool _is_pipelined;
	int _latency;
	int _width;
	int pending_instructions;
	int new_instructions;


	public:
		FunctionalUnit(bool is_pipelined, int latency, int width);
		bool isPipelined();
		int latency();
		int width();
		inline int newInstructions();
		inline int pendingInstructions();
		inline void addInstruction();
		inline void subInstruction();
		inline void resetNewInstructions();
};

inline int FunctionalUnit::newInstructions() {
	return new_instructions;
}

inline int FunctionalUnit::pendingInstructions() {
	return pending_instructions;
}

inline void FunctionalUnit::addInstruction() {
	new_instructions++;
	pending_instructions++;
}


inline void FunctionalUnit::subInstruction() {
	pending_instructions--;
	assert(pending_instructions >= 0);
}

inline void FunctionalUnit::resetNewInstructions() {
	new_instructions = 0;
}

} } // otawa::gensim

#endif // OTAWA_GENSIM_FUNCTIONAL_UNIT_H
