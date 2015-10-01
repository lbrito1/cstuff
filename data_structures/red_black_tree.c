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

node* rb_insert(binary_tree* bt, void* data, int uniqueness) {
    node *n = tree_insert(bt, data, uniqueness);
    node *gran, *r_uncle, *l_uncle;
    while(n != bt->root && n->parent->color == RED) {
        if (gran = grandpa(n)) { 
            if (gran->left_child == n->parent) {
                r_uncle = uncle(n, RIGHT);
                if (r_uncle && (r_uncle->color == RED)) {  //case 1
                    DBG("Case 1 L\n");
                    n->parent->color = BLACK;
                    r_uncle->color = BLACK;
                    gran->color = RED;
                    n = gran;
                }
                if (n == bt->root) break;
                r_uncle = uncle(n, RIGHT);
                if (grandpa(n) && (!r_uncle || r_uncle->color == BLACK)) {
                    if (n == n->parent->right_child) { // case 2
                        DBG("Case 2 L\n");
                        n = n->parent;
                        rb_left_rotate(bt, n);
                    }
                    DBG("Case 3 L\n");
                    if (n == bt->root) break;
                    n->parent->color = BLACK;           // case 3
                    gran = grandpa(n);
                    if (gran) gran->color = RED;
                    rb_right_rotate(bt, gran);
                }
            }
            else if (gran->right_child == n->parent) {
                l_uncle = uncle(n, LEFT);
                if (l_uncle && (l_uncle->color == RED)) {  //case 1
                    DBG("Case 1 R\n");
                    n->parent->color = BLACK;
                    l_uncle->color = BLACK;
                    gran->color = RED;
                    n = gran;
                }
                if (n == bt->root) break;
                l_uncle = uncle(n, LEFT);
                if ((gran = grandpa(n)) && (!l_uncle || l_uncle->color == BLACK)) {
                    if (n == n->parent->left_child) { // case 2
                        DBG("Case 2 R\n");
                        n = n->parent;
                        rb_right_rotate(bt, n);
                    }
                    DBG("Case 3 R\n");
                    if (n == bt->root) break;
                    n->parent->color = BLACK;           // case 3
                    gran = grandpa(n);
                    if (gran) gran->color = RED;
                    rb_left_rotate(bt, gran);
                }
            }
        }
    }
    bt->root->color = BLACK;
    return n;
}

void rb_left_rotate(binary_tree* bt, node* n) {
    DBG("Performing LEFT ROTATE (%c)...\n", *(char*)n->data);
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
}

void rb_right_rotate(binary_tree* bt, node* n) {
    DBG("Performing RIGHT ROTATE (%c)...\n", *(char*)n->data);
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
            n->parent->left_child = y;
        }
    }

    y->right_child = n;
    n->parent = y;
}


