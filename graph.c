#include "vector.c"

static int REMOVED = -1;
static int UNMARKED = 0;
static int VISITED = 1;

typedef struct graph {
      vector* nodes;
      vector* edges;
      unsigned long n_nodes;
      unsigned long n_edges;
} graph;

typedef struct node {
      int id;
      int status;
      void* data;
} node;

typedef struct edge {
      int id;
      node *to, *from;
      double cost;
} edge;

int compare_node(void* n1, void* n2) 
{
      return ((((node*) n1)->id) == (((node*) n2)->id));
}

int compare_edge(void* e1, void* e2) 
{
      return ((((edge*) e1)->id) == (((edge*) e2)->id));
}

graph* new_graph(unsigned size, size_t type_size, int (*comparator) (void*,void*))
{
      graph* g = malloc(sizeof(graph*));
      g->n_nodes = 0;
      g->n_edges = 0;
      g->nodes = new_vector(size, sizeof(node*), compare_node);
      g->edges = new_vector(size, sizeof(edge*), compare_edge);
      return g;
}

node* new_node(void* data)
{
      node* n = malloc(sizeof(node));
      n->data = data;
      n->id = -1;
      n->status = 0;
}

void add_node(graph* g, node* n)
{
      n->id = g->n_nodes++;
      add(g->nodes, n);
}

int remove_edge(graph* g, edge* e)
{
      return delete(g->edges, e);
}

int remove_node(graph* g, node* n)
{
      n->status = REMOVED;

      // remove edges leading to and from node
      int i;
      for (i=0; i<g->edges->used; i++)
      {
            node* to = ((edge*) (g->edges->array[i]))->to;
            node* from = ((edge*) (g->edges->array[i]))->to;
            if (compare_node(n, to) | compare_node(n,from))
                  remove_edge(g, g->edges->array[i]);
      }
      
      return 0;
}

edge* new_edge(node* from, node* to, double cost)
{
      edge* e = malloc(sizeof(edge));
      e->from = from;
      e->to = to;
      e->cost = cost;
      e->id = -1;
}

int add_edge(graph* g, edge* e)
{
      e->id = g->n_edges++;
      add(g->edges, e);
}

int main()
{
      static int x = 11;
      static int y = 9;
      node* n = new_node(&x);
      node* m = new_node(&y);
      edge* e = new_edge(n, m, 1.0);
      graph* g = new_graph(5, sizeof(int), compare_integer);
      add_node(g,n);
      add_node(g,m);
      add_edge(g,e);
      return 0;
}