#include <limits.h>
#include "../../utils/include/debug.h"
#include "../../data_structures/include/heap.h"
#include "../include/graph_defs.h"
#include "../include/al_graph.h"

int* dijkstra(graph* g, int from, int to, int* dist)
{
      int nv = get_nv(g); 
      
      int should_scrap_dist = FALSE;

      if (!dist) {
            dist = malloc(sizeof(int)*nv);
            should_scrap_dist = TRUE;
      }
      int* previous     = malloc(sizeof(int)*nv);
      heap* minheap = new_heap(nv, ORD_ASC, compare_kv);
      
      int i;
      for (i=0; i<nv; i++)
      {
            dist[i] = INT_MAX;
            previous[i] = -1;
            kv* val = new_kv(i, (void*) &dist[i], compare_integer);
            push_heap(minheap, val);
            
            #ifdef _DEBUG
                  edge_iter* itd = new_edge_it(g,get_vertex(g,i));
                  edge* next = NULL;
                  while ((next = next_edge(itd)) != NULL) if (next->to) DBG("\n%d\tE(%lu,%lu) = %d",itd->idx,next->from->id,next->to->id,next->cost ) ;
                  free(itd);
            #endif
      }
     
      
      dist[from]        = 0;
      previous[from]    = -1;
      
      kv* min = NULL; int found = FALSE;
      while (((min = pop_heap(minheap)) != NULL) && !found)
      {
            int u = min->k;
            visit_vert(g,u);
            
            edge_iter* it = new_edge_it(g,get_vertex(g,u));
            edge* next = NULL;
            
            
            DBG("\n\n\nNEIGHBORS OF v[%d]:\n--------------------",u);
            while ((next = next_edge(it)) != NULL)
            {
                  if (!next->to) return FALSE;
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
                        if (candidate !=NULL) update_heap(minheap, vpos);
                  }
            }
            free(it);
            
            if (u==to) found = TRUE;
      }

      //cleanup
      delete_heap(minheap);
      if (should_scrap_dist) free(dist);
      
      return previous;
}
