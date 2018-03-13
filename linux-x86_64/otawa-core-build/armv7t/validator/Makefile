CC = gcc
CFLAGS = -g3 -Wall -I../include
LDFLAGS = -L../src -larm

SOURCES = \
	main.c
OBJECTS = $(SOURCES:.c=.o)

all: validator

clean:
	rm -rf $(SOURCES:.c=.o)
	
distclean: clean
	rm -rf validator

validator: $(OBJECTS) ../src/libarm.a
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

