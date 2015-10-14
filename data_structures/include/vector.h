/*
    File: vector.h

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

#ifndef VECTOR_H
#define VECTOR_H


#include <stdio.h>
#include <stdlib.h>
    
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

vector* new_vector(size_t s, size_t ts, int (*comparator) (void*, void*));

int grow_vec(vector* v, int length);

int add_vec(vector* v, void* data);

void add_all_vec(vector* v, void** data, int length);

int get_vec(vector* v, void* data);

int delete_vec(vector* v, void* data);

void print_vector(vector *v);

#endif