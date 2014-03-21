/*
    File: al_graph.c

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

#include <stdlib.h>

#define UNMARKED 0
#define MARKED 1
#define TRUE 1
#define FALSE 0

typedef struct vertex
{
      unsigned long id;
      int status;
      double x,y;
      void* data;
} vertex;

typedef struct edge
{
      vertex* from, *to;
      int cost;
} edge;

/**
 *  @brief Create new vertex 
 *  
 *  @param [in] id   
 *  @param [in] data 
 *  @return 
 */
vertex* new_vertex(unsigned long id, void* data)
{
      vertex* v = malloc(sizeof(vertex));
      v->data = data;
      v->status = UNMARKED;
      v->id = id;
      v->x = 0.0;
      v->y = 0.0;
      return v;
}

/**
 *  @brief Create new edge
 *  
 *  @param [in] from 
 *  @param [in] to   
 *  @param [in] cost 
 *  @return 
 */
edge* new_edge(vertex* from, vertex* to, int cost)
{
      edge* e = malloc(sizeof(edge));
      e->from = from;
      e->to = to;
      e->cost = cost;
      return e;
}

/**
 *  @brief Compare vertices
 *  
 *  @param [in] v1 
 *  @param [in] v2 
 *  @return TRUE if ids are the same
 */
int compare_v(void* v1, void* v2) 
{
      if ((v1 == NULL) | (v2 == NULL)) return -1;
      return ((((vertex*) v1)->id) == (((vertex*) v2)->id));
}

/**
 *  @brief Compare edges
 *  
 *  @param [in] e1 
 *  @param [in] e2 
 *  @return TRUE if to and from vertices are
 *  the same at both edges
 */
int compare_e(void* e1, void* e2)
{
      if ((e1 == NULL) | (e2 == NULL)) return -1;
      return  (((edge*)e1)->from->id) == (((edge*)e2)->from->id)
      && (((edge*)e1)->to->id) == (((edge*)e2)->to->id);
}

/**
 *  @brief Visit vertex v
 *  
 *  @param [in] v 
 *  @return 
 */
int visit(vertex* v) 
{
      if (v->status == UNMARKED) 
      {
            v->status = MARKED;
            return TRUE;
      }
      return FALSE;
}
