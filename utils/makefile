CFLAGS=-fPIC -DLIBMAKE
LDFLAGS=-shared -Wl,-soname,data_structures
SRCS:=$(wildcard src/*.c) include/debug.h

../shared/utils.so:
	gcc $(SRCS) $(LDFLAGS) $(CFLAGS) $< -o $@