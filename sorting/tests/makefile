CFLAGS=-D_DEBUG -lm -g
CFILES=../../utils/include/debug.h ../../utils/src/burgergfx.c ../../utils/src/comparators.c ../../data_structures/src/linked_list.c ../../data_structures/src/heap.c ../../data_structures/src/vector.c ../src/quicksort.c ../src/insertionsort.c ../src/mergesort.c
TARGET=bin/$@.out
SRC=./src/$@.c

TESTS=$(CC) $(CFILES) $(SRC) -o $(TARGET) $(CFLAGS) 

insertion_sort_test:
	$(TESTS)

quicksort_test:
	$(TESTS)

mergesort_test:
	$(TESTS)

all: insertion_sort_test quicksort_test mergesort_test