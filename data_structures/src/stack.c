/*
    File: stack.c

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

#include "../include/doubly_linked_list.h"

typedef d_linked_list stack;
typedef d_element elem;

stack *new_stack(int (*comparator) (void*, void*))
{
      return new_list_dl(comparator);
}

void push_stack(stack* s, void *data)
{
      add_dl(s, data);
}

void* pop_stack(stack* s)
{
      elem* tail = s->tail;
      if (tail!=NULL) 
      {
            if (tail->prev != NULL)
            {
                  s->tail = tail->prev;
                  s->tail->next = NULL;   
            }
            else
            {
                  s->tail = s->head;                  
            }
      }
      return tail->data;
}

void* peek_stack(stack* s)
{
      return s->tail->data;
}

#ifdef _DEBUGGING
int main()
{
      stack* s = new_stack(compare_integer);
      int i, *data;
      for (i=0; i<100; i++) 
      {
            data = malloc(sizeof(int));
            *data = i;
            push(s, data);
      } 
      
      for (i=0; i<100; i++) 
      {
            data = (int*) pop(s);
            printf("\nPopped %d",*((int*) data));
            free(data);
      } 
      return 0;
}
#endif