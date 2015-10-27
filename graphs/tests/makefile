MKDIR_P = mkdir -p
CFLAGS=-D_DEBUG -lm -g
CFILES=../../utils/include/debug.h ../../utils/src/burgergfx.c ../../utils/src/comparators.c ../../data_structures/src/linked_list.c ../../data_structures/src/heap.c
GRAPHFILES:=$(wildcard ../src/*.c)
TARGET=bin/$@.out
SRC=./src/$@.c
TESTS=$(CC) $(GRAPHFILES) $(CFILES) $(SRC) -o $(TARGET) $(CFLAGS)

graph_test:
	$(MKDIR_P) bin
	$(TESTS)

dijkstra_test:
	$(MKDIR_P) bin
	$(TESTS)

all: graph_test dijkstra_test