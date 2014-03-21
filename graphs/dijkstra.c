#include <limits.h>
#include "../tests/graph_test.c"
#include "../data_structures/heap.c"

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

#ifdef _DIJKSTRA_MAIN
void print_trace(burger* b, graph* g, int* prev, int orig, int dest)
{
      DBG("\nTRACING FROM %d TO %d:\t",orig,dest);
      int i=dest;
      while ((i != orig) && (i<get_nv(g)))
      {
            DBG("%d, ",i);
            vertex* t = get_vertex(g, i);
            vertex* f = get_vertex(g, prev[i]);
            if ((f!=NULL) && (t!=NULL)) put_line(b, f->x, f->y, t->x, t->y);
            i = prev[i];
      }
}

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
      
      burger* bgfx = create(48,48);
      
      int* d = dijkstra(g,0,-1);
      
      print_graph(g,bgfx);
      
      print_vertex_status(g, bgfx);

      int i;
      DBG("\nPrevious\n===============\n");
      for (i=0; i<g->nv; i++) DBG("\nvert[%d]\t%d",i,d[i]);
      
      free(g);
      free(d);
      g = build_matrix_graph(25);
      
      put_weight(g,1,0,100);
      d = dijkstra(g,0,-1);
      clean_burger(bgfx);
      
      print_graph(g,bgfx);
      
      
      
      DBG("\nPrevious\n===============\n");
      for (i=0; i<g->nv; i++) DBG("\nvert[%d]\t%d",i,d[i]);
      
      clean_burger(bgfx);
      print_trace(bgfx,g,d,0,23);
      //draw_vertex_status(g, bgfx);
      print_burger(bgfx);
      
      return 0;
}
#endif