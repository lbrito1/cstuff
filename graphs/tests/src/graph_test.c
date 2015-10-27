#include "../../include/graph_utils.h"
#include "../../include/graph_defs.h"
#include "../../../utils/include/burgergfx.h"
#include "../../../utils/include/debug.h"


int main()
{
      graph* g = new_graph(10, UNDIRECTED);
      char mydata = 'A';
      char mydata2 = 'B';
      char mydata3 = 'C';
      char mydata4 = 'D';
      char mydata5 = 'F';
      char mydata6 = 'G';
      char mydata7 = 'H';
      
      vertex* v1 = add_vertex(g, &mydata);
      vertex* v2 = add_vertex(g, &mydata2);
      vertex* v3 = add_vertex(g, &mydata3);
      vertex* v4 = add_vertex(g, &mydata4);
      vertex* v5 = add_vertex(g, &mydata5);
      vertex* v6 = add_vertex(g, &mydata6);
      vertex* v7 = add_vertex(g, &mydata7);
      
      sendto(v1, 0.9, 0.4);
      sendto(v2, 0.5, 0.6);
      sendto(v3, 0.6, 0.3);
      sendto(v4, 0.7, 0.1);
      sendto(v5, 0.2, 0.45);
      sendto(v6, 0.4, 0.7);
      sendto(v7, 0.7, 0.7);
      
      add_edge(g, v1, v3, 1);
      add_edge(g, v2, v3, 1);
      add_edge(g, v2, v5, 1);
      add_edge(g, v3, v4, 1);
      add_edge(g, v5, v3, 1);
      add_edge(g, v6, v2, 1);
      add_edge(g, v6, v5, 1);
      add_edge(g, v7, v1, 1);
      
      edge_iter* it = new_edge_it(g,v1);
      edge* next = NULL;
      
      while ((next = next_edge(it)) != NULL) 
            DBG("\n%d\tE(%lu,%lu) = %d",it->idx,next->from->id,next->to->id,next->cost);
      
      
      // testing
      
      burger* bgfx = create_bgfx(48,48);
      
      print_graph(g,bgfx);
      
      graph* cg = build_complete_graph(100);
      
      print_vertex_status(cg, bgfx);
      
      return 0;
}
