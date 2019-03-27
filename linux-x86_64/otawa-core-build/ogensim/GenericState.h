/*
 *	$Id$
 *	Copyright (c) 2006, IRIT-UPS <casse@irit.fr>.
 *
 *	otawa/gensim/GenericState.h -- GenericState class interface.
 */
#ifndef OTAWA_GENSIM_GENERIC_STATE_H
#define OTAWA_GENSIM_GENERIC_STATE_H

#include "GenericProcessor.h"
#include "SimulatedInstruction.h"
#include <otawa/sim/Simulator.h>
#include <otawa/sim/State.h>
#include <otawa/otawa.h>
#include <debug.h>

namespace otawa { namespace gensim {

// Configuration
extern Identifier<int> INSTRUCTION_TIME;


class GenericState: public sim::State {
	friend class GenericSimulator;
	WorkSpace *fw;
	int _cycle;
	GenericProcessor* processor;
	bool running;
	SimulatedInstruction* _terminating_inst;

	// implemented in GenericSimulator.cpp
	void step(void);


public:
	sim::Driver *driver;

	WorkSpace* workspace() { return fw; }

	GenericState(WorkSpace *framework):
	fw(framework), _cycle(0), _terminating_inst(NULL), driver(NULL) {
	}

	GenericState(const GenericState& state):
	fw(state.fw), _cycle(state._cycle), driver(NULL) {
	}

	~GenericState();

	void init();

	// State overload
	virtual State *clone(void) {
		return new GenericState(*this);
	}

	virtual void run(sim::Driver& driver) {
		this->driver = &driver;
		running = true;
		while(running)
		{
			TRACEX(1, elm::cerr << "----------------" << io::endl;);
			step();
			TRACEX(1, elm::cerr << "cycle = " << cycle() << io::endl;);
		}
	}

	virtual void setTerminatingInstruction(SimulatedInstruction* inst) {
		_terminating_inst = inst;
	}

	virtual SimulatedInstruction* getTerminatingInstruction(void) const {
		return _terminating_inst;
	}

	virtual void stop(void);

	virtual void flush(void) {
	}

	virtual int cycle(void) {
		return _cycle;
	}

	virtual void reset(void) {
		_cycle = 0;
	}

	virtual Process *process(void) {
		ASSERTP(false, "should not have been called");
		return 0;
	}

};

} } // otawa::gensim


#endif // OTAWA_GENSIM_GENERIC_STATE_H
