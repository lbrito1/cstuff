#include <limits.h>

#include "../data_structures/linked_list.c"

#define DIRECTED 0
#define UNDIRECTED 1

#define UNMARKED 0
#define MARKED 1

typedef struct vertex
{
      unsigned long id;
      int status;
      double x,y;
      void* data;
} vertex;

typedef struct edge
{
      vertex* from, *to;
      int cost;
} edge;

typedef struct al_graph
{
      vertex** vertices;
      int directed;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long nv;
      linked_list** adj_list;
      void (*printvert) (void*);
} al_graph;

int compare_v(void* v1, void* v2) 
{
      if ((v1 == NULL) | (v2 == NULL)) return -1;
      return ((((vertex*) v1)->id) == (((vertex*) v2)->id));
}

int compare_e(void* e1, void* e2)
{
      if ((e1 == NULL) | (e2 == NULL)) return -1;
      return  (((edge*)e1)->from->id) == (((edge*)e2)->from->id)
      && (((edge*)e1)->to->id) == (((edge*)e2)->to->id);
}

int visit(al_graph* g, int vid) 
{
      if (g->vertices[vid]->status == UNMARKED) 
      {
            g->vertices[vid]->status = MARKED;
            return TRUE;
      }
      return FALSE;
}

al_graph* new_al_graph(int n_vertices, int directed)
{
      al_graph* g_p = malloc(sizeof(al_graph));
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

vertex* new_vertex(unsigned long id, void* data)
{
      vertex* v = malloc(sizeof(vertex));
      v->data = data;
      v->status = UNMARKED;
      v->id = id;
      v->x = 0.0;
      v->y = 0.0;
      return v;
}

edge* new_edge(vertex* from, vertex* to, int cost)
{
      edge* e = malloc(sizeof(edge));
      e->from = from;
      e->to = to;
      e->cost = cost;
      return e;
}

edge* get_edge(al_graph* g, int from, int to)
{
      element* e = g->adj_list[from]->head;
      while ((e=e->next) != NULL) if (((((edge*) e->data)->to)->id) == to) return ((edge*) e->data);
      return NULL;
}

vertex* add_vertex(al_graph* g, void* data) 
{
      vertex* v;
      int pos = g->nv;
      if (pos < g->max_vertices) 
      {
            v = (g->vertices[pos] = new_vertex(pos, data));
            add((g->adj_list[pos]), NULL);      //prepare adjlist
            g->nv++;
      }
      else
      {
            return NULL;
      }
      
      return v;
}


void add_edge(al_graph* g, vertex* vf, vertex* vt, int cost)
{
      add((g->adj_list[vf->id]), new_edge(vf,vt,cost));
      if (g->directed == UNDIRECTED) add((g->adj_list[vt->id]), new_edge(vt,vf,cost)); 
}

void print_vertices(al_graph* g)
{
      int i=0;
      printf("\nCurrently %lu elements",g->nv);
      printf("\n[ID]\tDATA\n=================");
      for (;i<g->nv;i++) printf("\n[%lu]\t", g->vertices[i]->id);
}
/*
int main()
{
      al_graph* g = new_al_graph(10);
      char* mydata = "Test";
      char* mydata2 = "Test2";
      char* mydata3 = "Test3";
      
      vertex* v1 = add_vertex(g, mydata);
      vertex* v2 = add_vertex(g, mydata2);
      vertex* v3 = add_vertex(g, mydata3);
      
      add_edge(g, v1, v2);
      
      print_vertices(g);
      
      return 0;
}
*/