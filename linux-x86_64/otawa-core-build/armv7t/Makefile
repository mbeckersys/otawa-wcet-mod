#
# ARMv5T -- GLISS2 implementation of ARMv5T
# Copyright (C) 2011  IRIT - UPS
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

-include config.mk 

# definitions
ARCH=arm
ifdef WITH_DYNLIB
REC_FLAGS = WITH_DYNLIB=1
endif

GFLAGS= \
	-m loader:old_elf \
	-m code:code \
	-m env:void_env \
	-m sys_call:extern/sys_call \
	-m shift:extern/shift \
	-v \
	-a disasm.c \
	-S \
	-switch \
	-D

ifdef WITH_IO
GFLAGS += -m mem:io_mem
else
GFLAGS += -m mem:vfast_mem
endif

ifdef WITH_THUMB
MAIN_NMP	=	arm-thumb.nmp
else
MAIN_NMP	=	arm.nmp
endif
NMP = \
	nmp/$(MAIN_NMP) \
	nmp/condition.nmp \
	nmp/control.nmp \
	nmp/dataProcessingMacro.nmp \
	nmp/dataProcessing.nmp \
	nmp/exception.nmp \
	nmp/fp.nmp  \
	nmp/loadstore.nmp \
	nmp/loadStoreM.nmp \
	nmp/loadStoreM_Macro.nmp \
	nmp/modes.nmp \
	nmp/mult.nmp \
	nmp/shiftedRegister.nmp \
	nmp/simpleType.nmp \
	nmp/state.nmp \
	nmp/syntax_macros.nmp \
	nmp/system.nmp \
	nmp/thumb2.nmp \
	nmp/tempVar.nmp
ifdef WITH_THUMB
NMP += nmp/thumb.nmp nmp/thumb2.nmp nmp/mem-thumb2.nmp nmp/gen.nmp nmp/coproc.nmp
endif


# goals definition
GOALS		=
SUBDIRS		=	src
CLEAN		=	arm.nml arm.irg nmp/state.nmp
DISTCLEAN	=	include src $(CLEAN) config.mk
LIB_DEPS	=	include/arm/config.h

ifdef WITH_FAST_STATE
GFLAGS		+=	-a used_regs.c
LIB_DEPS	+=	src/used_regs.c
endif

ifdef WITH_DISASM
GOALS		+=	arm-disasm
SUBDIRS		+=	disasm
DISTCLEAN	+= 	disasm
GFLAGS		+= -a disasm.c
LIB_DEPS	+= src/disasm.c 
endif

ifdef WITH_SIM
GOALS		+=	arm-sim
SUBDIRS		+=	sim
DISTCLEAN	+=	sim
endif


# rules
all: lib $(GOALS)

$(ARCH).irg: $(NMP)
	cd nmp &&  ../$(GLISS_PREFIX)/irg/mkirg $(MAIN_NMP) ../$@  && cd ..

ifdef WITH_FAST_STATE
STATE_NMP=state-fast.nmp
else
STATE_NMP=state-normal.nmp
endif
nmp/state.nmp: nmp/$(STATE_NMP) config.mk
	cp nmp/$(STATE_NMP) nmp/state.nmp  

src include: arm.irg
	$(GLISS_PREFIX)/gep/gep $(GFLAGS) $<

lib: src $(LIB_DEPS)
	(cd src; make $(REC_FLAGS))

arm-disasm:
	cd disasm; make

include/arm/config.h: config.tpl
	test -d src || mkdir src
	cp config.tpl $@
ifdef WITH_THUMB
	echo "#define ARM_THUMB" >> $@
	echo "#define ARM_THUMB_1" >> $@
endif

src/disasm.c: arm.irg
	$(GLISS_PREFIX)/gep/gliss-disasm $(ARCH).irg -o $@ -c

src/used_regs.c: $(ARCH).irg nmp/used_regs.nmp
	$(GLISS_PREFIX)/gep/gliss-used-regs $< -e nmp/used_regs.nmp

arm-sim:
	cd sim; make

clean:
	rm -rf $(CLEAN)

distclean:
	rm -Rf $(DISTCLEAN) arm.irg arm.out

config: config.mk

config.mk:
	cp config.mk.in config.mk
	echo "Created config.mk. Edit it for configuration."

