CC=arm-none-eabi-gcc
OBJDUMP=arm-none-eabi-objdump

OTAWA=owcet
SIM=ogensim
SIM2TIME=../../../../../../scripts/ogensim2times.py
TIMER=/usr/bin/time -v
GRAPH_DIR=graphs

SRCS=matmult.c
EXE=main.elf
ASM=$(EXE:.elf=.asm)
OBJS=$(SRCS:.c=.o)
FFX=$(EXE).ffx
FF=$(EXE:.elf=.ff)
CFG=cfg.xml
FUNC=Multiply

CFLAGS=-O0 -g --std=gnu99
CFLAGS+=--specs=nosys.specs -march=armv5

LDFLAGS=-gdwarf-4
LDFLAGS+=-lm

OWCET_SCRIPT=owcet-script.osx
OTAWA_PATH=$(shell otawa-config --data)
#OTAWA_FLAGS=-s $(OTAWA_PATH)/share/Otawa/scripts/generic.osx
OTAWA_FLAGS=-s $(OWCET_SCRIPT)
OTAWA_FLAGS+=--log=bb -v
OTAWA_FLAGS+=-p pipeline=otawa-pipelineconfig.xml
OTAWA_FLAGS+=-p cache=otawa-cacheconfig.xml
OTAWA_FLAGS+=-p graphdir=$(GRAPH_DIR)
SIM_FLAGS+=-c otawa-cacheconfig.xml
#SIM_FLAGS+=--traceCache
SIM_FLAGS+=-p otawa-pipelineconfig.xml
SIM_FLAGS+=-m otawa-memoryconfig.xml
SIM_FLAGS+=-vl 0
SIM_FLAGS+=--dumpCfg sim.cfg --dumpFcn $(FUNC)
SIM_FLAGS+=--clearCacheOn $(FUNC)
SIM_FLAGS+=--inlineCalls  # so that WCET output and sim concur

all: $(EXE) wcet.log sim.log times.log

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(ASM): $(EXE)
	$(OBJDUMP) -Dl $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FF): $(EXE)
	mkff $(EXE) > $@
	echo "Please edit file $@ manually"

$(FFX): $(SRCS)
	orange $^ -- $(FUNC) -o $@

$(CFG): $(EXE)
	dumpcfg --all -x $^ > $@

$(JSON): $(CFG)
	$(OTAWA2JSON) --xml $< --out $@

wcet.log: $(EXE) $(FFX) $(OWCET_SCRIPT)
	mkdir -p $(GRAPH_DIR)
	$(TIMER) $(OTAWA) $(OTAWA_FLAGS) $(EXE) $(FUNC) -f $(FFX) 2>&1 | tee $@

sim.log: $(EXE)
	$(SIM) $(SIM_FLAGS) $< 2>&1 | tee sim1.log
	mv sim1.log $@

times.log: sim.log $(EXE)
	$(SIM2TIME) -e $(EXE) -t sim.log --pretty --coverage | tee $@

clean:
	rm -f *.o $(EXE) $(FFX) $(FF) wcet.log
	rm -f sim.log times.log *.cfg cfg.xml
	rm -f main.asm
