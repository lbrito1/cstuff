/*
    File: al_graph.h

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

#ifndef GRAPH_VE_H
#define GRAPH_VE_H

#include <stdlib.h>

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

vertex* new_vertex(unsigned long id, void* data, size_t dsize);

void delete_vertex(vertex* v);

edge* new_edge(vertex* from, vertex* to, int cost);

int compare_v(void* v1, void* v2);

int compare_e(void* e1, void* e2);

int visit(vertex* v);

#endif