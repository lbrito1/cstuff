#include "../include/graph_defs.h"
#include "../include/graph_adj.h"
#include <limits.h>

#include "../../data_structures/include/linked_list.h"

graph* new_graph(int n_vertices, int directed)
{
      graph* g_p = malloc(sizeof(graph));
      g_p->directed = directed;
      g_p->max_vertices = n_vertices;
      g_p->vertices = malloc(sizeof(vertex*)*g_p->max_vertices);
      g_p->v_counter = 0;
      g_p->n_edges = 0;
      g_p->adj_list = malloc(sizeof(linked_list*)*g_p->max_vertices);
      int i=0;
      for (;i<g_p->max_vertices;i++) g_p->adj_list[i] = new_list(compare_e, sizeof(edge));
      return g_p;
}

edge* get_edge(graph* g, int from, int to)
{
      element* e = g->adj_list[from]->head;
      while ((e=e->next) != NULL) if (((((edge*) e->data)->to)->id) == to) return ((edge*) e->data);
      return NULL;
}

vertex* add_vertex(graph* g, void* data) 
{
      vertex* v;
      int pos = g->v_counter;
      if (pos < g->max_vertices) 
      {
            v = (g->vertices[pos] = new_vertex(pos, data));
            g->v_counter++;
      }
      else
      {
            return NULL;
      }
      
      return v;
}

vertex* get_vertex(graph* g, int idx)
{
      if (idx>get_nv(g)) return NULL;
      return g->vertices[idx];
}

void add_edge(graph* g, vertex* vf, vertex* vt, int cost)
{
      #ifdef _DEBUG
      // if (g->directed == UNDIRECTED) printf("\nAdding UNDIRECTED edges");
      #endif

      edge* e_fro = new_edge(vf,vt,cost), *e_to;
      add_ll((g->adj_list[vf->id]), e_fro);
      if (g->directed == UNDIRECTED) {
            e_to = new_edge(vt,vf,cost);
            add_ll((g->adj_list[vt->id]), e_to); 
      }

      #ifdef _DEBUG
      // if (g->directed == UNDIRECTED) {
      //       printf("\nAdded %p and %p", (void*) e_fro, (void*) e_to);
      // }
      #endif
}

int get_nv(graph* g)
{
      return g->v_counter;
}
