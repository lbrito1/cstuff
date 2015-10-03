/*
    File: binary_search_tree.c

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

#include <stdio.h>

#include "../utils/comparators.c"
#include "binary_tree.c"


node* tree_search(binary_tree* bt, void* val);

/**
 *  @brief Insertion
 *  
 *  Starting from the root, we dive down through
 *  the children until we reach the node whose
 *  value is closest to the value of the node we
 *  want to insert. 
 *  
 *  @param [in] bt 
 *  @param [in] value  
 *  @return new node
 */
node *tree_insert(binary_tree* bt, void* data, int uniqueness)
{
    node *n;
    uniqueness = uniqueness ? uniqueness : 0;
    if (uniqueness) {
        n = tree_search(bt, data);
        if (n) {
            DBG("Repeated node %d (%c), uniqueness is enforced. Aborting insertion\n", *(int*)data, *(char*)data);
            return n;
        }
    }
    n = new_node(data);

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
          DBG("%sNode (#%d) (%c) inserted\n%s",ANSI_COLOR_GREEN,*(int*)n->data,*(char*)n->data, ANSI_COLOR_RESET);
    }
    else  // tree is empty, insert @ root
    {
          DBG("Node (#%d) set as ROOT\n",*(int*)n->data);
          bt->root = n;
    }

#ifdef _DEBUG
    add(bt->insert_order,n->data);
#endif

    return n;
}

/**
 *  @brief Finds the tree's minval node
 *  
 *  @param [in] btroot 
 *  @return 
 */
node* tree_min(node* btroot)
{
      node* it = btroot;
      if(it!=NULL)
            while (it->left_child!=NULL) it = it->left_child;
      return it;
}


/**
 *  @brief Successor to n
 *  
 *  If n is the largest node of the tree, return NULL.
 *  
 *  Else, if n has a right child x, find the leftmost
 *  node (i.e. smallest) in the subtree rooted at x.
 *  
 *  If n doesn't have a right child, 
 *  
 *  @param [in] bt Parameter_Description
 *  @param [in] n  Parameter_Description
 *  @return Return_Description
 */
node* tree_successor(binary_tree* bt, node* n)
{
      node* suc_n = NULL;

      if (n->right_child!=NULL) return tree_min(n->right_child);
      suc_n = n->parent;
      while ((suc_n != NULL) && (n == suc_n->right_child)) 
      {
            n = suc_n;
            suc_n = suc_n->parent;
      }

      return suc_n;
}

/**
 *  @brief Searches for the node with the specified val
 *  
 *  @param [in] bt  
 *  @param [in] val 
 *  @return 
 */
node* tree_search(binary_tree* bt, void* val)
{
      DBG("Searching for node %d\n",*(int*) val);
      node* it = bt->root;
      while (it!=NULL)
      {
            int cmp = bt->cmp(it->data,val);
            if (cmp<0) it = it->left_child;
            else if (cmp>0) it = it->right_child;
            else 
            {
                  DBG("Found node %d\n",*(int*)it->data);
                  return it;
            }
      }
      return NULL;
}


/**
 *  @brief Deletion
 *  
 *  There are four possibilities regarding the node
 *  we want to delete:
 *  
 *  1. It doesn't exist - trivial case.
 *  2. It exists and has no child - trivial case,
 *  simply remove it from the tree.
 *  3. It exits and has one child - trivial case,
 *  simply replace it with it's child.
 *  4. It exists and has two children.
 *  
 *  The last case is the only one that is non-trivial. 
 *  After identifying the node x in the tree (the one
 *  we want removed), we need to find it's successor y, 
 *  which will have at most one child, and replace x
 *  with y. y's child z becomes child of y's parent.
 *  
 *  Ref. Cormen & Leiserson 2 ed p 253
 *  
 *  @param [in] 
 *  @param [in] 
 *  @return 
 */
node* tree_delete(binary_tree* bt, void* value)
{
      node* z = tree_search(bt, value);

      node* y = NULL;
      
      if (z!=NULL) 
      {
            if ((z->left_child == NULL) | (z->right_child == NULL)) y = z;
            else y = tree_successor(bt, z);
            
            node* x = NULL;
            
            if    (y->left_child != NULL) x = y->left_child;
            else  x = y->right_child;
            
            if (x!=NULL) x->parent = y->parent;
            
            if (y->parent == NULL) bt->root = x;
            else if (y == y->parent->left_child) y->parent->left_child = x;
            else y->parent->right_child = x;
            
            if (y != z) z->data = y->data;
      }
      
      return y;
}


