#include "../graphs/graph.c"
#include "../utils/burgergfx.c"
#include "../utils/debug.c"

void sendto(vertex* v, double x, double y)
{
      v->x = x; v->y = y;
}

void draw_vertices(graph* g, burger* b)
{
      int i;
      for (i=0; i<g->nv; i++)
      {
            vertex* v = g->vertices[i];
            put_burger(b, v->x, v->y, *((char*) v->data));
      }
}

void draw_vertex_status(graph* g, burger* b)
{
      int i;
      for (i=0; i<g->nv; i++)
      {
            vertex* v = g->vertices[i];
            char c = v->status == UNMARKED ? 'u' : 'M';
            put_burger(b, v->x, v->y, c);
      }
}

void draw_edges(graph* g, burger* b)
{
      int i;
      for (i=0; i<g->nv; i++)
      {
            element* head = g->adj_list[i]->head;
             while (head != NULL) 
             {
                  vertex* from = g->vertices[i];
                  if (from != NULL) 
                  {
                        void* dptr = head->data;
                        if (dptr != NULL) 
                        {
                              edge* e = (edge*) dptr;
                              vertex* to = e->to;
                              if (to != NULL && to!=from) 
                              {
                                    #ifdef _DEBUG
                                          printf("\n%d\t(%lu,%lu)\t@(%f,%f, %f,%f)",i,from->id,to->id,from->x,from->y,to->x,to->y);
                                    #endif
                                    put_line(b, from->x, from->y, to->x, to->y);
                              }
                        }
                  }
                  head = head->next;
            }
      }
}

void print_graph(graph* g, burger* bgfx)
{
      clean_burger(bgfx);
      draw_edges(g, bgfx);
      draw_vertices(g, bgfx);
      print_burger(bgfx);
}

void print_vertex_status(graph* g, burger* bgfx)
{
      clean_burger(bgfx);
      draw_vertex_status(g, bgfx);
      print_burger(bgfx);
}

#ifdef _GRAPH_TEST_MAIN
int main()
{
      graph* g = new_graph(10, UNDIRECTED);
      char mydata = 'A';
      char mydata2 = 'B';
      char mydata3 = 'C';
      char mydata4 = 'D';
      char mydata5 = 'F';
      
      vertex* v1 = add_vertex(g, &mydata);
      vertex* v2 = add_vertex(g, &mydata2);
      vertex* v3 = add_vertex(g, &mydata3);
      vertex* v4 = add_vertex(g, &mydata4);
      vertex* v5 = add_vertex(g, &mydata5);
      
      sendto(v1, 0.9, 0.1);
      sendto(v2, 0.4, 0.9);
      sendto(v3, 0.6, 0.3);
      sendto(v4, 0.7, 0.1);
      sendto(v5, 0.1, 0.3);
      
      add_edge(g, v1, v2, 1);
      add_edge(g, v1, v3, 1);
      add_edge(g, v2, v3, 1);
      add_edge(g, v3, v4, 1);
      add_edge(g, v5, v3, 1);
      add_edge(g, v5, v2, 1);
      
      edge_iter* it = new_edge_it(g,v1);
      edge* next = NULL;
      
      while ((next = next_edge(it)) != NULL) DBG("\n%d\tE(%lu,%lu) = %d",it->idx,next->from->id,next->to->id,next->cost ) ;
      
      
      // testing
      
      burger* bgfx = create(32,32);
      
      print_graph(g,bgfx);
      
      graph* cg = build_complete_graph(100);
      
      print_vertex_status(cg, bgfx);
      
      return 0;
}
#endif