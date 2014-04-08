/*
    File: avl_test.c
    
    Note: when printing a tree, burgergfx may overlay two nodes, 
    specifically one left child with one right child of two siblings,
    
    e.g.

                            G
                          .   .
                        .       .
                      .           .
                    .               .
                  C .                 P .
                .     .             .     .
              .         .         .         .
            .             .     .             .
        A .                 K .                 X


     Both C's right child and P's left child are set to the same
     position; whichever was written later gets printed.
     
     As a workaround if you're debugging, always print each node's
     height and/or children, so you'll know if C and P have children
     or not.


    
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


#include <time.h>
#include "../data_structures/avl_tree.c"
#include "../utils/burgergfx.c"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy, int pair)
{
      put_burger(burg, sx,sy,*(char*)r->data);
      
      float rf = 0;//(pair==0) ? -0.05 : 0;
      
      if (r->left_child) 
      {
            print_tree(burg, r->left_child, sx-0.1+rf, sy+0.1, (pair==0) ? 1 : 0);
            put_line(burg, sx, sy, sx-0.1+rf, sy+0.1);
      }
      if (r->right_child) 
      {
            print_tree(burg, r->right_child,sx+0.1,sy+0.1, (pair==0) ? 1 : 0);
            put_line(burg, sx, sy, sx+0.1+rf, sy+0.1);
      }
}

#ifdef _DEBUG
void visit(node* n)
{
      DBG("Visited node #%d (%c) \tPARENT=%d (%c)\tHEIGHT=%d\n",
      *(int*)n->data,
      *(int*)n->data,
      n->parent?*(int*)n->parent->data:-1,
      n->parent?*(int*)n->parent->data:'*',
      n->height
      );
}


void print_avl(burger* burg, binary_tree* bt)
{
      clean_burger(burg);
      print_tree(burg,bt->root,0.5,0.1, 0);
      print_burger(burg);
}

int main()
{
      burg = create(48,48);
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 8;     
      srand(time(NULL));
      int i;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%(25));
            node* n = new_node((void*) data);
            DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
            if (bt->root) print_avl(burg, bt);
            avl_insert(bt, n);
            DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
            print_avl(burg, bt);            
      }
      
      depth_first(bt, visit, IN_ORDER);


      return 0;
}
#endif