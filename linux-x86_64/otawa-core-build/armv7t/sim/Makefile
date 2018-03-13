CFLAGS=-I../include -I../src -g -O3
LIBADD =  $(shell bash ../src/arm-config --libs)

all: arm-sim

arm-sim: arm-sim.o  ../src/libarm.a
	$(CC) $(CFLAGS) -o $@ $< $(LIBADD)

clean:
	rm -f arm-sim.o

distclean: clean
	rm -f arm-sim
