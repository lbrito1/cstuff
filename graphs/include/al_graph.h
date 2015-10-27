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

#ifndef AL_GRAPH_H
#define AL_GRAPH_H

#include "graph_adj.h"

typedef struct edge_iter
{
      graph* g;
      vertex* origin;
      element* head;
      int idx, length;
} edge_iter;

edge_iter* new_edge_it(graph* g, vertex* from);

edge* next_edge(edge_iter* it);

int visit_vert(graph* g, int idx);

#endif