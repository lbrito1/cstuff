#include "../utils/debug.c"
#include "../tests/graph_test.c"
#include "../data_structures/heap.c"
 
int* dijkstra(graph* g, int from, int to)
{
      int nv = g->nv;
      
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
      
      kv* min = NULL;
      while ((min = pop(minheap)) != NULL)
      {
            int u = min->k;
            visit(g->vertices[u]);
            
            edge_iter* it = new_edge_it(g,get_vertex(g,u));
            edge* next = NULL;
            
            
            DBG("\n\n\nNEIGHBORS OF v[%d]:\n--------------------",u);
            while ((next = next_edge(it)) != NULL)
            {
                  int v = next->to->id;
                  DBG("\nv[%d]",v);
                  
                  if (u!=v) {
                  
                        edge* uv = get_edge(g, u, v);
                  
                        int ndist = dist[u] + uv->cost;
                        
                        DBG("\t optimal dist = %d",ndist);
                        
                        //relax edge
                        if ((ndist>=0) && (ndist<dist[v])) 
                        {
                              DBG("\tprev dist = %d",dist[v]);
                              
                              dist[v] = ndist;
                              previous[v] = u;
                              
                              if (minheap->heap_size>0) 
                              {
                                    kv* candidate = get_kv(minheap->array, minheap->heap_size, v);
                                    if (candidate !=NULL)
                                    for (i=1; i<=minheap->heap_size; i++) 
                                    {
                                          //(kv*) (minheap->array[i]);
                                          
                                          if ( (candidate->k) == v ) 
                                          {
                                                DBG("\tFound %d",(*(int*) candidate->v));
                                                update(minheap, i);
                                                
                                                i = minheap->heap_size+2;
                                          }
                                    }
                              }
                        }
                  }
            }
      }
      
      return previous;
}

#ifdef _DIJKSTRA_MAIN
int main()
{
      graph* g = new_graph(10,UNDIRECTED);
      char mydata = '0';
      char mydata2 = '1';
      char mydata3 = '2';
      char mydata4 = '3';
      char mydata5 = '4';
      char mydata6 = '5';
      
      vertex* v0 = add_vertex(g, &mydata);
      vertex* v1 = add_vertex(g, &mydata2);
      vertex* v2 = add_vertex(g, &mydata3);
      vertex* v3 = add_vertex(g, &mydata4);
      vertex* v4 = add_vertex(g, &mydata5);
      vertex* v5 = add_vertex(g, &mydata6);
      
      sendto(v0, 0.9, 0.1);
      sendto(v1, 0.4, 0.9);
      sendto(v2, 0.6, 0.3);
      sendto(v3, 0.7, 0.1);
      sendto(v4, 0.1, 0.3);
      sendto(v5, 0.2, 0.8);
      
      add_edge(g, v0, v1, 2);
      add_edge(g, v0, v2, 3);
      add_edge(g, v1, v2, 1);
      add_edge(g, v2, v3, 1);
      add_edge(g, v4, v2, 1);
      add_edge(g, v4, v1, 1);
      add_edge(g, v5, v4, 1);
      // testing
      
      burger* bgfx = create(32,32);
      
      int* d = dijkstra(g,0,2);
      
      print_graph(g,bgfx);
      
      print_vertex_status(g, bgfx);

      DBG("\nPrevious\n===============\n");
      int i;
      for (i=0; i<g->nv; i++)
      {
            DBG("\nvert[%d]\t%d",i,d[i]);
      }
      
      return 0;
}
#endif