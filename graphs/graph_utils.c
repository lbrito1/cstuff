/*
    File: graph_utils.c

    Copyright (c) 2014 Leonardo Brito <lbrito@gmail.com>

    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "../utils/debug.c"
#include "al_graph.c"
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
      graph* g = new_graph(nvert,UNDIRECTED);
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
graph* build_matrix_graph(int nvert) 
{
      graph* g = new_graph(nvert,UNDIRECTED);
      int i,j,side=sqrt(nvert);
      
      assert(side*side==nvert);   // square number
      
      //vertices
      int ch = 97;
      for(i=0;i<side;i++) 
      {
            for(j=0;j<side;j++,ch++) 
            {
                  char* data = malloc(sizeof(int));
                  *data = ch < 200 ? ch : 97;
                  vertex* v = add_vertex(g, data);
                  v->x = j/(float)side;
                  v->y = i/(float)side;
            }
      }
      
      //edges
      int from;
      for(i=0,from=0;i<side;i++) 
      {
            for(j=0;j<side;j++,from++) 
            {
                  int n,e,w,s;
                  
                  n = from - side;
                  e = from +1;
                  w = from - 1;
                  s = from + side;
                  
                  DBG("\nMATGRAPH\tidx=%d\t%d,%d,%d,%d",from,n,e,w,s);
                  DBG(" i=%d, j=%d",i,j);
                  if ((n>=0) && (i!=0)) add_edge(g, g->vertices[from], g->vertices[n], 1);
                  if ((e<=nvert) && (j!=side-1)) add_edge(g, g->vertices[from], g->vertices[e], 1);
                  //if ((w>=0) && (i!=0)) add_edge(g, g->vertices[from], g->vertices[w], 1);
                  //if (s<=side) add_edge(g, g->vertices[from], g->vertices[s], 1);
            }
      }     
      
      return g;
}

void put_weight(graph* g, int x, int y, int wg)
{
      int side = sqrt(get_nv(g));

      
      int idx = x + (y*side);
      DBG("\nxy = %d, %d\t%d\tidx %d",x,y,side,idx);
      
      edge_iter* it = new_edge_it(g, get_vertex(g,idx));
      
      edge* next = NULL;
      while ((next = next_edge(it)) != NULL)
      {
            next->cost = wg;
            DBG("\nUPD COST@[%d]->[%d] = %d",next->from->id,next->to->id,next->cost);
      }
}

void print_vertices(graph* g)
{
      int i=0;
      printf("\nCurrently %lu elements",g->nv);
      printf("\n[ID]\tDATA\n=================");
      for (;i<g->nv;i++) printf("\n[%lu]\t", g->vertices[i]->id);
}