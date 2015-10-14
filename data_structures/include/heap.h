/*
    File: heap.h

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

#ifndef HEAP_H
#define HEAP_H

typedef struct {
      void** array;
      int array_size;
      int heap_size;
      int order;
      int (*cmp) (void*, void*);
} heap;

heap* new_heap(int size, int ord, int (*compare) (void*, void*));

void heapify(heap* h, int idx);

void build_heap(heap* h);

void* pop_heap(heap* h);

void* pop_at(heap* h, int pos);

int push_heap(heap* h, void* k);

void update_heap(heap* h, int pos);

#endif