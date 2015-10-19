CFLAGS=-fPIC -DPYLIB
LDFLAGS=-shared -Wl,-soname,sorting
SRCS:=$(wildcard src/*.c)
PYDEP=-I/usr/include/python2.7 -lpython2.7
CFILES=../data_structures/src/heap.c ../data_structures/src/linked_list.c

../shared/sorting.so:
	gcc $(CFILES) $(SRCS) $(LDFLAGS) $(PYDEP) $(CFLAGS) $< -o $@
