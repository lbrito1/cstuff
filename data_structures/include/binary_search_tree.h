/*
    File: binary_search_tree.h

    Binary search tree property: 
    
    "Let x be a tree. 
    If y is a node in the left subtree of x, then key[y] <= key[x].
    If y is a node in the right subtree of x, then key[y] >= key[x]."
    
    Cormen & Leiserson chap 13
    
    Operation costs:
    
    SEARCH, FINDMIN, SUCCESSOR, INSERT, DELETE 
    
    O(h) time on a tree with height h.
    
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

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "binary_tree.h"

node *tree_insert(binary_tree* bt, void* data, int uniqueness);

node* tree_min(node* btroot);

node* tree_successor(binary_tree* bt, node* n);

node* tree_search(binary_tree* bt, void* val);

node* tree_delete(binary_tree* bt, void* value);

#endif