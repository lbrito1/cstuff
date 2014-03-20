#include "al_graph.c"
#include <math.h>
#include <assert.h>

#define ADJ_LIST 0
#define ADJ_MATRIX 1

typedef struct {
      int g_type;
      al_graph* al_g;
      int (*get_nv) (void*);
      vertex** (*get_vlist) (void*); 
      //mat_graph* mat_g;
} graph;

graph* new_graph(int type, int directed, int nvert) 
{
      graph* g;
      if (type == ADJ_LIST)
      {
            g = malloc(sizeof(graph));
            g->g_type = type;
            g->al_g = new_al_graph(nvert, directed);
            g->get_nv = get_al_nv;
            g->get_vlist = get_al_vlist;
            return g;
      }
      else if (type == ADJ_MATRIX)
      {
            return NULL;
      }
      else return NULL;
}

/**
 *  @brief Build a complete graph
 *  
 *  @param [in] nvert number of vertices: make sure to be perfect square
 *  @return 
 */
al_graph* build_complete_graph(int nvert) 
{
      al_graph* g = new_al_graph(nvert,UNDIRECTED);
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

/**
 *  @brief 
 *  
 *  @param [in] nvert number of vertices: make sure to be perfect square
 *  @return 
 */
al_graph* build_matrix_al_graph(int nvert) 
{
      al_graph* g = new_al_graph(nvert,UNDIRECTED);
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
      for(i=0;i<side;i++) 
      {
            for(j=0;j<side;j++) 
            {
                  int from = j+(i*side);
                  
                  int n,e,w,s;
                  
                  n = from - side;
                  e = from +1;
                  s = from + side;
                  w = from - 1;
                  
                  if (n>0) add_edge(g, g->vertices[from], g->vertices[n], 1);
                  if (e<side) add_edge(g, g->vertices[from], g->vertices[e], 1);
                  if (w>0) add_edge(g, g->vertices[from], g->vertices[w], 1);
                  if (s<side) add_edge(g, g->vertices[from], g->vertices[s], 1);
                  
            
                  printf("\n%d\t%d,%d,%d,%d",from,n,e,w,s);
            }
      }     
      
      return g;
}