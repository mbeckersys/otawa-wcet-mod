/*
 * main.cpp
 *
 *  Created on: 27 nov. 2014
 *      Author: casse
 */
#include <otawa/app/Application.h>
#include <elm/option/ValueOption.h>
#include <otawa/hard/Processor.h>
#include <otawa/hard/Memory.h>
#include <otawa/cfg/features.h>
#include "GenericSimulator.h"

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
		Application("ogensim", Version(1, 0, 1)),
		proc(option::ValueOption<string>::Make(this).cmd("-p").description("Processor description.")),
		cache(option::ValueOption<string>::Make(this).cmd("-c").description("Cache description.")),
		mem(option::ValueOption<string>::Make(*this).cmd("-m").cmd("--memory").description("memory description for simulation")),
		iVerboseLevel(option::ValueOption<int>::Make(*this).cmd("-vl").cmd("--verboseLevel").description("verbose level for simulation")),
		process(0),
		current(0),
		start(0),
		exit(0),
		state(0),
		coll(0),
		cfgInfo(0)
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
		cerr << current->address() << '\t' << current << io::endl;
		current = this->state->execute(current); // for arm: otawa/src/arm2/arm.cpp

		//do_stuff();

		return current;
	}

	void do_stuff() {
					//BasicBlock *bbbb = cfgInfo->findBB(current);
			//printf("[%s:%d] bbbb = 0x%X\n", __FILE__, __LINE__, bbbb);




/*
//			CodeBasicBlock *asdfg = BB(inst);
//			assert(asdfg);

			CFG *jj = cfgInfo->findCFG(current);
			// assert(jj);
			if(jj != 0) printf("[%s:%d] CFG BB count = %d\n", __FILE__, __LINE__, jj->countBB());


			for(CFGCollection::Iterator cfg(coll); cfg; cfg++)
			{
				for(CFG::BBIterator bb(cfg); bb; bb++)
				{
//					cout << "[" << __FILE__ << ":" << __LINE__ << "] " << "\t\tprocess BB " << bb->number()
//									<< " (" << ot::address(bb->address()) << ")\n";

					for(BasicBlock::InstIter instx(bb); instx; instx++)
					{
						//cout << instx->address() << "\n";
						if(instx->address() == current->address())
						{
							cout << "[" << __FILE__ << ":" << __LINE__ << "] " << " BB index = " <<  bb->number() << "\n";
							//return bb;
						} // end of if(instx->address() == inst->address())
					} // end of for(BasicBlock::InstIter instx(bb); instx; instx++)
				} // end of for(CFG::BBIterator bb(cfgToFind); bb; bb++)

			}

			//std::exit(1);

			//CFG *jj = cfgInfo->findCFG(current);
			//assert(jj);

			// cfgInfo->findBB(current) is the BB of the current instruction
			//printf("[%s:%d] BB index = %d\n", __FILE__, __LINE__, cfgInfo->findBB(current)->number());
*/
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

		// acquire the CFG
		// .......

		// install the hardware
		if(!*proc)
			throw elm::MessageException("no processor provided");
		otawa::PROCESSOR_PATH(props) = *proc;
		if(mem)
			otawa::MEMORY_PATH(props) = *mem;
		workspace()->require(hard::PROCESSOR_FEATURE, props);
		workspace()->require(hard::MEMORY_FEATURE);

		// decode the CFGs
		workspace()->require(otawa::CFG_INFO_FEATURE, props);
		workspace()->require(otawa::COLLECTED_CFG_FEATURE, props);

		coll = INVOLVED_CFGS(workspace());
		assert(coll);
		assert(coll->get(0));

		// obtain the CFG info
		cfgInfo = CFGInfo::ID(workspace());
		assert(cfgInfo);




		// prepare the functional simulation
		process = workspace()->process();

		// initialize the arm iss
		// arm.cpp implements newState which create simState (also implemented in arm.cpp)
		state = process->newState();
		if(!state)
			throw MessageException("no functional simulator with the current loader");

		// prepare the temporal simulation
		// which creates the systemC modules
		gensim::GenericSimulator gsim;
		// this returns a GenericState, which extends from the sim::State
		sim::State *sstate = gsim.instantiate(workspace());

		cout << "we passed gsim.instantiate(workspace());\n";


		// start() is implemented in arm.cpp, which returns the start instruction
		// the start instruction is identified when loading the binary file
		start = process->start();

		// lets try to get basic block with the instruction
		CFG *jj = cfgInfo->findCFG(start);
		assert(jj);
		printf("[%s:%d] CFG BB count = %d\n", __FILE__, __LINE__, jj->countBB());

		// BasicBlock* bb = cfgInfo->findBB(current);
		// printf("[%s:%d] BB index = %d\n", __FILE__, __LINE__, bb->number());


		//std::exit(0);


		cout << "we passed process->start();\n";

		ASSERT(start);
		exit = process->findInstAt("_exit");
		if(!exit)
			throw elm::MessageException("no _exit label to stop simulation");
		cout << "Exiting at " << exit << endl;

		//current = process->findInstAt("main");

		// someone can make use of this to decide where the heap starts
		//Inst* aa = process->findInstAt("errno"); // +4
		//cerr << aa->address()+4  << io::endl;

		// run the simulation
		sstate->run(*this); // defined in GenericState.h
		cerr << "cycles = " << sstate->cycle() << endl;
	}

private:
	SimState *state;
	Process *process;
	Inst *start, *current, *exit;
	option::ValueOption<string> proc;
	option::ValueOption<string> cache;
	option::ValueOption<string> mem;
	option::ValueOption<int> iVerboseLevel;
	CFGInfo *cfgInfo;
	const CFGCollection *coll;
};

OTAWA_RUN(Simulator);
