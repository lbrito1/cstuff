CFLAGS=-fPIC -DLIBMAKE
LDFLAGS=-shared -Wl,-soname,sorting
SRCS:=$(wildcard src/*.c)

../shared/sorting.so:
	gcc $(SRCS) $(LDFLAGS) $(CFLAGS) $< -o $@