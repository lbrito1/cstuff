/*
    File: red_black_tree.c

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


/*
 * A red-black tree is a binary search tree that satisfies the red-black properties:
 *
 * 1. Every node is either Black or Red
 * 2. All leaves are Black
 * 3. If a node is Red, then both of its children are Black
 * 4. Every path from a node to any of its leaves contains the same number of Black nodes
 *
 *
 */

#include <math.h>
#include "binary_search_tree.c"

#define RED 0
#define BLACK 1


void rb_left_rotate(binary_tree* bt, node* n);
void rb_right_rotate(binary_tree* bt, node* n);

void rb_insert(binary_tree* bt, void* data) {
    node* n = new_node(data);
    tree_insert(bt, n);
    while(n != bt->root && n->parent->color == RED) {
        node* grandpa = n->parent->parent;
        if (grandpa) { 
            if (grandpa->left_child == n->parent) {
                node* uncle = grandpa->right_child;
                if (uncle) {
                    if (uncle->color == RED) {  //case 1
                        DBG("\nCase 1 L");
                        n->parent->color = BLACK;
                        uncle->color = BLACK;
                        grandpa->color = RED;
                        n = grandpa;
                    }
                }
                if (n == bt->root) break;
                if (!uncle || uncle->color == BLACK) {
                    if (n == n->parent->right_child) { // case 2
                        DBG("\nCase 2 L");
                        n = n->parent;
                        rb_left_rotate(bt, n);
                    }
                    n->parent->color = BLACK;           // case 3
                    grandpa->color = RED;
                    rb_right_rotate(bt, grandpa);
                }
                
            }
            else if (grandpa->right_child == n->parent) {
                node* uncle = grandpa->left_child;
                if (uncle) {
                    if (uncle->color == RED) {  //case 1
                        DBG("\nCase 1 R");
                        n->parent->color = BLACK;
                        uncle->color = BLACK;
                        grandpa->color = RED;
                        n = grandpa;
                    }
                }
                if (n == bt->root) break;
                if (!uncle || uncle->color == BLACK) {
                    if (n == n->parent->left_child) { // case 2
                        DBG("\nCase 2 R");
                        n = n->parent;
                        rb_right_rotate(bt, n);
                    }
                    n->parent->color = BLACK;           // case 3
                    grandpa->color = RED;
                    rb_left_rotate(bt, grandpa);
                    
                }
            }
        }
    }
    bt->root->color = BLACK;
}

void rb_left_rotate(binary_tree* bt, node* n) {
    DBG("\nPerforming LEFT ROTATE...");
    node* y = n->right_child;

    n->right_child = y->left_child;
    if (y->left_child) y->left_child->parent = n;
    y->parent = n->parent;

    if (!n->parent) {
     bt->root = y;   
    }
    else {
        if (n == n->parent->left_child) {
            n->parent->left_child = y;
        }
        else {
            n->parent->right_child = y;
        }
    }

    y->left_child = n;
    n->parent = y;
    DBG("\nDone");
}

void rb_right_rotate(binary_tree* bt, node* n) {
    DBG("\nPerforming RIGHT ROTATE...");
    node* y = n->left_child;

    n->left_child = y->right_child;
    if (y->right_child) y->right_child->parent = n;
    y->parent = n->parent;

    if (!n->parent) {
     bt->root = y;   
    }
    else {
        if (n == n->parent->right_child) {
            n->parent->right_child = y;
        }
        else {
            n->parent->right_child = y;
        }
    }

    y->right_child = n;
    n->parent = y;
    DBG("\nDone");
}




