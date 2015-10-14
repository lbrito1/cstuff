/*
    File: doubly_linked_list.c

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

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/include/comparators.h"

#if !defined _TEST_SIZE_LIST && defined _DEBUGGING
#define _TEST_SIZE_LIST 10
#endif

#define TRUE 1
#define FALSE 0

typedef struct d_element
{
      void *data;
      struct d_element *next, *prev;
} d_element;

typedef struct d_linked_list
{
      d_element *head;
      d_element *tail;
      unsigned size;
      int (*cmp) (void*, void*);
} d_linked_list;

d_linked_list *new_list(int (*comparator) (void*, void*));

d_element *new_d_element(void *data);

void add(d_linked_list *list, void *data);

d_element *search(d_linked_list *list, void *data);

int delete(d_linked_list *list, void *data);

#endif