/*
 *	$Id$
 *	Copyright (c) 2007, IRIT UPS.
 *
 *	WCETCountRecorder class interface.
 */
#ifndef OTAWA_IPET_WCET_COUNT_RECORDER_H
#define OTAWA_IPET_WCET_COUNT_RECORDER_H

#include <otawa/hard/CacheConfiguration.h>
#include <otawa/proc/BBProcessor.h>
#include <otawa/proc/Feature.h>
#include <otawa/ilp.h>

namespace otawa { namespace ipet {

// WCETCountRecorder class
class WCETCountRecorder: public BBProcessor {
public:
	static p::declare reg;
	WCETCountRecorder(p::declare& r = reg);
protected:
	virtual void processWorkSpace(WorkSpace *fw);
	virtual void processCFG(WorkSpace *fw, CFG *cfg);
	virtual void processBB(WorkSpace *ws, CFG *cfg, BasicBlock *bb);
	virtual void setup(WorkSpace *ws);
	virtual void cleanup(WorkSpace *ws);
private:
	ilp::System *system;
	const hard::Cache *_icache;
};

} } // otawa::ipet

#endif	// OTAWA_IPET_WCET_COUNT_RECORDER_H
