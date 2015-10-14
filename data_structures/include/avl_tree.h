/*
    File: avl_tree.h
    
    AVL Tree implementation based on my previous implementation
    of a binary search tree.
    
    Dependencies: binary_search_tree.c
    
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

#ifndef AVL_TREE_H
#define AVL_TREE_H

#ifndef NOINCLUDE
#include "binary_search_tree.h"
#endif

/**
 *  @brief Inserts a node in the binary tree
 *  and does the necessary rebalancing required
 *  to maintain AVL property.
 *  
 *  @param [in] bt 
 *  @param [in] n  
 *  @return 
 */
node* avl_insert(binary_tree* bt, void* data, int uniqueness);

#endif