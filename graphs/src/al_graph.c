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


#include "../../data_structures/include/linked_list.h"

#include "../include/graph_defs.h"
#include "../include/al_graph.h"

edge_iter* new_edge_it(graph* g, vertex* from)
{
      edge_iter* it = malloc(sizeof(edge_iter));
      it->g = g;
      it->origin = from;
      it->head = g->adj_list[from->id]->head;
      it->idx = 0;
      it->length = g->adj_list[from->id]->size;
      return it;
}

edge* next_edge(edge_iter* it)
{
      if (++it->idx <= it->length)
      {
            edge* e = (edge*) it->head->data;
            it->head = it->head->next;
            return e;
      }
      else return NULL;
}

int visit_vert(graph* g, int idx)
{
      return visit(g->vertices[idx]);
}