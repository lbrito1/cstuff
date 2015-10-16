/*
    File: heapsort.c

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
#include "../../data_structures/include/heap.h"
#include "../../utils/include/exch.h"

void heapsort(heap* h)
{
      build_heap(h);
      int i;
      for (i = h->heap_size; i>1; i--)
      {
            exch(&(h->array[1]), &h->array[i]);
            h->heap_size--;
            heapify(h,1);
      }
}