/*
    File: graph_utils.h

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

#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include "../../utils/include/debug.h"
#include "../../utils/include/burgergfx.h"
#include "al_graph.h"

// Make sure nvert is perfect square
graph* build_complete_graph(int nvert);

graph* build_matrix_graph(int nvert);

void put_weight(graph* g, int x, int y, int wg);

void put_wgt_rect(graph* g, int x1, int y1, int x2, int y2, int val);

void print_path(graph* g, int* d);

void print_trace(burger* b, graph* g, int* prev, int orig, int dest);

void print_vertices(graph* g);

void sendto(vertex* v, double x, double y);

void draw_vertices(graph* g, burger* b);

void draw_vertices_spec(graph* g, burger* b, int data);

void draw_vertex_status(graph* g, burger* b);

void draw_edges(graph* g, burger* b);

void print_graph(graph* g, burger* bgfx);

void print_vertex_status(graph* g, burger* bgfx);

void set_vertex(graph* g, int idx, void* data);

void clear_graph(graph* g, int data);

int get_vertex_data(graph* g, int idx);

#endif