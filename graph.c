#include "vector.c"


typedef struct graph {
      vector* nodes;
      vector* edges;
      unsigned long n_nodes;
      unsigned long n_edges;
} graph;

typedef struct node {
      int id;
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

int main()
{
      int x = 11;
      node* n = new_node(&x);
      graph* g = new_graph(5, sizeof(int), compare_integer);
      printf("%d",g->edges->used);
      add_node(g,n);
      remove_node(g,n);
      return 0;
}