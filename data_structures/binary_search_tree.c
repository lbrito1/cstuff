/*
    File: binary_search_tree.c

    Binary search tree property: 
    
    "Let x be a tree. 
    If y is a node in the left subtree of x, then key[y] <= key[x].
    If y is a node in the right subtree of x, then key[y] >= key[x]."
    
    Cormen & Leiserson chap 13
    
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

#include <stdio.h>
#include <time.h>

#include "../utils/comparators.c"
#include "binary_tree.c"

void tree_insert(binary_tree* bt, node* n)
{
      node* cur = bt->root;
      node* prev = NULL;
      int goes_to = -1;
      
      while(cur!=NULL)
      {
            prev = cur;
            if ( (bt->order == ORD_ASC) 
                  ? bt->cmp(cur->data, n->data) < 0
                  : bt->cmp(cur->data, n->data) > 0 ) 
            {
                  cur = cur->left_child;
                  goes_to = LEFT;
            }
            else 
            {
                  cur = cur->right_child;
                  goes_to = RIGHT;
            }
      }
      
      if (prev != NULL)
      {
            n->parent = prev;
            if (goes_to == LEFT)          set_child(prev, n, LEFT);
            else if (goes_to == RIGHT)    set_child(prev, n, RIGHT);
            DBG("Node (#%d) inserted\n",*(int*)n->data);
      }
      else  // tree is empty, insert @ root
      {
            DBG("Node (#%d) set as ROOT\n",*(int*)n->data);
            bt->root = n;
      }
}

void visit(node* n)
{
      DBG("Visited node #%d\n",*(int*)n->data);
}

#ifdef _DEBUG
int main()
{
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 10;     
      
      srand(time(NULL));
      int i;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = rand()%(ts*10);
            node* n = new_node((void*) data);
            tree_insert(bt, n);     
      }
      
      depth_first(bt, visit, IN_ORDER);

      return 0;
}
#endif