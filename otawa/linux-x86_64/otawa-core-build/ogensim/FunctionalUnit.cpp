#include <assert.h>
#include "FunctionalUnit.h"

namespace otawa { namespace gensim {

FunctionalUnitConfiguration::FunctionalUnitConfiguration(bool is_pipelined, int latency, int width)
	: _is_pipelined(is_pipelined), _latency(latency), _width(width) {
	if (is_pipelined)
		assert(latency > 1);
}

bool FunctionalUnitConfiguration::isPipelined() {
	return _is_pipelined;
}

int FunctionalUnitConfiguration::latency() {
	return _latency;
}

int FunctionalUnitConfiguration::width() {
	return _width;
}

void FunctionalUnitConfiguration::addInstructionType(Inst::kind_t type) {
	instruction_types.addLast(type);
}

elm::genstruct::SLList<Inst::kind_t> * FunctionalUnitConfiguration::instructionTypes() {
	return &instruction_types;
}

FunctionalUnit::FunctionalUnit(bool is_pipelined, int latency, int width)
	: _is_pipelined(is_pipelined), _latency(latency), _width(width), pending_instructions(0), new_instructions(0) {
}

bool FunctionalUnit::isPipelined() {
	return _is_pipelined;
}

int FunctionalUnit::latency() {
	return _latency;
}

int FunctionalUnit::width() {
	return _width;
}


} } // otawa::gensim
