/*
    File: mergesort.h

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

#ifndef MERGESORT_H
#define MERGESORT_H

#include "../../data_structures/include/linked_list.h"
#include <time.h>
#include <stdlib.h>

#if !defined _TEST_SIZE_MSORT && defined _DEBUGGING
#define _TEST_SIZE_MSORT 10
#endif

#define ASC 0
#define DEC 1

/**
 *  @brief Orders the list using mergesort
 *  
 *  @param [in] list  Linked list
 *  @param [in] order Sorting order (ASC or DEC)
 *  @return partial result, used for recursion only
 */
element* mergesort(linked_list* list, int order);

#endif