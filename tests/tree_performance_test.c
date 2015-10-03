/*
 *  File: tree_performance_test.c
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
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

#define NOINCLUDE

#include "../data_structures/binary_search_tree.c"
#include "../data_structures/avl_tree.c"
#include "../data_structures/red_black_tree.c"

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

void visit(node* n)
{
#ifdef _DEBUG
    printf("Visited node #%d \tPARENT=%d \tHEIGHT=%d, COLOR=%d\n",
    *(int*)n->data,
    n->parent?*(int*)n->parent->data:-1,
    n->height,
    n->color
    );
#endif
}


double insert_nodes(int* data, int n, binary_tree* bt, node* (insert_fun(binary_tree* bt, void* data, int uniqueness))) {
    int i;
    srand(time(NULL));
    double time = get_time();
    for(i=0; i<n; i++) 
    {           
#ifdef WORST
        data[i] = i;
#else
        data[i] = rand()%(n*1000);
#endif
        (*insert_fun) (bt, (void*) &data[i], TRUE);
    }
    return get_time() - time;
}

double traversal(binary_tree* bt) {
    double time = get_time();
    depth_first(bt, visit, IN_ORDER);
    return get_time() - time;
}

// Searches ALL nodes in data.
double search_nodes(int* data, int n, binary_tree* bt) {
    int i;
    double time = get_time();
    for (i = 0; i < (int)(n/10.0); i++) {
        int* val = &data[rand()%n];
        tree_search(bt, (void*) val);
    }
    return get_time() - time;
}

void benchmark(double* insert_time, double* search_time, int i, node* (*insertion) (binary_tree* bt, void* data, int uniqueness)) {
    int* d = malloc(sizeof(int)*i);
    binary_tree* bst = new_binary_tree(compare_integer, ORD_ASC);
    *insert_time = insert_nodes(d, i, bst, insertion);
    *search_time = search_nodes(d, i, bst);
    free(d);
    free(bst);
}

int main(void)
{
#ifdef WORST
    FILE *f = fopen("tree_performance_worst.csv", "w");
#else
    FILE *f = fopen("tree_performance.csv", "w");
#endif

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f,"n, bst_insert, bst_search, avl_insert, avl_search, rb_insert, rb_search\n");

    int ts = 100000;
    int step = 1000;
    int interpolation_thres = 10000; 
    int interpolation_step = step * 10;
    int original_step = step;
#ifndef WORST 
    interpolation_thres = 99999999; // we don't need to interpolate when using avg case
#endif

    int i;
    double bst_insert_time,bst_search_time,avl_insert_time,avl_search_time,rb_insert_time,rb_search_time;
    double bst_insert_time_interp = -1,bst_search_time_interp,avl_insert_time_interp,avl_search_time_interp,rb_insert_time_interp,rb_search_time_interp;
    for (i=0; i < ts; i+=step) {
        if (i==0) continue;

        if (i < interpolation_thres) {
            benchmark(&bst_insert_time, &bst_search_time, i, &tree_insert);
            benchmark(&avl_insert_time, &avl_search_time, i, &avl_insert);
            benchmark(&rb_insert_time, &rb_search_time, i, &rb_insert);
            fprintf(f,"%d,%f,%f,%f,%f,%f,%f\n", i, bst_insert_time, bst_search_time, avl_insert_time, avl_search_time, rb_insert_time, rb_search_time);
        }
        else {
            step = interpolation_step;

            if (bst_insert_time_interp > 0) {   // use data from previous interpolation
                bst_insert_time = bst_insert_time_interp;
                avl_insert_time = avl_insert_time_interp;
                rb_insert_time = rb_insert_time_interp;
            }
            else { // first ever interpolation; needs to calculate both points
                benchmark(&bst_insert_time, &bst_search_time_interp, i, &tree_insert);
                benchmark(&avl_insert_time, &avl_search_time_interp, i, &avl_insert);
                benchmark(&rb_insert_time, &rb_search_time_interp, i, &rb_insert);
            }

            benchmark(&bst_insert_time_interp, &bst_search_time_interp, i+step, &tree_insert);
            benchmark(&avl_insert_time_interp, &avl_search_time_interp, i+step, &avl_insert);
            benchmark(&rb_insert_time_interp, &rb_search_time_interp, i+step, &rb_insert);

            int j;
            double t;
            for (j = i; j < i + step; j+= original_step) {
                t = (j-i)/((double)step); 
                fprintf(f,"%d,%f,%f,%f,%f,%f,%f\n", j,
                    (bst_insert_time * (1 - t) + t * bst_insert_time_interp), 
                    (bst_search_time * (1 - t) + t * bst_search_time_interp), 
                    (avl_insert_time * (1 - t) + t * avl_insert_time_interp), 
                    (avl_search_time * (1 - t) + t * avl_search_time_interp), 
                    (rb_insert_time * (1 - t) + t * rb_insert_time_interp), 
                    (rb_search_time * (1 - t) + t * rb_search_time_interp)); 
            }
        }
    }
    return 0;
}
