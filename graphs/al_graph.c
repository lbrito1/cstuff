#include <limits.h>
#include "../data_structures/linked_list.c"
#include "graph_ve.c"

#define DIRECTED 0
#define UNDIRECTED 1

#define UNMARKED 0
#define MARKED 1

typedef struct graph
{
      vertex** vertices;
      int directed;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long nv;
      linked_list** adj_list;
      void (*printvert) (void*);
} graph;

typedef struct edge_iter
{
      graph* g;
      vertex* origin;
      element* head;
      int idx, length;
} edge_iter;

graph* new_graph(int n_vertices, int directed)
{
      graph* g_p = malloc(sizeof(graph));
      g_p->directed = directed;
      g_p->max_vertices = n_vertices;
      g_p->vertices = malloc(sizeof(vertex*)*g_p->max_vertices); 
      g_p->nv = 0;
      g_p->n_edges = 0;
      g_p->adj_list = malloc(sizeof(linked_list*)*g_p->max_vertices);
      int i=0;
      for (;i<g_p->max_vertices;i++) g_p->adj_list[i] = new_list(compare_e);
      return g_p;
}

edge_iter* new_edge_it(graph* g, vertex* from)
{
      printf("x");
      edge_iter* it = malloc(sizeof(edge_iter));
      it->g = g;
      it->origin = from;
      it->head = g->adj_list[from->id]->head->next;
      printf("y");
      it->idx = 0;
      it->length = g->adj_list[from->id]->size;
      return it;
}

edge* next_edge(edge_iter* it)
{
      if (++it->idx < it->length)
      {
            edge* e = (edge*) it->head->data;
            it->head = it->head->next;
            return e;
      }
      else return NULL;
}

edge* get_edge(graph* g, int from, int to)
{
      element* e = g->adj_list[from]->head;
      while ((e=e->next) != NULL) if (((((edge*) e->data)->to)->id) == to) return ((edge*) e->data);
      return NULL;
}

vertex* get_vertex(graph* g, int idx)
{
      if (idx>g->nv) return NULL;
      return g->vertices[idx];
}

vertex* add_vertex(graph* g, void* data) 
{
      vertex* v;
      int pos = g->nv;
      if (pos < g->max_vertices) 
      {
            v = (g->vertices[pos] = new_vertex(pos, data));
            add((g->adj_list[pos]), NULL);      //prepare adjlist
            g->nv++;
      }
      else return NULL;
      
      return v;
}

void add_edge(graph* g, vertex* vf, vertex* vt, int cost)
{
      add((g->adj_list[vf->id]), new_edge(vf,vt,cost));
      if (g->directed == UNDIRECTED) add((g->adj_list[vt->id]), new_edge(vt,vf,cost)); 
}

