# Extended OTAWA WCET analysis tools
This repository holds a modified version of the OTAWA v1 WCET toolbox (www.otawa.fr) from IRIT/University of Toulouse.
Unlike the original, this version features a temporal and functional simulator for ARM binaries. There are further changes, but these are mostly minor.

The original version of OTAWA was from 2018-Jan-15 (fddfe090441c).

## Modifications
(see diff or branch changelog)

 * simulator: revived and added I-cache model, CFG back-annotation, etc.

### Generic, cycle-accurate simulator for ARM binaries
The program `ogensim` was taken from an older branch of OTAWA and revived. It is
a generic functional and temporal simulator that builds on the decoders existing in OTAWA.

:warning: Note that this does not simulate a specific ARM-based processor, but just reads ARM binaries 
and simulates them on a generic microarchitecture that is configured with XML files.

The following modifications were done:

 * fix everything to get a successful build with current OTAWA
 * added I-cache model (LRU only)
   * optionally creates cache access trace
   * configured according to OTAWA's XML description
 * emit a trace for either fetch, decode, execute or commit stage
   * can be parsed into a timing profile with script `ogensim2times.py`
 * dump CFG annotated with simulation results (exec count, exec time, cache misses)
   * can be diff'd against `owcet` output to compare WCET estimate with simulation
   * (changes to OTAWA core were necessary to enable annotation)
 * option to clear cache when given function is entered (for comparability with WCET estimate)

## Compiling
Use `otawa/build.sh`. For the first build, uncomment the last line in that file.
Downloads OTAWA sources from the original authors (in specific revisions) and builds everything.
After building you want to comment this line again, to avoid that the repository is accidentally re-downloaded, discarding all of your potential changes. For the second build onwards, use `otawa/make install` instead.

## How to run the simulation on an ARM binary
See `otawa/linux-x86_64/otawa-core-build/ogensim/example`.
