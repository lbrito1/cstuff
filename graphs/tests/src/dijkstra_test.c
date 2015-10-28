#include "../../include/dijkstra.h"
#include "../../include/graph_utils.h"
#include "../../include/graph_defs.h"
#include "../../../utils/include/debug.h"

#define WALL 87
#define WALL_VAL 100


int main()
{

      // Custom graph
      
      int res = 32;

      graph* g = new_graph(10,UNDIRECTED);
      // char mydata = '0';
      // char mydata2 = '1';
      // char mydata3 = '2';
      // char mydata4 = '3';
      // char mydata5 = '4';
      // char mydata6 = '5';
      
      // vertex* v0 = add_vertex(g, &mydata);
      // vertex* v1 = add_vertex(g, &mydata2);
      // vertex* v2 = add_vertex(g, &mydata3);
      // vertex* v3 = add_vertex(g, &mydata4);
      // vertex* v4 = add_vertex(g, &mydata5);
      // vertex* v5 = add_vertex(g, &mydata6);
      
      // sendto(v0, 0.9, 0.1);
      // sendto(v1, 0.4, 0.9);
      // sendto(v2, 0.6, 0.3);
      // sendto(v3, 0.7, 0.1);
      // sendto(v4, 0.1, 0.3);
      // sendto(v5, 0.2, 0.8);
      
      // add_edge(g, v0, v1, 2);
      // add_edge(g, v0, v2, 3);
      // add_edge(g, v1, v2, 1);
      // add_edge(g, v2, v3, 1);
      // add_edge(g, v4, v2, 1);
      // add_edge(g, v4, v1, 1);
      // add_edge(g, v5, v4, 1);
      
      burger* bgfx = create_bgfx(res,res);
      
      int* d = dijkstra(g,0,-1,NULL);
      
      print_graph(g,bgfx);
      
      print_vertex_status(g, bgfx);
      
      int i,j;
      DBG("\nPrevious\n===============\n");
      for (i=0; i<get_nv(g); i++) DBG("\nvert[%d]\t%d",i,d[i]);
      
      int start = 0, finish = (res*res)-2;
      
      free(g);
      free(d);




      g = build_matrix_graph(res*res);
      
      clear_graph(g, 1);
      char st = 'S', fs = 'F';
      get_vertex(g,start)->data = (void*) &st;
      get_vertex(g,finish)->data = (void*) &fs;
      
      put_wgt_rect(g, 0,3,30,5,WALL_VAL);
      put_wgt_rect(g, 2,10,32,13,WALL_VAL);
      put_wgt_rect(g, 10,15,12,32,WALL_VAL);
            
      d = dijkstra(g,0,-1,NULL);
      clean_burger(bgfx);
      print_trace(bgfx,g,d,start,finish);
      draw_vertices_spec(g,bgfx,1);
      //draw_vertex_status(g, bgfx);
      print_burger(bgfx);
      
      
      return 0;
}
