#ifndef GRAPH_ADJ_H
#define GRAPH_ADJ_H

#include <limits.h>

#include "graph_ve.h"
#include "../../data_structures/include/linked_list.h"

typedef struct graph
{
      vertex** vertices;
      int directed;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long v_counter;
      linked_list** adj_list;
      void (*printvert) (void*);
} graph;

graph* new_graph(int n_vertices, int directed);

edge* get_edge(graph* g, int from, int to);

vertex* add_vertex(graph* g, void* data) ;

vertex* get_vertex(graph* g, int idx);

void add_edge(graph* g, vertex* vf, vertex* vt, int cost);

int get_nv(graph* g);

#endif