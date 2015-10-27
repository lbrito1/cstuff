CFLAGS=-fPIC -DPYLIB
LDFLAGS=-shared -Wl,-soname,graphs
PYDEP=-I/usr/include/python2.7 -lpython2.7
SRCS:=$(wildcard src/*.c)

../shared/graphs.so:
	gcc $(SRCS) $(LDFLAGS) $(PYDEP) $(CFLAGS) $< -o $@
