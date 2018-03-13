
CFLAGS=-I../include -I../src -g -O3
LIBADD += $(shell bash ../src/arm-config --libs)

all: arm-disasm

arm-disasm: arm-disasm.o ../src/libarm.a
	$(CC) $(CFLAGS) -o $@ $< $(LIBADD)

clean:
	rm -rf arm-disasm.o

distclean: clean
	rm -rf arm-disasm
