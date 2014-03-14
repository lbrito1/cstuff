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

void print_graph(graph* g, burger* bgfx)
{
      clean_burger(bgfx);
      draw_edges(g, bgfx);
      draw_vertices(g, bgfx);
      print_burger(bgfx);
}

int main()
{
      graph* g = new_graph(10);
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
      sendto(v4, 0.7, 0.2);
      sendto(v5, 0.6, 0.9);
      
      add_edge(g, v1, v2);
      add_edge(g, v3, v4);
      
      // testing
      
      burger* bgfx = create(48,48);
      
      print_graph(g,bgfx);
      
      return 0;
}