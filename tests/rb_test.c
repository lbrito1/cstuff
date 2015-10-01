/*
 *  File: rb_test.c
 *
 *  Compilation: gcc -D_DEBUG tests/rb_test.c -o tests/rb_test.bin -lm
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
#include "../data_structures/red_black_tree.c"
#include "../utils/burgergfx.c"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy, int left)
{
    char should_put = r->color == 0 ? 'R' : 'B';
    set_color_scooch(burg, sx, sy, r->color == 0 ? ANSI_COLOR_RED : ANSI_COLOR_RESET, left);
    put_burger_scooch(burg, sx,sy,*(char*) r->data, left);

    if (r->left_child) {
        print_tree(burg, r->left_child, sx-default_spacing, sy+default_spacing, 1);
        put_line(burg, sx, sy, sx-default_spacing, sy+default_spacing);
    }
    if (r->right_child) {
        print_tree(burg, r->right_child,sx+default_spacing,sy+default_spacing, -1);
        put_line(burg, sx, sy, sx+default_spacing, sy+default_spacing);
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
    n->height,
    n->color
    );
}


void print_rb(burger* burg, binary_tree* bt)
{
    clean_burger(burg);
    print_tree(burg,bt->root,0.5,0.1, 0);
    print_burger(burg);
}

int main(void)
{
    burg = create(48,48);
    binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);
       
    int ts = 8;
    srand(time(NULL));
    int i;

    //int predef[] = {76, 85, 81, 67, 72, 74, 86, 70};

    for(i=0;i<ts;i++) 
    {           
        DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
        if (bt->root) print_rb(burg, bt);
        int* data = malloc(sizeof(int));
        *data = 65+(rand()%(25));
        //*data = predef[i];
        rb_insert(bt, (void*)data, TRUE);
        DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
        print_rb(burg, bt);            
    }
    
    depth_first(bt, visit, IN_ORDER);
    return 0;
}
#endif
