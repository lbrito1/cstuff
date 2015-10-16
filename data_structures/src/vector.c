//gcc data_structures/src/vector.c data_structures/src/linked_list.c data_structures/src/avl_tree.c utils/src/comparators.c utils/src/burgergfx.c data_structures/tests/vector_test.c -o data_structures/tests/bin/avl_test.out -D_DEBUG -lm


/*
    File: vector.c

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

#ifdef PYLIB
#include <Python.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif
    
#include "../../utils/include/comparators.h"
#include "../../utils/include/debug.h"

typedef struct
{
      void** array;
      size_t type_size;
      size_t size;
      unsigned used;
      int (*cmp) (void*, void*);
} vector;

/**
 *  @brief Creates a new vector
 *  
 *  @param [in] s          initial array size
 *  @param [in] ts         type size
 *  @param [in] comparator comparator function
 *  @return pointer to created vector
 */
vector* new_vector(size_t s, size_t ts, int (*comparator) (void*, void*))
{
      vector* v = malloc(sizeof(vector));
      v->used = 0;
      v->size = s;
      v->type_size = ts;
      v->cmp = comparator;
      v->array = malloc(sizeof(void*)*v->size);
      
      return v;
}

/**
 *  @brief Doubles the vector size if necessary
 *  
 *  @param [in] v      vector
 *  @param [in] length expected increase
 *  @return success(0) or failure(1)
 */
int grow_vec(vector* v, int length)
{
      int ttlsize = v->used + length;
      int available = v->size;
      if (ttlsize > available) 
      {
            while ( (available *= 2) < ttlsize);
            void** buf = (void**) realloc(v->array, sizeof(void*)*available);
            if (!buf) return 1;
            v->size = available;
            v->array = buf;
      }
      return 0;
}

/**
 *  @brief Add a single element to the vector
 *  
 *  @param [in] v    vector
 *  @param [in] data
 *  @return success(0) or failure(1)
 */
int add_vec(vector* v, void* data)
{
      if (grow_vec(v,1) != 0) return 1;
      v->array[v->used++] = data;
      return 0;
}

/**
 *  @brief Adds an entire array to the vector
 *  
 *  @param [in] v      
 *  @param [in] data   data array
 *  @param [in] length length of the data array
 *  @return success(0) or failure(1)
 */
void add_all_vec(vector* v, void** data, int length) {
  int i=0;
  for (;i < length;i++) add_vec(v, data[i]);
}

/**
 *  @brief Get data
 *  
 *  @param [in] v    
 *  @param [in] data 
 *  @return index to searched data (-1 for failure)
 */
int get_vec(vector* v, void* data)
{
      if (v->used==0) return -1;
      int i=0;
      do {
            if (v->cmp(data, v->array[i]) == 0) return i;
      } while (++i<v->used);
      return -1;
}

/**
 *  @brief Delete data from vector
 *  
 *  @param [in] v    
 *  @param [in] data 
 *  @return success(0) or failure(1)
 */
int delete_vec(vector* v, void* data)
{
      int idx = get_vec(v, data);
      if (idx < 0) return idx;
      free(v->array[idx]);
      v->array[idx] = v->array[--v->used];
      return v->used;
}

void print_vector(vector *v)
{
      DBG("\nSIZE=%d\tUSED=%d\n==============\n",(int)v->size,v->used);
      int i;
      for (i=0;i<v->used;i++) printf("[%d]\t%d\n",i,*(int*)v->array[i]);
}

