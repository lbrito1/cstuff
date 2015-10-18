/*
    File: binary_tree.h

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

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdlib.h>

#include "linked_list.h"

#define TRUE 1
#define FALSE 0

#define LEFT 0
#define RIGHT 1

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

typedef struct node
{
      void* data;
      int height, bal, color;
      struct node* parent;
      struct node* left_child;
      struct node* right_child;
} node;

typedef struct 
{
      node *root, *nil;
      int order;
      int (*cmp) (void*, void*);
#ifdef _DEBUG
      linked_list* insert_order;
#endif
} binary_tree;

node* grandpa(node* n);

node* uncle(node* n, int direction);

binary_tree* new_binary_tree(int (*cmp) (void*, void*), int order);

void delete_tree(binary_tree* bt);

node* new_node(void* data);

void delete_node(node* n);

void dfs(node* n, void (*visit) (node*), int v_order);

int height(node* n);

void depth_first(binary_tree* bt, void (*visit) (node*), int v_order);

int set_child(node* parent, node* child, int c);

#ifdef _DEBUG
void print_insert_order(binary_tree* bt);
#endif

#endif