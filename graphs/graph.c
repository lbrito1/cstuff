#include "graph_adj.c"
#include <math.h>
#include <assert.h>

/**
 *  @brief Build a complete graph
 *  
 *  @param [in] nvert number of vertices: make sure to be perfect square
 *  @return 
 */
graph* build_complete_graph(int nvert) 
{
      graph* g = new_graph(nvert);
      int i,j,side=sqrt(nvert);
      
      assert(side*side==nvert);   // square number
      
      //vertices
      for(i=0;i<side;i++) 
      {
            for(j=0;j<side;j++) 
            {
                  int* data = malloc(sizeof(int));
                  *data = j+(i*side);
                  vertex* v = add_vertex(g, data);
                  v->x = j/(float)side;
                  v->y = i/(float)side;
            }
      }
      
      //edges
      for(i=0;i<nvert;i++) 
      {
            for(j=0;j<nvert;j++) 
            {
                  if (i!=j) // no self-loops
                  {
                        add_edge(g, g->vertices[i], g->vertices[j], 1);
                  }
            }
      }     
      
      return g;
}