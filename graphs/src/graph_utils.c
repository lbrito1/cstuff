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

#include "../include/graph_defs.h"
#include "../include/graph_utils.h"
#include "../include/al_graph.h"
#include "../../utils/include/debug.h"
#include "../../utils/include/burgergfx.h"
#include <math.h>
#include <assert.h>


void print_path(graph* g, int* d)
{
      int i = 0;
      DBG("\nPrevious\n===============\n");
      for (i=0; i<get_nv(g); i++) DBG("\nvert[%d]\t%d",i,d[i]);
}

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

void put_wgt_rect(graph* g, int x1, int y1, int x2, int y2, int val)
{
      int i,j;
      for (i=x1;i<x2;i++)
            for (j=y1;j<y2;j++) put_weight(g,i,j,val);
}

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
                  vertex* v = add_vertex(g, data,sizeof(int));
                  free(data);
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
                  vertex* v = add_vertex(g, data,sizeof(int));
                  free(data);
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
      
      vertex* orig = get_vertex(g,idx);
      
      
      int* xx = malloc(sizeof(int));
      *xx = 87;
      orig->data = (void*)xx;
      
      edge_iter* it = new_edge_it(g, orig);
      
      edge* next = NULL;
      while (next = next_edge(it))
      {
            next->cost = wg;
            if (next->to && next->to->id) DBG("\nUPD COST@[%lu]->[%lu] = %d",next->from->id,next->to->id,next->cost);
      }
}

void print_vertices(graph* g)
{
      int i=0;
      printf("\nCurrently %d elements",get_nv(g));
      printf("\n[ID]\tDATA\n=================");
      for (;i<get_nv(g);i++) printf("\n[%lu]\t", g->vertices[i]->id);
}


void sendto(vertex* v, double x, double y)
{
      v->x = x; v->y = y;
}

void draw_vertices(graph* g, burger* b)
{
      int i;
      for (i=0; i<get_nv(g); i++)
      {
            vertex* v = g->vertices[i];
            put_burger(b, v->x, v->y, *((char*) v->data));
      }
}

void draw_vertices_spec(graph* g, burger* b, int data)
{
      int i;
      for (i=0; i<get_nv(g); i++)
      {
            vertex* v = g->vertices[i];
            if ((*(int*)v->data) != data) put_burger(b, v->x, v->y, *((char*) v->data));
      }
}

void draw_vertex_status(graph* g, burger* b)
{
      int i;
      for (i=0; i<get_nv(g); i++)
      {
            vertex* v = g->vertices[i];
            char c = v->status == UNMARKED ? 'u' : 'M';
            put_burger(b, v->x, v->y, c);
      }
}

void draw_edges(graph* g, burger* b)
{
      int i;
      for (i=0; i<get_nv(g); i++)
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

void set_vertex(graph* g, int idx, void* data) {
      get_vertex(g, idx)->data = data;
}

void clear_graph(graph* g, int data) {
      int* xx = malloc(sizeof(int));
      *xx = data;
      int i;
      for(i=0;i<get_nv(g);i++) get_vertex(g,i)->data = (void*)xx;
}

int get_vertex_data(graph* g, int idx) {
      return *(int*) get_vertex(g, idx)->data;
}