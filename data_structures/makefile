CFLAGS=-fPIC -DLIBMAKE
LDFLAGS=-shared -Wl,-soname,data_structures
SRCS:=$(wildcard src/*.c)

../shared/data_structures.so:
	gcc $(SRCS) $(LDFLAGS) $(CFLAGS) $< -o $@