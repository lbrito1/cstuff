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

#include <stdio.h>
#include <stdlib.h>
#include "comparators.c"

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
int grow(vector* v, int length)
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
int add(vector* v, void* data)
{
      if (grow(v,1) != 0) return 1;
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
int add_all(vector* v, void** data, int length)
{
     grow(v, length);
     int i=0;
     while (i<length) v->array[v->used++] = &(data[i++]);
}

/**
 *  @brief Get data
 *  
 *  @param [in] v    
 *  @param [in] data 
 *  @return index to searched data (-1 for failure)
 */
int get(vector* v, void* data)
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
int delete(vector* v, void* data)
{
      int idx = get(v, data);
      if (idx < 0) return idx;
      free(v->array[idx]);
      v->array[idx] = v->array[--v->used];
      return v->used;
}

#ifdef _DEBUGGING
void print_vector(vector *v)
{
      printf("\nSIZE=%d\tUSED=%d\n==============",v->size,v->used);
      int i;
      for (i=0;i<v->used;i++) printf("\n[%d]\t%d",i,*(int*)v->array[i]);
}

int main()
{
      vector* v = new_vector(2, sizeof(int), compare_integer);
      vector* q = new_vector(2, sizeof(int), compare_integer);
      
     
      static int y[] = {10,31,99,3,7,89,2,3};
      static int z = 888;
      add_all(v, (void**) y, 8);
      add(v, &z);
      delete(v, &y[0]);
      print_vector(v);
      
      return 0;
}
#endif
