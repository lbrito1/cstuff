// gcc sorting/quicksort.c -shared -Wl,-soname,quicksort_library -o shared/quicksort_library.so -fPIC

/*
    File: quicksort.c

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

#include "../../data_structures/include/vector.h"
#include "../../utils/include/exch.h"
#include <stdlib.h>

#ifdef GFX
#include <Python.h>    
#endif


void quicksort(vector* a, int lo, int hi) {
  if (lo < hi) {
    int pivot = partition(a, lo, hi - 1);
    quicksort(a, lo, pivot - 1);
    quicksort(a, pivot + 1, hi);
  }
}

int partition(vector* a, int lo, int hi) {
  void* pivot = a->array[hi];
  int i = lo, j;
  for (j = lo; j < hi; j++) {
    if (a->cmp(a->array[j], pivot) >= 0) {
      exch(a->array[i], a->array[j]);
      i++;
    }
  }
  exch(a->array[i], a->array[hi]);
  return i;
}

void _qsort(vector* a) {
  quicksort(a, 0, a->used);
}
