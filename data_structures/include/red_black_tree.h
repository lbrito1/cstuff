/*
    File: red_black_tree.h

    Copyright (c) 2015 Leonardo Brito <lbrito@gmail.com>

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

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <math.h>
#include "binary_search_tree.h"

#define RED 0
#define BLACK 1

node* rb_insert(binary_tree* bt, void* data, int uniqueness);

#endif