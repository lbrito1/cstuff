#include "../utils/debug.c"
#include "../tests/graph_test.c"
#include "../data_structures/heap.c"
 
int* dijkstra(graph* g, int from, int to)
{
      int nv = g->nv;
      
      int* dist         = malloc(sizeof(int)*nv);
      int* previous     = malloc(sizeof(int)*nv);
      
      heap* minheap = new_heap(nv, ORD_ASC, compare_kv);
      
      dist[from] = 0;
      previous[from] = -1;
      
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
            
            
            #ifdef _DEBUG
            element* el = g->adj_list[i]->head;
            while ((el=el->next)!=NULL) 
            {
                  edge* ed = (edge*) el->data;
                  DBG("\n%d\tE(%lu,%lu) = %d",i,ed->from->id,ed->to->id,ed->cost ) ;
            }
            #endif
      }
      
      
      kv* min = NULL;
      while ((min = pop(minheap)) != NULL)
      {
            int u = *((int*) min->v);
            visit(g,u);
            
            element* head = g->adj_list[u]->head;
            
            #ifdef _DEBUG
                  DBG("\n\n===========\nChecking v[%d], HEAPSZ=%d\n---------\n",u,minheap->heap_size);
                  DBG("\nNEIGHBORS OF %d:\t",u);
                  while ((head = head->next) != NULL) DBG(" %lu,",((edge*)(head->data))->to->id);
                  DBG("\n");
            #endif
            
            head = g->adj_list[u]->head;            
            while ((head = head->next) != NULL) 
            {
                  int v = ((edge*) (head->data))->to->id;
                  DBG("\nNeighbor %d",v);
                  
                  if (u!=v) {
                  
                        edge* uv = get_edge(g, u, v);
                  
                        int ndist = dist[u] + uv->cost;
                        
                        DBG("\t ndist= %d",ndist);
                        
                        //relax edge
                        if ((ndist>=0) && (ndist<dist[v])) 
                        {
                              DBG("\tprev dist = %d",dist[v]);
                              
                              dist[v] = ndist;
                              previous[v] = u;
                              
                              if (minheap->heap_size>0) 
                              {
                                    kv* v_p = NULL;
                                    for (i=1; i<=minheap->heap_size; i++) 
                                    {
                                          kv* candidate = (kv*) (minheap->array[i]);
                                          
                                          if ( (*(int*) candidate->v) == v ) 
                                          {
                                                DBG("\tFound %d",(*(int*) candidate->v));
                                                v_p = pop_at(minheap, i);
                                                v_p->k = dist[v];
                                                
                                                push(minheap, v_p);
                                                
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

int main()
{
      graph* g = new_graph(10,UNDIRECTED);
      char mydata = '0';
      char mydata2 = '1';
      char mydata3 = '2';
      char mydata4 = '3';
      char mydata5 = '4';
      
      vertex* v0 = add_vertex(g, &mydata);
      vertex* v1 = add_vertex(g, &mydata2);
      vertex* v2 = add_vertex(g, &mydata3);
      vertex* v3 = add_vertex(g, &mydata4);
      vertex* v4 = add_vertex(g, &mydata5);
      
      sendto(v0, 0.9, 0.1);
      sendto(v1, 0.4, 0.9);
      sendto(v2, 0.6, 0.3);
      sendto(v3, 0.7, 0.1);
      sendto(v4, 0.1, 0.3);
      
      add_edge(g, v0, v1, 1);
      add_edge(g, v0, v2, 1);
      add_edge(g, v1, v2, 1);
      add_edge(g, v2, v3, 1);
      add_edge(g, v4, v2, 1);
      add_edge(g, v4, v1, 1);
      
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
