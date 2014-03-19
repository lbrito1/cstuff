#include "graph.c"
#include "../data_structures/heap.c"
 
int* dijkstra(graph* g, int from, int to)
{
      int nv = g->v_counter;
      
      int* dist         = malloc(sizeof(int)*nv);
      int* previous     = malloc(sizeof(int)*nv);
      
      heap* minheap = new_heap(nv, ORD_ASC, compare_kv);
      
      dist[from] = 0;
            
      int i;
      for (i=0; i<nv; i++)
      {
            if (i!=from) 
            {
                  dist[i] = INT_MAX;
                  previous[i] = -1;
            }
            int* x = malloc(sizeof(int));
            *x = i;
            kv* a = new_kv(dist[i], (void*)x);
            push(minheap,a);
      }
      
      kv* min = NULL;
      while ((min = pop(minheap)) != NULL)
      {
            int u = *((int*) min->v);
            element* head = g->adj_list[u]->head;
            
            while ((head = head->next) != NULL) 
            {
                  int v = *(int*) ((kv*) head->data)->v;
                  edge* uv = get_edge(g, u, v);
            
                  int ndist = dist[u] + uv->cost;
                  
                  if ((ndist>=0) && (ndist<dist[v])) //relax edge
                  {
                        dist[v] = ndist;
                        previous[v] = u;
                        min->k = dist[v];
                        push(minheap,min);
                  }
            }
      }
      
      return previous;
}

int main()
{
      graph* g = build_complete_graph(25);
      int* x = dijkstra(g,10,20);
      int i;
      for (i=0; i<g->v_counter; i++) printf("\n%d\t%d",i,x[i]);
            
            
      
      return 0;
}
