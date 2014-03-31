/*
    File: binary_tree.c

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

#include "../utils/debug.c"

#define LEFT 0
#define RIGHT 1

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

typedef struct node
{
      void* data;
      struct node* parent;
      struct node* left_child;
      struct node* right_child;
} node;

typedef struct 
{
      node* root;
      int order;
      int (*cmp) (void*, void*);
} binary_tree;

binary_tree* new_binary_tree(int (*cmp) (void*, void*), int order) 
{
      binary_tree* bt = malloc(sizeof(binary_tree));
      bt->root = NULL;
      bt->cmp = cmp;
      bt->order = order;
      return bt;
}

node* new_node(void* data)
{
      node* n = malloc(sizeof(node));
      n->data = data;
      DBG("New node (#%d)\n",*(int*)n->data);
      n->parent = NULL;
      n->left_child = NULL;
      n->right_child = NULL;
      return n;
}

void dfs(node* n, void (*visit) (node*), int v_order)
{
      if (n!=NULL) 
      {
            if (v_order == PRE_ORDER) visit(n);
            
            dfs(n->left_child, visit, v_order);
            
            if (v_order == IN_ORDER) visit(n);
            
            dfs(n->right_child, visit, v_order);
            
            if(v_order == POST_ORDER) visit(n);
      }
}

void depth_first(binary_tree* bt, void (*visit) (node*), int v_order)
{
      DBG("\nSTARTED DFS\n\n");
      dfs(bt->root, visit, v_order);
}

int set_child(node* parent, node* child, int c)
{
      if (parent == NULL) return -1;
      if (c==LEFT) parent->left_child = child;
      else if (c==RIGHT) parent->right_child = child;
      return 0;
}