//  gcc data_structures/src/linked_list.c data_structures/src/avl_tree.c utils/src/comparators.c utils/src/burgergfx.c data_structures/tests/avl_test.c -o data_structures/tests/bin/avl_test.out -D_DEBUG -lm



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
#include "../../include/avl_tree.h"
#include "../../../utils/include/debug.h"
#include "../../../utils/include/comparators.h"
#include "../../../utils/include/burgergfx.h"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy) {
  float spacing = (r->height+1) * (r->height+1) * (burg->default_spacing/10);
  put_burger(burg, sx,sy,*(char*)r->data);

  if (r->left_child) {
    print_tree(burg, r->left_child, sx-spacing, sy+spacing);
    put_line(burg, sx, sy, sx-spacing, sy+spacing);
  }
  if (r->right_child) {
    print_tree(burg, r->right_child,sx+spacing,sy+spacing);
   put_line(burg, sx, sy, sx+spacing, sy+spacing);
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
      print_tree(burg,bt->root,0.5,0.1);
      print_burger(burg);
}

int main()
{
      burg = create_bgfx(256,256);
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 30;     
      srand(time(NULL));
      int i;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%(ts));
            DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
#ifndef NOGFX
            if (bt->root) print_avl(burg, bt);
#endif
            avl_insert(bt, data, TRUE);
            DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
#ifndef NOGFX
            print_avl(burg, bt);            
#endif
      }
      
      depth_first(bt, visit, IN_ORDER);


      return 0;
}
#endif
