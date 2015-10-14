// gcc data_structures/src/vector.c data_structures/src/linked_list.c utils/src/comparators.c utils/src/burgergfx.c data_structures/src/red_black_tree.c data_structures/tests/rb_test.c -o data_structures/tests/bin/rb_test.out -D_DEBUG -lm


/*
 *  File: rb_test.c
 *
 *  Compilation: gcc -D_DEBUG tests/rb_test.c -o tests/rb_test.out -lm
 *
 *  You will need a terminal with ANSI escape code coloring to be able
 *  to see node colors.
 *
 *  Copyright (c) 2015 Leonardo Brito <lbrito@gmail.com>
 *
 *  This software is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write the Free Software Foundation, Inc., 51
 *  Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <time.h>
#include "../../include/red_black_tree.h"
#include "../../../utils/include/burgergfx.h"
#include "../../../utils/include/colors.h"
#include "../../../utils/include/debug.h"
#include "../../../utils/include/comparators.h"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy)
{
    char should_put = r->color == 0 ? 'R' : 'B';
    set_color(burg, sx, sy, r->color == 0 ? ANSI_COLOR_RED : ANSI_COLOR_RESET);
    put_burger(burg, sx,sy,*(char*) r->data);

    int h = height(r);
    float spacing = h * h * (burg->default_spacing/10);

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
    DBG("Visited node #%d (%c) \tPARENT=%d (%c)\tHEIGHT=%d, COLOR=%d\n",
    *(int*)n->data,
    *(int*)n->data,
    n->parent?*(int*)n->parent->data:-1,
    n->parent?*(int*)n->parent->data:'*',
    height(n),
    n->color
    );
}


void print_rb(burger* burg, binary_tree* bt)
{
    clean_burger(burg);
    print_tree(burg,bt->root,0.5,0.1);
    print_burger(burg);
}

int main(void)
{
    burg = create(256,256);
    binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);
       
    int ts = 21;
    srand(time(NULL));
    int i;

    int predef[] = {84,79,72,68,77,78,83,89,88,87,70,69,82,71,81,73,67,75,65,80,85};

    for(i=0;i<ts;i++) 
    {           
        DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
#ifndef NO_GFX
        if (bt->root) print_rb(burg, bt);
#endif
        int* data = malloc(sizeof(int));
        *data = predef[i];
#ifdef RAND
        *data = 65+(rand()%(25));
#endif
        rb_insert(bt, (void*)data, TRUE);
        DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
#ifndef NO_GFX
        print_rb(burg, bt);            
#endif
        depth_first(bt, visit, IN_ORDER);
        print_insert_order(bt);
    }
    
    return 0;
}
#endif
