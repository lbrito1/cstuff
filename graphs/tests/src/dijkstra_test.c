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
      char mydata = '0';
      char mydata2 = '1';
      char mydata3 = '2';
      char mydata4 = '3';
      char mydata5 = '4';
      char mydata6 = '5';
      
      vertex* v0 = add_vertex(g, &mydata, sizeof(char));
      vertex* v1 = add_vertex(g, &mydata2, sizeof(char));
      vertex* v2 = add_vertex(g, &mydata3, sizeof(char));
      vertex* v3 = add_vertex(g, &mydata4, sizeof(char));
      vertex* v4 = add_vertex(g, &mydata5, sizeof(char));
      vertex* v5 = add_vertex(g, &mydata6, sizeof(char));
      
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
      
      burger* bgfx = create_bgfx(res,res);
      
      int* d = dijkstra(g,0,-1, NULL);
      
      print_graph(g,bgfx);
      
      print_vertex_status(g, bgfx);
      
      int i,j;
      DBG("\nPrevious\n===============\n");
      for (i=0; i<get_nv(g); i++) DBG("\nvert[%d]\t%d",i,d[i]);
      
      int start = 0, finish = (res*res)-2;
      
      delete_graph(g);
      free(d);

      // Pathfinding

      g = build_matrix_graph(res*res);
      
      clear_graph(g, 1);

      // will be freed by graph
      char *st = malloc(sizeof(char));
      char *fs = malloc(sizeof(char));
      set_vertex(g,start, st);
      set_vertex(g,finish, fs);
      
      put_wgt_rect(g, 0,3,30,5,WALL_VAL);
      put_wgt_rect(g, 2,10,32,13,WALL_VAL);
      put_wgt_rect(g, 10,15,12,32,WALL_VAL);
            
      int* dist = malloc(sizeof(int)*get_nv(g));
      d = dijkstra(g,0,-1, dist);
      free(dist);
      clean_burger(bgfx);
      print_trace(bgfx,g,d,start,finish);
      draw_vertices_spec(g,bgfx,1);
      print_burger(bgfx);
      delete_burger(bgfx);

      delete_graph(g);
      
      return 0;
}
