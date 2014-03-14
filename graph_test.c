#include "graph_adj.c"
#include "burgergfx.c"

void sendto(vertex* v, double x, double y)
{
      v->x = x; v->y = y;
}

void draw_vertices(graph* g, burger* b)
{
      int i;
      for (i=0; i<g->v_counter; i++)
      {
            vertex* v = g->vertices[i];
            put_burger(b, v->x, v->y, *((char*) v->data));
      }
}

void draw_edges(graph* g, burger* b)
{
       int i;
      for (i=0; i<g->v_counter; i++)
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
                              vertex* to = (vertex*) dptr;
                              if (to != NULL) put_line(b, from->x, from->y, to->x, to->y);
                        }
                  }
                  head = head->next;
            }
      }
}

int main()
{
      graph* g = new_graph(10);
      char mydata = 'A';
      char mydata2 = 'B';
      char mydata3 = 'C';
      
      vertex* v1 = add_vertex(g, &mydata);
      vertex* v2 = add_vertex(g, &mydata2);
      vertex* v3 = add_vertex(g, &mydata3);
      
      sendto(v1, 0.1, 0.1);
      sendto(v2, 0.4, 0.9);
      sendto(v3, 0.6, 0.3);
      
      add_edge(g, v1, v2);
      
      // testing
      
      burger* bgfx = create(32,32);
      
      clean_burger(bgfx);

      draw_edges(g, bgfx);
      draw_vertices(g, bgfx);
      
      
      print_burger(bgfx);
      
      return 0;
}