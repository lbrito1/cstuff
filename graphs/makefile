CFLAGS=-fPIC -DPYLIB
LDFLAGS=-shared -Wl,-soname,graphs
PYDEP=-I/usr/include/python2.7 -lpython2.7
CFILES=../utils/src/comparators.c ../utils/include/debug.h ../utils/src/burgergfx.c ../data_structures/src/heap.c ../data_structures/src/linked_list.c
SRCS:=$(wildcard src/*.c)

../shared/graphs.so:
	gcc $(CFILES) $(SRCS) $(LDFLAGS) $(PYDEP) $(CFLAGS) $< -o $@
