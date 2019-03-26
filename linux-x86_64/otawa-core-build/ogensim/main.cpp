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
#include <otawa/ipet/IPET.h>
#include <otawa/display/ConfigOutput.h>
#include <otawa/cfgio/Output.h>
#include <otawa/proc/DynProcessor.h>
#include <otawa/cfg/features.h>
#include <otawa/prop/PropList.h>
#include <elm/io/OutFileStream.h>
#include "GenericSimulator.h"
#include "GenericState.h"


#include <stack>
#include <set>

// just for debugging
#include <assert.h>
#include <cstdlib>
#include <cstdio>

using namespace elm;
using namespace otawa;
using namespace gensim;

int debugVerbose = 0;

class SimContext {
public:
	SimContext() : _call_pending(false), _endofbb_pending(false),
					begin_of_func(false), end_of_func(false),
					curr_bb(NULL), pre_bb(NULL), returned_cfg(NULL) {}

	/*********
	 * TYPES
	 *********/
	struct callstack_item_s {
		CFG* cfg;
		int  time_called;
		callstack_item_s(CFG* c, int t) : cfg(c), time_called(t) {}
	};
	typedef struct callstack_item_s callstack_item;

	/*********
	 * ATTRS
	 *********/
	std::stack<callstack_item> callstack;

	// rather not for user
	bool _call_pending;
	bool _endofbb_pending;

	// for user
	bool begin_of_func;
	bool end_of_func;
	bool begin_of_bb;  ///< implies end of previous BB
	otawa::BasicBlock* curr_bb;
	otawa::BasicBlock* pre_bb;

	int time_bb_enter;
	int time_fun_enter;

	// filled when end_of_func==true
	CFG* returned_cfg;
	int  duration_returned_cfg;
};

class Simulator: public otawa::Application, public sim::Driver {
public:
	Simulator(void):
		Application("ogensim", Version(1, 0, 2)),
		state(0),
		process(0),
		start(0),
		current(0),
		exit(0),
		proc(option::ValueOption<string>::Make(this).cmd("-p").description("Processor description.")),
		cache(option::ValueOption<string>::Make(this).cmd("-c").description("Cache description.")),
		mem(option::ValueOption<string>::Make(*this).cmd("-m").cmd("--memory").description("memory description for simulation")),
		events(option::ValueOption<string>::Make(*this).cmd("-e").cmd("--event").description("which event to trace: 2^{f,d,e,c}")),
		iVerboseLevel(option::ValueOption<int>::Make(*this).cmd("-vl").cmd("--verboseLevel").description("verbose level for simulation")),
		dumpCfg(option::ValueOption<string>::Make(*this).cmd("-o").cmd("--dumpCfg").description("output annotated CFGs to given file")),
		traceCache(*this, 't', "traceCache", "enable cache protocol", false),
		dumpConfig(*this, 'd', "dumpConfig", "write platform config to HTML file", false),
		inlineCalls(*this, 'i', "inlineCalls", "Inline the function calls when dumping CFG (not affecting simulation).", false),
		cfgInfo(0),
		coll(0),
		ev_fetch(false), ev_decode(false), ev_exec(false), ev_commit(false)
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

		track_context(ctx_fetch, inst);
		if (ev_fetch) emit_trace(ctx_fetch, inst, "F");

		current = this->state->execute(current); // for arm: otawa/src/arm2/arm.cpp
		return current;
	}

	/**
	 * @brief write back some stats to the CFG
	 */
	void annotate_cfg(SimContext& ctx, Inst *inst, bool cache_miss=false) {
		if (!ctx.callstack.empty()) {
			SimContext::callstack_item cit = ctx.callstack.top();
			if (ctx.begin_of_func) {
				otawa::ipet::COUNT(cit.cfg) += 1;
			}
			if (ctx.end_of_func) {
				// elm::cout << "Function '" << ctx.returned_cfg->name() << "' returned after "
				//	 << ctx.duration_returned_cfg << " cycles " << io::endl;
				if (ctx.duration_returned_cfg > otawa::ipet::WCET(ctx.returned_cfg)) {
					otawa::ipet::WCET(ctx.returned_cfg) = ctx.duration_returned_cfg;
				}
				otawa::ipet::TOTAL_TIME(ctx.returned_cfg) += ctx.duration_returned_cfg;
			}
		}
		if (ctx.begin_of_bb) {
			if (ctx.curr_bb) {
				otawa::ipet::COUNT(ctx.curr_bb) += 1;
			}
			const int now = sstate->cycle();
			if (ctx.pre_bb) {
				const int duration = now - ctx.time_bb_enter;
				//elm::cout << "Annotating BB " << ctx.pre_bb->address() << ", dur=" << duration << io::endl;
				// time is cumulative incl. all cache and pipeline effects
				//elm::cout << "check before: PROP=" << otawa::ipet::TOTAL_TIME(ctx.pre_bb) << io::endl;
				otawa::ipet::TOTAL_TIME(ctx.pre_bb) += duration;
				//elm::cout << "check after: PROP=" << otawa::ipet::TOTAL_TIME(ctx.pre_bb) << io::endl;
				if (duration > otawa::ipet::WCET(ctx.pre_bb)) {
					otawa::ipet::WCET(ctx.pre_bb) = duration;
				}
			}
			ctx.time_bb_enter = now;
		}
		if (cache_miss && ctx.curr_bb) {
			otawa::ipet::ICACHE_MISSES(ctx.curr_bb) += 1;
		}
	}

	/**
	 * @brief called whenever an instruction is committed
	 */
	virtual void terminateInstruction(sim::State &state, Inst *inst) {
		// FIXME: remove this cache miss hack. find a better way to pass it back from Execute
		bool cache_miss;
		if (GenericState* gs = dynamic_cast<GenericState*>(&state)) {
			cache_miss = gs->terminatingHadCacheMiss();
		} else {
			cache_miss = false;
		}
		track_context(ctx_commit, inst);
		if (ev_commit) emit_trace(ctx_commit, inst, "C");
		if (dumpCfg) annotate_cfg(ctx_commit, inst, cache_miss);
	}

	inline otawa::BasicBlock* find_next_bb(otawa::BasicBlock* curr_bb, otawa::Inst* next_inst) const {
		if (curr_bb) {
			otawa::BasicBlock*bb = curr_bb->getTaken();
			if (bb && bb->firstInst() == next_inst) return bb;
		}
		if (curr_bb){
			otawa::BasicBlock*bb = curr_bb->getNotTaken();
			if (bb && bb->firstInst() == next_inst) return bb;
		}
		// still here? then maybe OTAWA is confused or we have >2 targets?
		// scan all BBs in all CFGs
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			for(CFG::BBIterator bb(cfg); bb; ++bb) {
				if (bb->firstInst() == next_inst) {
					return bb;
				}
			}
		}
		return NULL;
	}

	/**
	 * @brief keep track of currently running function and so on
	 */
	void track_context(SimContext& ctx, otawa::Inst*curr) const {
		// new function begins. use callstack.
		ctx.begin_of_func = ctx._call_pending;
		if (ctx._call_pending) {
			ctx._call_pending = false;
			CFG *jj = cfgInfo->findCFG(curr); // only finds the first insn/addr of each function
			if (jj) {
				SimContext::callstack_item cit(jj, sstate->cycle());
				ctx.callstack.push(cit);
			}
		}
		// new BB begins. find it. Don't rely on callstack.
		ctx.begin_of_bb = ctx._endofbb_pending;
		if (ctx._endofbb_pending) {
			ctx._endofbb_pending = false;
			otawa::BasicBlock* next_bb = find_next_bb(ctx.pre_bb, curr);  // FIXME: why pre???
			ctx.pre_bb = ctx.curr_bb;
			ctx.curr_bb = next_bb;
		}
		// search for upcoming end of BB and func return
		if (curr->isCall()) {
			ctx._call_pending = true;
		}
		if (curr->isReturn()) {
			if (!ctx.callstack.empty()) {
				SimContext::callstack_item cit = ctx.callstack.top();
				ctx.callstack.pop();

				const int duration = sstate->cycle() - cit.time_called;
				ctx.end_of_func = true;
				ctx.returned_cfg = cit.cfg;
				ctx.duration_returned_cfg = duration;
			}
		} else {
			ctx.end_of_func = false;
		}
		if (ctx.curr_bb) {
			ctx._endofbb_pending = ctx.curr_bb->lastInst() == curr;
		} else {
			ctx._endofbb_pending = true; // next insn is scanned for BB...until we have one
		}
	}

	/**
	 * @brief initialize all CFG annotations
	 */
	void predecorate_cfgs(void) {
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			otawa::ipet::TOTAL_TIME(cfg) = 0;
			otawa::ipet::WCET(cfg) = 0;
			otawa::ipet::COUNT(cfg) = 0;
			otawa::ipet::ICACHE_MISSES(cfg) = 0;
			for(CFG::BBIterator bb(cfg); bb; ++bb) {
				otawa::ipet::COUNT(bb) = 0;
				otawa::ipet::TOTAL_TIME(bb) = 0;
				otawa::ipet::ICACHE_MISSES(bb) = 0;
			}
		}
	}

	void rollup_bb_props(CFG* cfg) const {
		otawa::ipet::TOTAL_TIME(cfg) = 0;
		otawa::ipet::ICACHE_MISSES(cfg) = 0;
		for(CFG::BBIterator bb(cfg); bb; ++bb) {
			otawa::ipet::TOTAL_TIME(cfg) += otawa::ipet::TOTAL_TIME(bb);
			otawa::ipet::ICACHE_MISSES(cfg) += otawa::ipet::ICACHE_MISSES(bb);
		}
		otawa::ipet::COUNT(cfg) = otawa::ipet::COUNT(cfg->firstBB());
	}

	void check_annotations() {
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		// correct cases where return was not detected; possibly some asm tricks.
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			if (otawa::ipet::COUNT(cfg) > 0 &&
				otawa::ipet::TOTAL_TIME(cfg) == 0)
			{
				elm::cout << "WARN: Correcting annotations of " << cfg->name() << "..." << io::endl;
				rollup_bb_props(cfg);
			}
		}
	}

	void verbose_cfg(CFG* cfg) {
		elm::cout << "CFG " << cfg->name() <<":" << io::endl;
		for(CFG::BBIterator bb(cfg); bb; ++bb) {
			elm::cout << "\tBB" << bb->number() << ": "
					<< "WCET=" << otawa::ipet::WCET(bb)
					<< io::endl;
			BasicBlock*bbb = bb;
			const PropList& props = *bbb;
			for(PropList::Iter prop(props); prop; prop++) {
				if(prop->id()->name()) {
					StringBuffer buf;
					prop->id()->print(buf, *prop);
					string s = buf.toString();
					elm::cout << "\tPROP " << prop->id()->name() << ": " << s << io::endl;
				}
			}
		}
	}

	/**
	 * @brief write cycle, function, offset, and so on to output
	 */
	void emit_trace(SimContext& ctx, otawa::Inst*curr, const string& what) const {
		// PRINT elf, addr, cycle ...
		elm::cout << process->program()->name() << " " << curr->address() << ": "
			 << what << ": "
			 << sstate->cycle() << ": ";

		// ... function and offset
		CFG* currCFG = (!ctx.callstack.empty()) ? ctx.callstack.top().cfg : NULL;
		if (currCFG) {
			const Address::offset_t off = curr->address() - currCFG->address();
			elm::cout << currCFG->name() << "+" << io::hex(off) << "\t";
		} else {
			elm::cout << "??+??\t";
		}

		// ... assembly ...
		elm::cout << curr;

		// ... additional comments ...
		if (curr->isCall()) {
			elm::cout << "\t;; CALL";
			ctx._call_pending = true;

		} else if (curr->isReturn()) {
			elm::cout << "\t;; RETURN";
		}
		elm::cout << io::endl;
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
		elm::cout << "Processor from " << otawa::PROCESSOR_PATH(props) << io::endl;
		if(mem) {
			otawa::MEMORY_PATH(props) = *mem;
			workspace()->require(hard::MEMORY_FEATURE, props);
			elm::cout << "Memory from " << otawa::MEMORY_PATH(props) << io::endl;
		}
		if (cache) {
			otawa::CACHE_CONFIG_PATH(props) = *cache;
			workspace()->require(hard::CACHE_CONFIGURATION_FEATURE, props);
			elm::cout << "Cache from " << otawa::CACHE_CONFIG_PATH(props) << io::endl;

		}
		if (traceCache) {
			TRACE_CACHES(workspace()) = true;
		}
		if (events) {
			string strev = *events;
			if (strev.indexOf('f') >= 0) ev_fetch = true;
			if (strev.indexOf('d') >= 0) {
				ev_decode = true;
				elm::cerr << "WARN: event 'decode' not supported, yet" << io::endl;
			}
			if (strev.indexOf('e') >= 0) {
				ev_exec = true;
				elm::cerr << "WARN: event 'execute' not supported, yet" << io::endl;
			}
			if (strev.indexOf('c') >= 0) ev_commit = true;
		} else {
			ev_fetch = true;
		}

		// decode the CFGs and stuff
		workspace()->require(otawa::CFG_INFO_FEATURE, props);
		workspace()->require(otawa::COLLECTED_CFG_FEATURE, props);

		// dump the config, if requested
		if (dumpConfig) {
			elm::cout << "Dumping config..." << io::endl;
			display::ConfigOutput output;
			output.process(workspace(), props);
		}

		coll = INVOLVED_CFGS(workspace());
		assert(coll);
		assert(coll->count() > 0);
		if (dumpCfg) {
			predecorate_cfgs();
		}

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
			elm::cout << "Start at " << sym->name() << io::endl;
		} else {
			Option<Pair<cstring,int> > info = process->getSourceLine(start->address());
			if(info) {
				cstring file = (*info).fst;
				int line = (*info).snd;
				elm::cout << "Start at " << start->address() << " (" << file << ":" << line << ")" << io::endl;
			} else {
				elm::cout << "Start at " << start->address() << " (no info)" << io::endl;
			}
		}
		exit = process->findInstAt("_exit");
		if(!exit)
			throw elm::MessageException("no _exit label to stop simulation");
		elm::cout << "Exiting at " << exit << io::endl;

		//current = process->findInstAt("main");
		// someone can make use of this to decide where the heap starts
		//Inst* aa = process->findInstAt("errno"); // +4
		//elm::cerr << aa->address()+4  << io::endl;

		/********
		 * RUN!
		 ********/
		sstate->run(*this); // defined in GenericState.h
		elm::cerr << "cycles = " << sstate->cycle() << io::endl;

		/*********
		 * OUTPUT
		 *********/
		if(inlineCalls) {
			elm::cout << "Virtualizing CFGs (inline calls)..." << io::endl;

			workspace()->require(VIRTUALIZED_CFG_FEATURE, props); // also propagates bb annotations
			const CFGCollection *coll = INVOLVED_CFGS(workspace());
			assert(coll->count() == 1);
			CFG* entry = coll->get(0);
			rollup_bb_props(entry);
		}

		if (dumpCfg) {
			elm::cout << "Dumping CFG to file " << *dumpCfg << io::endl;
			check_annotations();

			io::OutFileStream stream(*dumpCfg);
			otawa::cfgio::Output::WITH_ASM(props) = false;
			otawa::cfgio::Output::OUTPUT(props) = &stream;
			DynProcessor dis("otawa::cfgio::Output");
			dis.process(workspace(), props);
		}
	}

private:
	SimState *state;
	sim::State *sstate;
	Process *process;
	Inst *start, *current, *exit;
	option::ValueOption<string> proc;
	option::ValueOption<string> cache;
	option::ValueOption<string> mem;
	option::ValueOption<string> events;
	option::ValueOption<int> iVerboseLevel;
	option::ValueOption<string> dumpCfg;
	option::BoolOption traceCache;
	option::BoolOption dumpConfig;
	option::BoolOption inlineCalls;
	CFGInfo *cfgInfo;
	const CFGCollection *coll;
	bool ev_fetch;
	bool ev_decode;
	bool ev_exec;
	bool ev_commit;
	SimContext ctx_fetch;
	SimContext ctx_commit;
};

OTAWA_RUN(Simulator);
