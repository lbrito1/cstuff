CFLAGS=-fPIC -DPYLIB
LDFLAGS=-shared -Wl,-soname,data_structures
PYDEP=-I/usr/include/python2.7 -lpython2.7
SRCS:=$(wildcard src/*.c)

all: ../shared/data_structures.so
	rm -f $<
	gcc $(SRCS) $(LDFLAGS) $(PYDEP) $(CFLAGS) -o $<

.PHONY: all