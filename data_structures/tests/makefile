CFLAGS=-D_DEBUG -lm -g
CFILES=../../utils/include/debug.h ../../utils/src/burgergfx.c ../../utils/src/comparators.c ../src/linked_list.c ../src/binary_tree.c ../src/binary_search_tree.c ../src/avl_tree.c ../src/red_black_tree.c ../src/heap.c ../src/vector.c
TARGET=bin/$@.out
SRC=./src/$@.c

TESTS=$(CC) $(CFILES) $(SRC) -o $(TARGET) $(CFLAGS)

linked_list_test:
	$(TESTS)

avl_test:
	$(TESTS)

bst_test:
	$(TESTS)

rb_test:
	$(TESTS)

heap_test:
	$(TESTS)

vector_test:
	$(TESTS)

all: avl_test bst_test rb_test linked_list_test heap_test vector_test