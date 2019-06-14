# Extended OTAWA WCET analysis tools
This repository holds a modified version of the OTAWA v1 WCET toolbox (www.otawa.fr).

The original version of OTAWA which was used as a basis is from 2018-Jan-15 (fddfe090441c).

## Modifications
(see diff or branch changelog)

 * simulator: revived and added I-cache model, CFG back-annotation, etc.

### Generic, cycle-accurate simulator for ARM binaries
The program `ogensim` was taken from an older branch of OTAWA and revived. It is
a generic functional and temporal simulator that builds on the decoders existing in OTAWA.
The following modifications were done:

 * fix everything to get a successful build with current OTAWA
