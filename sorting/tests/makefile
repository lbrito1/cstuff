MKDIR_P = mkdir -p
CFLAGS=-D_DEBUG -lm -g
CFILES=../../utils/include/debug.h ../../utils/src/burgergfx.c ../../utils/src/comparators.c ../../data_structures/src/linked_list.c ../../data_structures/src/heap.c ../../data_structures/src/vector.c ../src/quicksort.c ../src/insertionsort.c ../src/mergesort.c
TARGET=bin/$@.out
SRC=./src/$@.c

TESTS=$(CC) $(CFILES) $(SRC) -o $(TARGET) $(CFLAGS) 

insertion_sort_test:
	$(MKDIR_P) bin
	$(TESTS)

quicksort_test:
	$(MKDIR_P) bin
	$(TESTS)

mergesort_test:
	$(MKDIR_P) bin
	$(TESTS)

all: insertion_sort_test quicksort_test mergesort_test