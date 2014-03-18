/*
    File: heap.c

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

#include <stdlib.h>

#define PARENT(i) i>>1
#define LEFT(i) i<<1
#define RIGHT(i) (i<<1)+1
static inline void exch(void** a, void** b) { void* p = *a; *a = *b; *b = p; }

typedef struct {
      void** array;
      int array_size;
      int heap_size;
      int order;
      int (*cmp) (void*, void*);
} heap;

/**
 *  @brief Create new heap data structure
 *  
 *  @param [in] size    maximum heap size
 *  @param [in] ord     minheap: ORD_ASC, maxheap: ORD_DES
 *  @param [in] compare comparator
 *  @return Return_Description
 */
heap* new_heap(int size, int ord, int (*compare) (void*, void*))
{
      heap* h = malloc(sizeof(heap));
      h->array = malloc(sizeof(void*)*size);
      h->array_size = size+1;
      h->heap_size = 0;
      h->cmp = compare;
      h->order = ord;
      return h;
}

/**
 *  @brief Heapifies subtree rooted at h->array[idx], assuming
 *  that its two subtree children are already heaps. This is done
 *  by "floating down" the value at idx, which may violate heap
 *  condition, until it reaches the appropriate depth.
 *  
 *  @param [in] h   Parameter_Description
 *  @param [in] idx Parameter_Description
 */
void heapify(heap* h, int idx)
{
      int l = LEFT(idx);
      int r = RIGHT(idx);
      int largest = idx;
      
      if (h->order == ORD_ASC) 
      {
            if ((l<=h->heap_size) && (h->cmp(h->array[l], h->array[idx]) > 0)) largest = l;
            if ((r<=h->heap_size) && (h->cmp(h->array[r], h->array[largest]) > 0)) largest = r;
      }
      else if (h->order == ORD_DES)
      {
            if ((l<=h->heap_size) && (h->cmp(h->array[l], h->array[idx]) < 0)) largest = l;
            if ((r<=h->heap_size) && (h->cmp(h->array[r], h->array[largest]) < 0)) largest = r;
      }
      
      if (largest != idx) 
      {
            exch(&h->array[idx], &h->array[largest]);
            heapify(h, largest);
      }
}

/**
 *  @brief Builds a heap from an unsorted array (h->array)
 *  
 *  @param [in] h 
 */
void build_heap(heap* h)
{
      int i;
      for(i = h->heap_size>>1; i>0; i--) heapify(h, i);
}

/**
 *  @brief Pops min/maxval from heap
 *  
 *  @param [in] h 
 *  @return pointer to min/maxval
 */
void* pop(heap* h)
{
      if(h->heap_size<1) return NULL;
      void* max = h->array[1];
      h->array[1] = h->array[h->heap_size--];
      heapify(h,1);
      return max;
}

/**
 *  @brief Pushes value onto heap
 *  
 *  @param [in] h 
 *  @param [in] k 
 *  @return FALSE if heap is full, TRUE otherwise
 */
int push(heap* h, void* k)
{
      if (h->heap_size == h->array_size - 1) return FALSE;
      h->heap_size++; 
      
      int i;
      if (h->order == ORD_ASC)
            for (i = h->heap_size; i>1 && h->cmp(h->array[PARENT(i)], k) < 0; i = PARENT(i)) h->array[i] = h->array[PARENT(i)];
      else if (h->order == ORD_DES)
            for (i = h->heap_size; i>1 && h->cmp(h->array[PARENT(i)], k) > 0; i = PARENT(i)) h->array[i] = h->array[PARENT(i)];
      
      h->array[i] = k;
      
      return TRUE;
}