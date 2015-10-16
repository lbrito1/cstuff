CFLAGS=-fPIC -DLIBMAKE
LDFLAGS=-shared -Wl,-soname,sorting
SRCS:=$(wildcard src/*.c)
CFILES=../data_structures/src/heap.c ../data_structures/src/linked_list.c

../shared/sorting.so:
	gcc $(CFILES) $(SRCS) $(LDFLAGS) $(CFLAGS) $< -o $@