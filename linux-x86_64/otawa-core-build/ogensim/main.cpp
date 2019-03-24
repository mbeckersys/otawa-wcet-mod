/*
 * main.cpp
 *
 *  Created on: 27 nov. 2014
 *      Author: casse
 */
#include <otawa/app/Application.h>
#include <elm/option/ValueOption.h>
#include <elm/option/BoolOption.h>
#include <otawa/hard/Processor.h>
#include <otawa/hard/Memory.h>
#include <otawa/hard/CacheConfiguration.h>
#include <otawa/display/ConfigOutput.h>
#include <otawa/cfg/features.h>
#include "GenericSimulator.h"

#include <stack>

// just for debugging
#include <assert.h>
#include <cstdlib>
#include <cstdio>

using namespace elm;
using namespace otawa;
using namespace gensim;

int debugVerbose = 0;

class Simulator: public otawa::Application, public sim::Driver {
public:
	Simulator(void):
		Application("ogensim", Version(1, 0, 2)),
		proc(option::ValueOption<string>::Make(this).cmd("-p").description("Processor description.")),
		cache(option::ValueOption<string>::Make(this).cmd("-c").description("Cache description.")),
		mem(option::ValueOption<string>::Make(*this).cmd("-m").cmd("--memory").description("memory description for simulation")),
		iVerboseLevel(option::ValueOption<int>::Make(*this).cmd("-vl").cmd("--verboseLevel").description("verbose level for simulation")),
		traceCache(*this, 't', "traceCache", "enable cache protocol", false),
		dumpConfig(*this, 'd', "dumpConfig", "write platform config to HTML file", false),
		process(0),
		current(0),
		start(0),
		exit(0),
		state(0),
		coll(0),
		cfgInfo(0),
		call_pending(false)
		{ }

	virtual Inst *nextInstruction (sim::State &state, Inst *inst) {
		if(inst == NULL) // first instruction
		{
			current = start;
			return start;
		}

		if (current == exit)
		{
			return NULL;
		}

		emit_trace();
		current = this->state->execute(current); // for arm: otawa/src/arm2/arm.cpp
		return current;
	}

	/**
	 * @brief also fails for functions prior to main
	 */
	CFG* _try_find_cfg(Address addr) {
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			cout << "? CFG " << cfg->name() << endl;
			for(CFG::BBIterator bb(cfg); bb; ++bb) {
				for(BasicBlock::InstIterator inst(bb); inst; ++inst) {
					if (inst->address() == addr) {
						return cfg;
					}
				}
			}
		}
		return NULL;
	}

	/**
	 * @brief write cycle, function, offset, and so on to output
	 */
	void emit_trace() {

		if (call_pending) {
			CFG *jj = cfgInfo->findCFG(current); // only finds the first insn/addr of each function
			if (jj) {
				callstack.push(jj);
				// cout << ";; Callstack: " << callstack << io::endl;
				call_pending = false;
			}
		}

		// PRINT elf, addr, cycle ...
		cout << process->program()->name() << " " << current->address() << ": "
			 << sstate->cycle() << ": ";

		// ... function and offset
		CFG* currCFG = (!callstack.empty()) ? callstack.top() : NULL;
		#if 0
		if (!currCFG) {
			CFG*jj = _try_find_cfg(current->address());
		}
		#endif
		if (currCFG) {
			const Address::offset_t off = current->address() - currCFG->address();
			cout << currCFG->name() << "+" << io::hex(off) << "\t";
		} else {
			cout << "??+??\t";
		}

		// ... assembly ...
		cout << current;

		// ... additional comments ...
		if (current->isCall()) {
			cout << "\t;; CALL";
			call_pending = true;

		} else if (current->isReturn()) {
			cout << "\t;; RETURN";
			if (!callstack.empty()) {
				callstack.pop();
			}
		}
		cout << io::endl;
	}

	virtual void terminateInstruction(sim::State &state, Inst *inst) {
	}

	virtual Address lowerRead(void) {
		return this->state->lowerRead();
	}

	virtual Address upperRead(void) {
		return this->state->upperRead();
	}

	virtual Address lowerWrite(void) {
		return this->state->lowerWrite();
	}

	virtual Address upperWrite(void) {
		return this->state->upperWrite();
	}

	virtual void redirect(sim::State &state, Inst *branch, bool direction) {

	}

	virtual bool PredictBranch(sim::State &state, Inst *branch, bool pred) {
		return false;
	}

protected:
	virtual void work(PropList &props) throw (elm::Exception) {
		debugVerbose = iVerboseLevel;

		// "install" the hardware
		if(!*proc)
			throw elm::MessageException("no processor provided");
		otawa::PROCESSOR_PATH(props) = *proc;
		workspace()->require(hard::PROCESSOR_FEATURE, props);
		cout << "Processor from " << otawa::PROCESSOR_PATH(props) << io::endl;
		if(mem) {
			otawa::MEMORY_PATH(props) = *mem;
			workspace()->require(hard::MEMORY_FEATURE, props);
			cout << "Memory from " << otawa::MEMORY_PATH(props) << io::endl;
		}
		if (cache) {
			otawa::CACHE_CONFIG_PATH(props) = *cache;
			workspace()->require(hard::CACHE_CONFIGURATION_FEATURE, props);
			cout << "Cache from " << otawa::CACHE_CONFIG_PATH(props) << io::endl;

		}
		if (traceCache) {
			TRACE_CACHES(workspace()) = true;
		}

		// decode the CFGs and stuff
		workspace()->require(otawa::CFG_INFO_FEATURE, props);
		workspace()->require(otawa::COLLECTED_CFG_FEATURE, props);

		// dump the config, if requested
		if (dumpConfig) {
			cout << "Dumping config..." << endl;
			display::ConfigOutput output;
			output.process(workspace(), props);
		}

		coll = INVOLVED_CFGS(workspace());
		assert(coll);
		assert(coll->get(0));

		// obtain the CFG info
		cfgInfo = CFGInfo::ID(workspace());
		assert(cfgInfo);

		// prepare the functional simulation
		process = workspace()->process();

		// initialize the arm *functional* iss
		// arm.cpp implements newState which create simState (also implemented in arm.cpp)
		state = process->newState();
		if(!state)
			throw MessageException("no functional simulator with the current loader");

		// prepare the *temporal* simulation
		// which creates the systemC modules
		gensim::GenericSimulator gsim;

		// this returns a GenericState, which extends from the sim::State
		sstate = gsim.instantiate(workspace());

		/*************
		 * BEGIN/EXIT
		 *************/
		// start() is implemented in arm.cpp, which returns the start instruction
		// the start instruction is identified when loading the binary file
		start = process->start();
		ASSERT(start);
		Symbol* sym = process->findSymbolAt(start->address());
		if (sym) {
			cout << "Start at " << sym->name() << endl;
		} else {
			Option<Pair<cstring,int> > info = process->getSourceLine(start->address());
			if(info) {
				cstring file = (*info).fst;
				int line = (*info).snd;
				cout << "Start at " << start->address() << " (" << file << ":" << line << ")" << endl;
			} else {
				cout << "Start at " << start->address() << " (no info)" << endl;
			}
		}
		exit = process->findInstAt("_exit");
		if(!exit)
			throw elm::MessageException("no _exit label to stop simulation");
		cout << "Exiting at " << exit << endl;

		//current = process->findInstAt("main");
		// someone can make use of this to decide where the heap starts
		//Inst* aa = process->findInstAt("errno"); // +4
		//cerr << aa->address()+4  << io::endl;

		/********
		 * RUN!
		 ********/
		sstate->run(*this); // defined in GenericState.h
		cerr << "cycles = " << sstate->cycle() << endl;
	}

private:
	SimState *state;
	sim::State *sstate;
	Process *process;
	Inst *start, *current, *exit;
	option::ValueOption<string> proc;
	option::ValueOption<string> cache;
	option::ValueOption<string> mem;
	option::ValueOption<int> iVerboseLevel;
	option::BoolOption traceCache;
	option::BoolOption dumpConfig;
	CFGInfo *cfgInfo;
	std::stack<CFG*> callstack;
	const CFGCollection *coll;
	bool call_pending;
};

OTAWA_RUN(Simulator);
