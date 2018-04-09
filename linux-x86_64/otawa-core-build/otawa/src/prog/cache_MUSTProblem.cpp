
#include <stdio.h>
#include <elm/io.h>
#include <otawa/cache/LBlockSet.h>
#include <otawa/util/LBlockBuilder.h>
#include <otawa/ilp.h>
#include <otawa/ipet.h>
#include <otawa/cfg/Edge.h>
#include <otawa/util/Dominance.h>
#include <otawa/cfg.h>
#include <otawa/util/LoopInfoBuilder.h>
#include <otawa/hard/CacheConfiguration.h>
#include <otawa/hard/Platform.h>


#include <otawa/cache/cat2/MUSTProblem.h>
#include <otawa/cache/FirstLastBuilder.h>


using namespace otawa;
using namespace otawa::ilp;
using namespace otawa::ipet;



/**
 * @class MUSTProblem
 *
 * Problem for computing the cache MUST ACS.
 * This implements Ferdinand's Must analysis.
 *
 * Each cache set is modeled as one cache line, which
 * holds A (number of ways) elements, sorted by age (youngest first).
 *
 */

namespace otawa {


MUSTProblem::MUSTProblem(const int _size, LBlockSet *_lbset, WorkSpace *_fw, const hard::Cache *_cache, const int _A)
:	lbset(_lbset),
	fw(_fw),
	line(lbset->line()),
	cache(_cache),
	bot(_size, _A),
	ent(_size, _A),
	callstate(_size, _A)
{
		ent.empty();
}

MUSTProblem::~MUSTProblem() {

}
const MUSTProblem::Domain& MUSTProblem::bottom(void) const {
		return bot;
}
const MUSTProblem::Domain& MUSTProblem::entry(void) const {
		return ent;
}

// this is called on a BB: finds L-block and checks whether it belongs to the
// cache set of this MUSTProblem instance.
// we don't need to iterate over all l-blocks of this BB, just over the first.
// the cache behavior of the others in this line follows.
void MUSTProblem::update(Domain& out, const Domain& in, BasicBlock* bb) {
	assign(out, in); // out := in
	LBlock *lblock = LAST_LBLOCK(bb)[line]; // if L-block is stored in in this cache set (set==line if direct-mapped) ... FIXME: why LAST? actually we don't care, as long as it's this line.
	if (lblock != NULL)
		out.inject(lblock->cacheblock()); // ... then update this cache set (makes cacheblock the youngest element in the set)
}

elm::io::Output& operator<<(elm::io::Output& output, const MUSTProblem::Domain& dom) {
	dom.print(output);
	return output;
}

}
