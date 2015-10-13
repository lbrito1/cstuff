CFLAGS=-fPIC -DLIBMAKE
LDFLAGS=-shared -Wl,-soname,sorts
SRCS=quicksort.c mergesort.c heapsort.c insertion.c

../shared/sorts.so:
	gcc $(SRCS) $(LDFLAGS) $(CFLAGS) $< -o $@ -Iutils

