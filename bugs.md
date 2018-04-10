# ndes/FDO

HalfAbsInt somehow has BB24 (0x8274) in PERS set (SET/line 39, cid=1), but it's not in a loop
output = PERS=[ (W=[cid=1:0], [cid=1:0])] MUST=[ [cid=1:0]]

Hypotheses:
 H0: AI accidentally processes entry twice => No.
 H1: context is left too often (multiple times per one loop) => No.
 H3: accidenally enters a loop and creates PERS data where isn't one => No
 H4: The one edge that leaves both loops from the inner one makes trouble => YES.

## Diagnosis
SET 39: occurs in PERS (is that okay?): PERS=[ (W=[1:0], []|[1:0, 2:1])] => meaning: there are two levels of PERS analysis; the innermost one has cid=1 with age=0 and cid=2 with age=1
    output notation: [item:age], where age in [0, A-1] and A stands for "older than A-1"
    data is the stack of PERS analyses
    W stands for WHOLE, and is not being used in I-caches (only D-caches)

When leaving loop B7, the deck is not cleaned up. It grows again!!!

Error 1: ML-persistence analysis has too many stack items => BBs outside of loop have persistence data
Behavior: analysis crashes.

## Unrelated findings
AbsInt terminates early in SET1:
 1. outer loop reaches fixpoint
 2. pushing all of its exit edges: 17->24, 25->24, 32->38
   25->24 fails because the depend on BB38
   17->24 fails because the depend on BB38
   32->38 is pushed
 4. BB38 is in worklist, pushes BB24
 5. BB24 is in worklist, fails pushing BB 24->31, because 68->31 is not done (that is the back-edge of loop header BB31) ---> why does it work in SET0 but not in SET1???

Error 2: AbsInt terminates early. Some BBs are never evaluated => result is unsafe.
Error 2.1: back edges are not always identified -> problem with irreducible loops?
Error 2.2: FIRST_ITER seems to be not reset when analysis does not terminate a loop

Behavior: silently ignored, therefore WCET estimates are UNSAFE (only half the BBs are simulated,
therefore not all evictions are encountered). The error amplifies itself: when AbsInt for one cache
set terminates early, following set analyses may terminate even earlier because the markers
are not properly reset then.

## Conclusion
All the seen errors suggest that OTAWA fails with non-natural loops. Major flaw, needs fix.

## Solution Draft
TBD
 0. Add consistency checks
   0.1 DONE: when AbsInt terminates, all loops must have reached fixpoint
   0.2 TODO: PERS stack cannot be deeper than loop nesting level
 1. Fix missing identification of some back-edges (TODO: check whether dominator analysis fails).
    After that analysis should not no longer terminate prematurely.
 2. Handle the case where multiple loops are exited at once.

AbsInt notes:
 * exit edges are not enabled until the loop's fixpoint are not reached
 * other edges are not added to worklist (well..their targets), when the target's other
   edges are not yet completed. Therefore, the last predecessor to be computed will add it to
   the worklist.
