#include "linked_list.c"

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

typedef struct graph
{
      vertex** vertices;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long v_counter;
      linked_list** adj_list;
      void (*printvert) (void*);
} graph;

int compare_v(void* v1, void* v2) 
{
      return ((((vertex*) v1)->id) == (((vertex*) v2)->id));
}

graph* new_graph(int n_vertices)
{
      graph* g_p = malloc(sizeof(graph));
      g_p->max_vertices = n_vertices;
      g_p->vertices = malloc(sizeof(vertex*)*g_p->max_vertices);
      g_p->v_counter = 0;
      g_p->n_edges = 0;
      g_p->adj_list = malloc(sizeof(linked_list*)*g_p->max_vertices);
      int i=0;
      for (;i<g_p->max_vertices;i++) g_p->adj_list[i] = new_list(compare_v);
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

vertex* add_vertex(graph* g, void* data) 
{
      vertex* v;
      int pos = g->v_counter;
      if (pos < g->max_vertices) 
      {
            v = (g->vertices[pos] = new_vertex(pos, data));
            
            //prepare adjlist
            add((g->adj_list[pos]), NULL);
            
            g->v_counter++;
      }
      else
      {
            // grow/error
      }
      
      return v;
}


void add_edge(graph* g, vertex* vf, vertex* vt)
{
      add((g->adj_list[vf->id]), vt);
}

//    tests

void print_vertices(graph* g)
{
      int i=0;
      printf("\nCurrently %d elements",g->v_counter);
      printf("\n[ID]\tDATA\n=================");
      for (;i<g->v_counter;i++) printf("\n[%lu]\t", g->vertices[i]->id);
}
/*
int main()
{
      graph* g = new_graph(10);
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