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

#ifdef _DEBUG
#include "linked_list.c"
#endif

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

node* grandpa(node* n) {
    return n->parent ? n->parent->parent : NULL;
}

node* uncle(node* n, int direction) {
    if (!n->parent || !n->parent->parent) {
        return NULL;
    }
    if (direction == LEFT) {
        return n->parent->parent->left_child;
    }
    else if (direction == RIGHT) {
        return n->parent->parent->right_child;
    }
}

binary_tree* new_binary_tree(int (*cmp) (void*, void*), int order) 
{
      binary_tree* bt = malloc(sizeof(binary_tree));
      bt->root = NULL;
      bt->nil = NULL;
      bt->cmp = cmp;
      bt->order = order;
#ifdef _DEBUG
      bt->insert_order = new_list(compare_integer); 
#endif
      return bt;
}

node* new_node(void* data)
{
      node* n = malloc(sizeof(node));
      n->data = data;
      //DBG("New node #%d (%c)\n",*(int*)n->data,*(int*)n->data);
      n->parent = NULL;
      n->left_child = NULL;
      n->right_child = NULL;
      n->height = 0;
      n->bal = 0;
      n->color = 0;
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

int height(node* n) {
    if (!n) {
        return 0;
    }
    else {
        int lh = height(n->left_child);
        int rh = height(n->right_child);
        return ((lh > rh) ? lh : rh) + 1;
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

#ifdef _DEBUG
void print_insert_order(binary_tree* bt) 
{
      if (bt->insert_order->size == 0) {
            printf("\nList empty.");
      }
      else {
            printf("\n======Insertion order======");
            element *e = bt->insert_order->head;
            int i = 0;
            do {
                  printf("\nList [%d]:\t%d (%C)",i++, *(int*) e->data, *(char*) e->data);
            } while ((e = e->next) != NULL);
            printf("\n==============\n");
      }
}
#endif
