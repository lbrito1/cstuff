#include <limits.h>
#include "../tests/graph_test.c"
#include "../data_structures/include/heap.h"

int* dijkstra(graph* g, int from, int to)
{
      int nv = get_nv(g); 
      
      int* dist         = malloc(sizeof(int)*nv);
      int* previous     = malloc(sizeof(int)*nv);
      heap* minheap = new_heap(nv, ORD_ASC, compare_kv);
      
      int i;
      for (i=0; i<nv; i++)
      {
            dist[i] = INT_MAX;
            previous[i] = -1;
            kv* val = new_kv(i, (void*) &dist[i], compare_integer);
            push(minheap, val);
            
            #ifdef _DEBUG
                  edge_iter* itd = new_edge_it(g,get_vertex(g,i));
                  edge* next = NULL;
                  while ((next = next_edge(itd)) != NULL) DBG("\n%d\tE(%lu,%lu) = %d",itd->idx,next->from->id,next->to->id,next->cost ) ;
                  free(itd);
            #endif
      }
     
      
      dist[from]        = 0;
      previous[from]    = -1;
      
      kv* min = NULL; int found = FALSE;
      while (((min = pop(minheap)) != NULL) && !found)
      {
            int u = min->k;
            visit_vert(g,u);
            
            edge_iter* it = new_edge_it(g,get_vertex(g,u));
            edge* next = NULL;
            
            
            DBG("\n\n\nNEIGHBORS OF v[%d]:\n--------------------",u);
            while ((next = next_edge(it)) != NULL)
            {
                  int v = next->to->id;
                  int ndist = dist[u] + next->cost;
                  DBG("\nv[%d]",v);
                  DBG("\t optimal dist = %d",ndist);
                  
                  //relax edge
                  if ((ndist>=0) && (ndist<dist[v]) && (u!=v)) 
                  {
                        DBG("\tprev dist = %d",dist[v]);
                        
                        dist[v]     = ndist;
                        previous[v] = u;
                        
                        int vpos = -1;
                        kv* candidate = get_kv(minheap->array, minheap->heap_size, v, &vpos);
                        if (candidate !=NULL) update(minheap, vpos);
                  }
            }
            
            if (u==to) found = TRUE;
      }
      
      return previous;
}
