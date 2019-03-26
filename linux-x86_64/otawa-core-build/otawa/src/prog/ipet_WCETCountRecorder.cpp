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
			wcet_cfg += COUNT(bb);
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
		TOTAL_TIME(bb) = COUNT(bb) * TIME(bb); // TODO: cache?
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
