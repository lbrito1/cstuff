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

#define DIRECTED 0
#define UNDIRECTED 1
#include "../include/graph_ve.h"
#include "../data_structures/include/linked_list.h"

typedef struct graph
{
      vertex** vertices;
      int directed;
      unsigned long max_vertices;
      unsigned long n_edges;
      unsigned long nv;
      linked_list** adj_list;
      void (*printvert) (void*);
} graph;

typedef struct edge_iter
{
      graph* g;
      vertex* origin;
      element* head;
      int idx, length;
} edge_iter;

/**
 *  @brief 
 *  
 *  @param [in] n_vertices max n vertices
 *  @param [in] directed   DIRECTED or UNDIRECTED graph
 *  @return 
 */
graph* new_graph(int n_vertices, int directed)
{
      graph* g_p = malloc(sizeof(graph));
      g_p->directed = directed;
      g_p->max_vertices = n_vertices;
      g_p->vertices = malloc(sizeof(vertex*)*g_p->max_vertices); 
      g_p->nv = 0;
      g_p->n_edges = 0;
      g_p->adj_list = malloc(sizeof(linked_list*)*g_p->max_vertices);
      int i=0;
      for (;i<g_p->max_vertices;i++) g_p->adj_list[i] = new_list(compare_e);
      return g_p;
}

/**
 *  @brief Edge iterator: all neighbors of vertex 'from'
 *  
 *  @param [in] g    
 *  @param [in] from 
 *  @return 
 */
edge_iter* new_edge_it(graph* g, vertex* from)
{
      edge_iter* it = malloc(sizeof(edge_iter));
      it->g = g;
      it->origin = from;
      it->head = g->adj_list[from->id]->head->next;
      it->idx = 0;
      it->length = g->adj_list[from->id]->size;
      return it;
}

/**
 *  @brief Next edge in list
 *  
 *  @param [in] it 
 *  @return 
 */
edge* next_edge(edge_iter* it)
{
      if (++it->idx < it->length)
      {
            edge* e = (edge*) it->head->data;
            it->head = it->head->next;
            return e;
      }
      else return NULL;
}

/**
 *  @brief Get edge from adjacency list
 *  
 *  @param [in] g    
 *  @param [in] from 
 *  @param [in] to   
 *  @return 
 */
edge* get_edge(graph* g, int from, int to)
{
      element* e = g->adj_list[from]->head;
      while ((e=e->next) != NULL) if (((((edge*) e->data)->to)->id) == to) return ((edge*) e->data);
      return NULL;
}

/**
 *  @brief Get vertex from array @idx
 *  
 *  @param [in] g   
 *  @param [in] idx 
 *  @return 
 */
vertex* get_vertex(graph* g, int idx)
{
      if (idx>g->nv) return NULL;
      return g->vertices[idx];
}

/**
 *  @brief Add vertex to graph
 *  
 *  @param [in] g    
 *  @param [in] data vertex data
 *  @return created vertex
 */
vertex* add_vertex(graph* g, void* data) 
{
      vertex* v;
      int pos = g->nv;
      if (pos < g->max_vertices) 
      {
            v = (g->vertices[pos] = new_vertex(pos, data));
            add((g->adj_list[pos]), NULL);      //prepare adjlist
            g->nv++;
      }
      else return NULL;
      
      return v;
}

/**
 *  @brief Add edge to graph
 *  
 *  @param [in] g    
 *  @param [in] vf   
 *  @param [in] vt   
 *  @param [in] cost 
 *  @return 
 */
void add_edge(graph* g, vertex* vf, vertex* vt, int cost)
{
      add((g->adj_list[vf->id]), new_edge(vf,vt,cost));
      if (g->directed == UNDIRECTED) add((g->adj_list[vt->id]), new_edge(vt,vf,cost)); 
}

/**
 *  @brief Get number of vertices in graph
 *  
 *  @param [in] g 
 *  @return 
 */
int get_nv(graph* g)
{
      return g->nv;
}

/**
 *  @brief Visit vertex @idx
 *  
 *  @param [in] g   
 *  @param [in] idx 
 *  @return 
 */
int visit_vert(graph* g, int idx)
{
      return visit(g->vertices[idx]);
}