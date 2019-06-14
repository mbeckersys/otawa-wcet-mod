/*
 * main.cpp
 *
 *  Created on: 27 nov. 2014
 *      Author: casse, Martin Becker
 * FIXME: ignore flow constraints, because we don't need it for sim.
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
#include <otawa/prop/DynIdentifier.h>
#include <elm/io/OutFileStream.h>
#include "GenericSimulator.h"
#include "GenericState.h"
#include "SimContext.h"

#include <unistd.h>
#include <set>
#include <map>

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
		state(0),
		process(0),
		startInst(0),
		current(0),
		exitInst(0),
		proc(option::ValueOption<string>::Make(this).cmd("-p").description("Processor description.")),
		cache(option::ValueOption<string>::Make(this).cmd("-c").description("Cache description.")),
		mem(option::ValueOption<string>::Make(*this).cmd("-m").cmd("--memory").description("memory description for simulation")),
		events(option::ValueOption<string>::Make(*this).cmd("-e").cmd("--event").description("which event to trace: 2^{f,d,e,c}")),
		iVerboseLevel(option::ValueOption<int>::Make(*this).cmd("-vl").cmd("--verboseLevel").description("verbose level for simulation")),
		dumpCfg(option::ValueOption<string>::Make(*this).cmd("-o").cmd("--dumpCfg").description("output annotated CFGs of chosen function to given file")),
		dumpFcn(option::ValueOption<string>::Make(*this).cmd("-O").cmd("--dumpFcn").description("Only dump CFG for given function and callees (used with --dumpCfg)")),
		traceCache(*this, 't', "traceCache", "enable cache protocol", false),
		clearCacheOn(option::ValueOption<string>::Make(*this).cmd("-C").cmd("--clearCacheOn").description("Clear the caches when entering given functions")),
		dumpConfig(*this, 'd', "dumpConfig", "write platform config to HTML file", false),
		inlineCalls(*this, 'i', "inlineCalls", "Inline the function calls when dumping CFG (not affecting simulation).", false),
		cfgInfo(0),
		coll(0),
		ctx_fetch(NULL), ctx_commit(NULL)
	{ }

	~Simulator() {
		delete_contexts();
	}

	/***************
	 * init stuff
	 ***************/

	void create_contexts(void) {
		string strev = events ? *events : "f";

		sim_contexts['f'] = &ctx_fetch;
		sim_contexts['d'] = NULL;
		sim_contexts['e'] = NULL;
		sim_contexts['c'] = &ctx_commit;

		unsigned num_ctx = 0;
		for (std::map<char, SimContext**>::const_iterator it = sim_contexts.begin();
			it != sim_contexts.end();
			++it)
		{
			if (strev.indexOf(it->first) >= 0) {
				if (it->second) {
					num_ctx++;
					*(it->second) = new SimContext(string::make(it->first));
					elm::cout << "INFO: Tracking event '" << it->first << "'" << io::endl;
				} else {
					elm::cerr << "WARN: event '" << it->first << "' not supported, yet" << io::endl;
				}
			}
		}
		// we always need the commit stage for internal purposes.
		if (!ctx_commit) {
			ctx_commit = new SimContext("c", false, false);
		}

		if (dumpCfg && num_ctx > 1) {
			elm::cerr << "WARN: --dumpCFG with multiple events doesn't work! Turning it off" << io::endl;
			for (std::map<char, SimContext**>::const_iterator it = sim_contexts.begin();
				it != sim_contexts.end();
				++it)
			{
				(*it->second)->annotate_cfg = false;
			}
		}
	}

	void delete_contexts(void) {
		for (std::map<char, SimContext**>::const_iterator it = sim_contexts.begin();
			it != sim_contexts.end();
			++it)
		{
			if (it->second) {
				delete *it->second;
			}
		}
	}

	void get_clearCachePoints(void) {
		const CFGCollection *coll = INVOLVED_CFGS(workspace());
		string list = clearCacheOn;
		int pos = 0, lastpos = 0;
		while (pos >= 0) {
			pos = list.indexOf(',', lastpos);
			int tail;
			if (pos < 0) {
				tail = list.length();
			} else {
				tail = pos;
			}
			const string fcn = list.substring(lastpos, tail-lastpos).trim();

			bool found = false;
			for (CFGCollection::Iterator cfg(coll); cfg; ++cfg) {
				if (fcn == cfg->name()) {
					address_t addr = cfg->address();
					clearCachePoints.insert(addr);
					elm::cout << "INFO: clearing cache when '" << fcn << "' ("
								<< addr << ") is entered" << io::endl;
					found = true;
					break;
				}
			}
			if (!found) {
				elm::cout << "WARN: cannot clear cache when '" << fcn << "' is entered (not found)"
							<< io::endl;
			}
			lastpos = pos+1;
		}
	}

	/*************************
	 * Simulation control
	 *************************/

	/**
	 * @brief wraps the functional simulator
	 */
	virtual Inst *nextInstruction (sim::State &state, Inst *inst) {
		if(inst == NULL) { // first instruction
			current = startInst;
			return startInst;
		}
		if (current == exitInst) return NULL;

		if (ctx_fetch) {
			track_context(ctx_fetch, inst);
			if (ctx_fetch->emit_trace) emit_trace(ctx_fetch, inst);
			if (ctx_fetch->annotate_cfg) annotate_cfg(ctx_fetch, inst);
		}

		// triggers to functionally execute the instruction to get the next
		current = this->state->execute(current); // for arm: otawa/src/arm2/arm.cpp
		if (!clearCachePoints.empty()) check_clearCacheOn(current);
		return current;
	}

	/**
	 * @brief called whenever an instruction is committed
	 * We now have additional information, like cache misses
	 */
	virtual void terminateInstruction(sim::State &state, Inst *inst) {
		assert(ctx_commit); // needed to get extra info about retired instructions
		track_context(ctx_commit, inst);

		// get post-execution info about instruction for statistics
		if (GenericState* gs = dynamic_cast<GenericState*>(&state)) {
			SimulatedInstruction* sInst = gs->getTerminatingInstruction();
			assert(sInst);
			const bool cache_miss = sInst->cacheMiss();
			if (cache_miss && ctx_commit->curr_bb) {
				annotate_cache_miss(ctx_commit->curr_bb);
				#if 0
				elm::cout << "Inst " << sInst->inst()->address()
							<< " (BB=" << ctx_commit->curr_bb->address() << ")"
							<< " has cache miss " << io::endl;
				#endif
			}
		}

		if (ctx_commit->emit_trace) emit_trace(ctx_commit, inst);
		if (ctx_commit->annotate_cfg) annotate_cfg(ctx_commit, inst);
	}

	/**
	 * @brief check whether user requested to clear cache for this insn
	 */
	inline void check_clearCacheOn(Inst* insn) {
		if (clearCachePoints.find(insn->address()) != clearCachePoints.end()) {
			gsim.clearCaches();
		}
	}

	/*************************
	 * Tracking Execution
	 *************************/

	 /*
	  * We track basic blocks independently of the callstacks.
	  *  - Callstacks are tracked on unprocessed CFGs, to enable call counters when virtual inlining is off
	  *  - BBs are tracked via CFG edges as opposed to callstacks, since we want to follow virtual inlining when on
	  *
	  * Comment about CFG collections:
	  *  - CFGCollection *cfgs = INVOLVED_CFGS(workspace());  ///< only sees inlined
	  *  - CFGCollection::Iter cfg(cfgInfo)  ///< finds all cfgs as they are in the binary
	  */

	inline otawa::BasicBlock* find_next_bb(otawa::BasicBlock* curr_bb, otawa::Inst* next_inst) const {
		if (curr_bb) {
			/*
			elm::cout << "next bb for "
						<< curr_bb->cfg()->name() << "."
						<< curr_bb->number()
						<< " @" << curr_bb->address()
						<< " starting with address " << next_inst->address()
						<< io::endl;
			*/
			for(BasicBlock::OutIterator edge(curr_bb); edge; edge++) {
				otawa::BasicBlock* cand = edge->target();
				if (cand) {
					if (debugVerbose)
						elm::cout << "next bb: " << cand->address() << "?" << io::endl;
					if (cand->firstInst() == next_inst) {
						return cand;
					}
				}
			}
		}

		// still here? then maybe OTAWA is confused or we have >2 targets?
		// scan all BBs in all CFGs
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());  ///< only sees inlined
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			for(CFG::BBIterator bb(cfg); bb; ++bb) {
				if (bb->firstInst() == next_inst) {
					elm::cout << "WARN: had lost track of BBs, recovered now." << io::endl;
					return bb;
				}
			}
		}
		return NULL;
	}

	/**
	 * @brief keep track of currently running function and so on
	 */
	void track_context(SimContext* ctx, otawa::Inst*curr) const {
		// new function begins. use callstack.
		ctx->begin_of_func = ctx->_call_pending;
		if (ctx->_call_pending) {
			ctx->_call_pending = false;
			CFG *jj = cfgInfo->findCFG(curr); // only finds the first insn/addr of each function
			if (jj) {
				SimContext::callstack_item cit(jj, sstate->cycle());
				ctx->callstack.push(cit);
			}
		}
		// new BB begins. find it. Don't rely on callstack, because it might be virtualized.
		ctx->begin_of_bb = ctx->_endofbb_pending;
		if (ctx->_endofbb_pending) {
			ctx->_endofbb_pending = false;
			if (debugVerbose)
				elm::cout << ctx->name << ": next bb?" << io::endl;
			otawa::BasicBlock* next_bb = find_next_bb(ctx->curr_bb, curr);
			if (debugVerbose && next_bb) {
				elm::cout << ctx->name << ": " << next_bb->cfg()->name() << "."
							<< next_bb->number()
							<< " @" << next_bb->address()
							<< " begins" << io::endl;
			}
			ctx->pre_bb = ctx->curr_bb;
			ctx->curr_bb = next_bb;
		}
		// search for upcoming callstack changes and end of BB
		if (curr->isCall()) {
			ctx->_call_pending = true;
		}
		if (curr->isReturn()) {
			if (!ctx->callstack.empty()) {
				SimContext::callstack_item cit = ctx->callstack.top();
				ctx->callstack.pop();

				const int duration = sstate->cycle() - cit.time_called;
				ctx->end_of_func = true;
				ctx->returned_cfg = cit.cfg;
				ctx->duration_returned_cfg = duration;
			}
		} else {
			ctx->end_of_func = false;
		}
		if (ctx->curr_bb) {
			ctx->_endofbb_pending = ctx->curr_bb->lastInst() == curr;
		} else {
			ctx->_endofbb_pending = true; // next insn is scanned for BB...until we have one
		}
	}

	/**
	 * @brief write cycle, function, offset, and so on to output
	 */
	void emit_trace(SimContext* ctx, otawa::Inst*curr) const {
		// PRINT elf, addr, cycle ...
		elm::cout << process->program()->name() << " " << curr->address() << ": "
			 << ctx->name << ": "
			 << sstate->cycle() << ": ";

		// ... function and offset
		CFG* currCFG = (!ctx->callstack.empty()) ? ctx->callstack.top().cfg : NULL;
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
			ctx->_call_pending = true;

		} else if (curr->isReturn()) {
			elm::cout << "\t;; RETURN";
		}
		elm::cout << io::endl;
	}

	/*************************
	 * Back-annotation of CFG
	 *************************/

	/**
	 * @brief initialize all CFG annotations
	 */
	void predecorate_cfgs(void) {
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			ipet::TOTAL_TIME(cfg) = 0;
			ipet::WCET(cfg) = 0;
			ipet::COUNT(cfg) = 0;
			ipet::ICACHE_MISSES(cfg) = 0;
			for(CFG::BBIterator bb(cfg); bb; ++bb) {
				ipet::COUNT(bb) = 0;
				ipet::TOTAL_TIME(bb) = 0;
				//ipet::TIME(bb) = -1;
				ipet::ICACHE_MISSES(bb) = 0;
			}
		}
	}

	inline void annotate_cache_miss(BasicBlock *bb) {
		ipet::ICACHE_MISSES(bb) += 1;
	}

	/**
	 * @brief write back some stats to the CFG
	 */
	void annotate_cfg(SimContext* ctx, Inst *inst) {
		/*****************
		 * function stats
		 *****************/
		if (!ctx->callstack.empty()) {
			SimContext::callstack_item cit = ctx->callstack.top();
			if (ctx->begin_of_func) {
				ipet::COUNT(cit.cfg) += 1;
				if (debugVerbose)
					elm::cout << ctx->name << ": Function " << cit.cfg->name()
								<< " is called" << io::endl;
			}
			if (ctx->end_of_func) {
				// elm::cout << "Function '" << ctx->returned_cfg->name() << "' returned after "
				//	 << ctx->duration_returned_cfg << " cycles " << io::endl;
				if (ctx->duration_returned_cfg > ipet::WCET(ctx->returned_cfg)) {
					ipet::WCET(ctx->returned_cfg) = ctx->duration_returned_cfg;
				}
				ipet::TOTAL_TIME(ctx->returned_cfg) += ctx->duration_returned_cfg;
			}
		}
		/*****************
		 * BB stats
		 *****************/
		if (ctx->begin_of_bb) {
			if (ctx->curr_bb) {
				ipet::COUNT(ctx->curr_bb) += 1;
			}
			const int now = sstate->cycle();
			if (ctx->pre_bb) {
				const int duration = now - ctx->time_bb_enter;
				// time is cumulative incl. all cache and pipeline effects
				ipet::TOTAL_TIME(ctx->pre_bb) += duration;
				if (duration > ipet::WCET(ctx->pre_bb)) {
					ipet::WCET(ctx->pre_bb) = duration;
				}
			}
			ctx->time_bb_enter = now;
		}
	}

	void rollup_bb_props(CFG* cfg) const {
		ipet::TOTAL_TIME(cfg) = 0;
		ipet::ICACHE_MISSES(cfg) = 0;
		for(CFG::BBIterator bb(cfg); bb; ++bb) {
			if (ipet::TOTAL_TIME(bb) >= 0) {
				ipet::TOTAL_TIME(cfg) += ipet::TOTAL_TIME(bb);
				ipet::ICACHE_MISSES(cfg) += ipet::ICACHE_MISSES(bb);
				#if 0
					// sanity check
					int expected_time = ipet::COUNT(bb) * bb->countInsts();
					if (cache) {
						const unsigned cache_penalty = 10;
						expected_time += ipet::ICACHE_MISSES(bb) * cache_penalty;
					}
					if (expected_time != ipet::TOTAL_TIME(bb)) {
						elm::cout << "WARN: " << cfg->name() << ".BB #" << bb->number() << " "
									<< bb->address() << " might have too much time "
									<< "(" << ipet::TOTAL_TIME(bb) << " instead of "
									<< expected_time << ")" << io::endl;
					}
				#endif
			}
		}
		ipet::COUNT(cfg) = ipet::COUNT(cfg->firstBB());
		if (1 == ipet::COUNT(cfg)) {
			ipet::WCET(cfg) = ipet::TOTAL_TIME(cfg);
		}
	}

	void check_annotations() {
		const CFGCollection *cfgs = INVOLVED_CFGS(workspace());
		// correct cases where return was not detected; possibly some asm tricks.
		for(CFGCollection::Iterator cfg(cfgs); cfg; ++cfg) {
			if (ipet::COUNT(cfg) > 0 && ipet::TOTAL_TIME(cfg) == 0) {
				elm::cout << "WARN: Correcting annotations of " << cfg->name() << "..." << io::endl;
				rollup_bb_props(cfg);
			}
		}
	}

	void verbose_cfg(CFG* cfg) {
		elm::cout << "CFG " << cfg->name() <<":" << io::endl;
		for(CFG::BBIterator bb(cfg); bb; ++bb) {
			elm::cout << "\tBB" << bb->number() << ": " << "WCET=" << ipet::WCET(bb) << io::endl;
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

		/*******************
		 * Platform config
		 *******************/

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

		// dump the config, if requested
		if (dumpConfig) {
			elm::cout << "Dumping config..." << io::endl;
			display::ConfigOutput output;
			output.process(workspace(), props);
		}

		// create contexts for events to be tracked
		create_contexts();

		/*******************
		 * Get CFGs
		 *******************/

		// decode the CFGs and stuff
		workspace()->require(otawa::CFG_INFO_FEATURE, props);  ///< builds CFGs
		cfgInfo = CFGInfo::ID(workspace());
		assert(cfgInfo);
		if (dumpFcn) {
			// non-default entry requested (important for inlining)
			CFG* cfg_entry = cfgInfo->findCFG(dumpFcn);
			if (!cfg_entry) {
				elm::cerr << "ERROR: dumpFcn function '" << dumpFcn << "' not found!" << io::endl;
				exit(1);
			}
			elm::cout << "INFO: dumpFcn function=" << cfg_entry->name() << io::endl;
			ENTRY_CFG(props) = cfg_entry;
		}
		workspace()->require(otawa::COLLECTED_CFG_FEATURE, props);  ///< creates INVOLVED_CFGs

		if (clearCacheOn) {
			get_clearCachePoints();
		}

		if (inlineCalls) {
			elm::cout << "Virtualizing CFGs (inline calls)..." << io::endl;
			workspace()->require(VIRTUALIZED_CFG_FEATURE, props);
			const CFGCollection *coll = INVOLVED_CFGS(workspace());
			assert(coll->count() == 1);
		}

		coll = INVOLVED_CFGS(workspace());
		assert(coll);
		assert(coll->count() > 0);
		if (dumpCfg) {
			predecorate_cfgs();
		}

		/***********
		 * init sim
		 ***********/

		// prepare the functional simulation
		process = workspace()->process();

		// initialize the arm *functional* iss
		// arm.cpp implements newState which create simState (also implemented in arm.cpp)
		state = process->newState();
		if(!state)
			throw MessageException("no functional simulator with the current loader");

		// prepare the *temporal* simulation
		// which creates the systemC modules
		// this returns a GenericState, which extends from the sim::State
		sstate = gsim.instantiate(workspace());

		/*************
		 * BEGIN/EXIT
		 *************/

		// start() is implemented in arm.cpp, which returns the startInst instruction
		// the startInst instruction is identified when loading the binary file
		startInst = process->start();
		ASSERT(startInst);
		Symbol* sym = process->findSymbolAt(startInst->address());
		if (sym) {
			elm::cout << "Starting at " << sym->name() << io::endl;
		} else {
			Option<Pair<cstring,int> > info = process->getSourceLine(startInst->address());
			elm::cout << "Starting at " << startInst->address();
			if(info) {
				cstring file = (*info).fst;
				int line = (*info).snd;
				elm::cout << " (" << file << ":" << line << ")" << io::endl;
			} else {
				elm::cout << " (no info)" << io::endl;
			}
		}
		exitInst = process->findInstAt("_exit");
		if(!exitInst)
			throw elm::MessageException("no _exit label to stop simulation");
		elm::cout << "Exiting at " << exitInst << io::endl;

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
		if (inlineCalls) {
			const CFGCollection *coll = INVOLVED_CFGS(workspace());
			CFG* dumpFcn = coll->get(0);
			rollup_bb_props(dumpFcn);
		}

		if (dumpCfg) {
			elm::cout << "Dumping CFG to file " << *dumpCfg << io::endl;
			check_annotations();

			//io::OutFileStream stream(*dumpCfg);
			//otawa::cfgio::Output::OUTPUT(props) = &stream;

			DynIdentifier<string> FILENAME("otawa::cfgio::Output::FILENAME");
			FILENAME(props) = *dumpCfg;
			DynProcessor dis("otawa::cfgio::Output");
			dis.process(workspace(), props);
		}
	}

private:
	gensim::GenericSimulator gsim;
	SimState *state;
	sim::State *sstate;
	Process *process;
	Inst *startInst, *current, *exitInst;

	option::ValueOption<string> proc;
	option::ValueOption<string> cache;
	option::ValueOption<string> mem;
	option::ValueOption<string> events;
	option::ValueOption<int> iVerboseLevel;
	option::ValueOption<string> dumpCfg;
	option::ValueOption<string> dumpFcn;
	option::BoolOption traceCache;
	option::ValueOption<string> clearCacheOn;
	option::BoolOption dumpConfig;
	option::BoolOption inlineCalls;

	CFGInfo *cfgInfo;
	const CFGCollection *coll;
	SimContext *ctx_fetch;
	SimContext *ctx_commit;
	std::map<char, SimContext**> sim_contexts;
	std::set<otawa::address_t> clearCachePoints;
};

OTAWA_RUN(Simulator);
