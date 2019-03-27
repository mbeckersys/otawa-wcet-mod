/*
 *	$Id$
 *	Copyright (c) 2007, IRIT UPS.
 *
 *	WCETCountRecorder class implementation.
 */

#include <elm/assert.h>
#include <otawa/ipet/WCETCountRecorder.h>
#include <otawa/ipet/WCETComputation.h>
#include <otawa/ipet/IPET.h>
#include <otawa/cache/LBlockSet.h>
#include <otawa/cache/cat2/features.h>
#include <otawa/hard/Platform.h>
#include <otawa/ilp.h>
#include <otawa/cfg/Edge.h>
#include <otawa/cfg/features.h>
#include <otawa/ipet/ILPSystemGetter.h>

namespace otawa { namespace ipet {

/**
 * @class WCETCountRecorder
 * This class may be used to record back in the CFG the execution count of each
 * basic block and of each edge for the WCET path.
 *
 * @par Provided Features
 * @li @ref WCET_COUNT_RECORDED_FEATURE
 *
 * @par Required Features
 * @li @ref WCET_FEATURE
 */


/**
 */
void WCETCountRecorder::setup(WorkSpace *fw) {
	ASSERT(fw);
	ASSERT(!system);
	system = SYSTEM(fw);
	ASSERT(system);
}


/**
 */
void WCETCountRecorder::cleanup(WorkSpace *fw) {
	ASSERT(fw);
	ASSERT(system);
	system = 0;
}

void WCETCountRecorder::processWorkSpace(WorkSpace *fw) {
	// before doing anything, back-annotate all the i-cache misses, because they are
	// global (per cache set) rather than per CFG
	_icache = hard::CACHE_CONFIGURATION(fw)->instCache();
	if(_icache) {
		LBlockSet **lbsets = LBLOCKS(fw);
		if (lbsets) {
			for (int i = 0 ; i < _icache->rowCount(); i++) {
				for (LBlockSet::Iterator lb(*lbsets[i]); lb; lb++) {
					BasicBlock* bb = lb->bb();
					if (bb) {
						if (ilp::Var *mvar = MISS_VAR(lb)) {
							if (ICACHE_MISSES(bb) < 0) ICACHE_MISSES(bb) = 0;
							ICACHE_MISSES(bb) += int(system->valueOf(mvar));
							CFG* cfg = bb->cfg();
							if (cfg) {
								if (ICACHE_MISSES(cfg) < 0) ICACHE_MISSES(cfg) = 0;
								ICACHE_MISSES(cfg) += int(system->valueOf(mvar));
							}
						}
					}
				}
			}
		} else {
			_icache = NULL; // to avoid any back-annotation
			log << "\tCache present, but no cache analysis done" << io::endl;
		}
	}

	// now all the CFGs
	const CFGCollection *cfgs = INVOLVED_CFGS(fw);
	ASSERT(cfgs);
	for(CFGCollection::Iterator cfg(cfgs); cfg; cfg++) {
		if(logFor(LOG_CFG))
			log << "\tprocess CFG " << cfg->label() << io::endl;
		processCFG(fw, cfg);
	}
}

void WCETCountRecorder::processCFG(WorkSpace *fw, CFG *cfg) {
	int wcet_cfg = 0;
	for(CFG::BBIterator bb(cfg); bb; bb++) {
		if(logFor(LOG_BB)) {
			log << "\t\tprocess BB " << bb->number()
				<< " (" << ot::address(bb->address()) << ")\n";
		}
		processBB(fw, cfg, bb);

		// annotate CFG itself
		if (COUNT(bb) >= 0) {
			wcet_cfg += TOTAL_TIME(bb);
			if (bb == cfg->entry()) {
				COUNT(cfg) = COUNT(bb);
			}
		}
	}
	WCET(cfg) = wcet_cfg;
}

/**
 */
void WCETCountRecorder::processBB(WorkSpace *fw, CFG *cfg, BasicBlock *bb) {
	ASSERT(fw);
	ASSERT(cfg);
	ASSERT(bb);

	// Record BB var count
	ilp::Var *var = VAR(bb);
	if(var) {
		COUNT(bb) = (int)system->valueOf(var);
		// also sum up overall contrib to WCET
		TOTAL_TIME(bb) = COUNT(bb) * TIME(bb);
		if (_icache) {
			int cache_time = ICACHE_MISSES(bb) * _icache->missPenalty();
			TOTAL_TIME(bb) += cache_time;
		}
	}

	// Record out var count
	for(BasicBlock::OutIterator edge(bb); edge; edge++) {
		ilp::Var *var = VAR(edge);
		if(var) {
			COUNT(edge) = (int)system->valueOf(var);
		}
	}
}


/**
 */
WCETCountRecorder::WCETCountRecorder(p::declare& r): BBProcessor(r), system(0) {
}


/**
 */
p::declare WCETCountRecorder::reg = p::init("otawa::ipet::WCETCountRecorder", Version(1, 0, 1))
	.base(BBProcessor::reg)
	.maker<WCETCountRecorder>()
	.require(WCET_FEATURE)
	.provide(WCET_COUNT_RECORDED_FEATURE);


/**
 * This feature asserts that WCET execution count of basic block and of edge
 * have been recorded.
 *
 * @par Properties
 * @li @ref ipet::COUNT
 */
p::feature WCET_COUNT_RECORDED_FEATURE("otawa::ipet::WCET_COUNT_RECORDED_FEATURE", new Maker<WCETCountRecorder>());

} } // otawa::ipet
