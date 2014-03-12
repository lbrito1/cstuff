#include "linked_list.c"

#define DIRECTED 0
#define UNDIRECTED 1

#define UNMARKED 0
#define MARKED 1

typedef struct vertex
{
      int id;
      int status;
      void* data;
} vertex;

typedef struct graph
{
      vertex** vertices;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long v_counter;
      void (*printvert) (void*);
} graph;

graph* new_graph(int n_vertices)
{
      graph* g_p = malloc(sizeof(graph));
      g_p->max_vertices = n_vertices;
      g_p->vertices = malloc(sizeof(vertex*)*g_p->max_vertices);
      g_p->v_counter = 0;
      g_p->n_edges = 0;
}

void add_vertex(graph* g, void* data) 
{
      if (g->v_counter < g->max_vertices) 
      {
            vertex* v_p = g->vertices[g->v_counter];
            v_p = malloc(sizeof(vertex));
            v_p->data = data;
            v_p->status = UNMARKED;
            v_p->id = g->v_counter;
            g->v_counter++;
      }
      else
      {
            // grow/error
      }
}

//    tests

void print_vertices(graph* g)
{
      int i=0;
      printf("\nCurrently %d elements",g->v_counter);
      printf("\n[ID]\tDATA\n=================");
      for (;i<g->v_counter;i++) printf("\n[%lu]\t", g->vertices[i]->id);
}

int main()
{
      graph* g = new_graph(10);
      char* mydata = "Test";
      add_vertex(g, mydata);
      
      print_vertices(g);
      
      return 0;
}
