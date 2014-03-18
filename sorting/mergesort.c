/*
    File: mergesort.c

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

#include "linked_list.c"
#include <time.h>
#include <stdlib.h>

#if !defined _TEST_SIZE_MSORT && defined _DEBUGGING
#define _TEST_SIZE_MSORT 10
#endif

#define ASC 0
#define DEC 1

element* mergesort(linked_list* list, int order);
void halve(linked_list* list, linked_list* left, linked_list* right);
element* merge(element* a, element* b, int (*cmp) (void*, void*), int order);

/**
 *  @brief Orders the list using mergesort
 *  
 *  @param [in] list  Linked list
 *  @param [in] order Sorting order (ASC or DEC)
 *  @return partial result, used for recursion only
 */
element* mergesort(linked_list* list, int order)
{
      linked_list *left = new_list(list->cmp);
      linked_list *right = new_list(list->cmp);
      
      if (list->head == NULL || list->head->next == NULL) return list->head;
      
      halve(list, left, right);
      
      element* merged = merge(mergesort(left, order),mergesort(right, order), list->cmp, order);
      
      free(left);
      free(right);
      
      return merged;
}

/**
 *  @brief Splits a list into two halves
 *  
 *  @param [in] list  Original list
 *  @param [in] left  Left half
 *  @param [in] right Right half
 */
void halve(linked_list* list, linked_list* left, linked_list* right)
{
      element* middle = list->head;
      if (middle!=NULL) {
      int half = (int) ((list->size)/2.0f), i=0;
      while (++i<half) middle = middle->next;
      element* middle_head = middle->next;
      middle->next = NULL;
      
      left->head = list->head;
      left->size = (list->size)-half;
      
      right->head = middle_head;
      right->size = half;}
}

/**
 *  @brief Merges two lists into a single list
 *  
 *  @param [in] a   First half
 *  @param [in] b   Second half
 *  @param [in] cmp Comparator function
 *  @return Pointer to consolidated list's head
 */
element* merge(element* a, element* b, int (*cmp) (void*, void*), int order)
{
      element* c = new_element(NULL);
      element* merged = c;
      while (a != NULL && b != NULL) 
      {
            if ((order==ASC) ? (cmp(a->data, b->data) > 0) : (cmp(a->data, b->data) < 0))
            {
                  c->next = a;
                  a = a->next;
            }
            else
            {
                  c->next = b;
                  b = b->next;
            }
            c = c->next;
      }
      c->next = (a == NULL) ? b : a;
      return merged->next;
}

//#ifdef _DEBUGGING
int main()
{
      linked_list* list = new_list(compare_integer);
      
      srand(time(NULL));
      
      int* x = malloc(sizeof(int)*_TEST_SIZE_MSORT);
      
      int i=0;
      for (;i<_TEST_SIZE_MSORT;i++)
      {
            x[i] = rand();
            add(list, &(x[i]));
      }
      
      element* xx = list->head;
      i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      printf("\n\nSorted:");
      xx = mergesort(list, DEC);
      list->head = xx;
      i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      return 0;
}
//#endif