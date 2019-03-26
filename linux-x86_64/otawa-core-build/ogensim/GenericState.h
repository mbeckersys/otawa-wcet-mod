/*
 *	$Id$
 *	Copyright (c) 2006, IRIT-UPS <casse@irit.fr>.
 *
 *	otawa/gensim/GenericState.h -- GenericState class interface.
 */
#ifndef OTAWA_GENSIM_GENERIC_STATE_H
#define OTAWA_GENSIM_GENERIC_STATE_H

#include "GenericProcessor.h"
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
	int cycle_last_cache_miss;

	// implemented in GenericSimulator.cpp
	void step(void);


public:
	sim::Driver *driver;

	WorkSpace* workspace() { return fw; }

	GenericState(WorkSpace *framework):
	fw(framework), _cycle(0), driver(NULL) {
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

	// --- MBe/hack begin

	virtual void markCacheMiss(void) { ///< call just before terminateInstruction()
		cycle_last_cache_miss = cycle();
	}

	virtual bool terminatingHadCacheMiss(void) { ///< SimDriver can then use this...
		return cycle() == cycle_last_cache_miss;
	}

	// --- MBe/hack end

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
