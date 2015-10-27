/*
    File: burgergfx.c

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

#include "../include/burgergfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/colors.h"
#include "../include/debug.h"
#include "../include/comparators.h"

int gt(int a, int b) { return a > b ? a : b; }
int lt(int a, int b) { return a < b ? a : b; }

void exch(int* a, int* b) { int p = *a; *a = *b; *b = p; }

int next_color = 0;

/**
 *  @brief Create a new w x h burger
 *  
 *  @param [in] w width
 *  @param [in] h height
 *  @return pointer to burger
 */
burger* create_bgfx(int w, int h)
{
      burger* bgfx = malloc(sizeof(burger));
      bgfx->w = w; 
      bgfx->h = h;
      bgfx->minx = w+1;
      bgfx->miny = h+1;
      bgfx->maxx = 0;
      bgfx->maxy = 0;
      bgfx->burger_matrix = malloc(sizeof(char)*w*h);
      bgfx->color_matrix = malloc(sizeof(char*)*w*h);
      bgfx->default_spacing = 0.02;
      int i=0;
      for (;i<w*h;i++) {
          bgfx->burger_matrix[i] = '.'; 
          bgfx->color_matrix[i] = NULL;
      }
      return bgfx;
}

void delete_burger(burger* b) {
  free(b->burger_matrix);
  free(b->color_matrix);
  free(b);
}

/**
 *  @brief Get the appropriate cell from a normalized x coordinate
 *  
 *  @param [in] b burger
 *  @param [in] x normalized coordinate
 *  @return cell index
 */
int get_norm_x(burger* b, double x)
{
      return (int) round(b->w*x);
}

/**
 *  @brief Get the appropriate cell from a normalized y coordinate
 *  
 *  @param [in] b burger
 *  @param [in] y normalized coordinate
 *  @return cell index
 */
int get_norm_y(burger* b, double y)
{
      return (int) round(b->h*y);
}

/**
 *  @brief Fill the burger with whitespace
 *  
 *  @param [in] b 

 */
void clean_burger(burger* b)
{
      int i=0;
      for (;i<b->w*b->h;i++) b->burger_matrix[i] = ' ';
}

void update_frame(burger* b, int x, int y)
{
    b->maxx = gt(x,b->maxx);
    b->minx = lt(x,b->minx);
    b->maxy = gt(y,b->maxy);
    b->miny = lt(y,b->miny);
}

/**
 *  @brief Put char in cell
 *  
 *  @param [in] b  burger
 *  @param [in] dx normalized x position
 *  @param [in] dy normalized y position
 *  @param [in] c  char to be put
 */
void put_burger(burger* b, double dx, double dy, char c)
{
      int x = get_norm_x(b, dx);
      int y = get_norm_y(b, dy);
      update_frame(b,x,y);
      b->burger_matrix[y+(x*b->w)] = c;
}


char get_burger(burger* b, int x, int y) {
  return b->burger_matrix[y+(x*b->w)];
}

int occupied(burger* b, int x, int y) 
{
    char candidate = b->burger_matrix[y+(x*b->w)];
    if (!(candidate == ' ' || candidate == '.')) {
        return TRUE;
    }
    return FALSE;
}

void put_burger_scooch(burger* b, double dx, double dy, char c, int direction)
{
      int x = get_norm_x(b, dx);
      int y = get_norm_y(b, dy);
      if (occupied(b, x, y)) x += direction;
      update_frame(b,x,y);
      b->burger_matrix[y+(x*b->w)] = c;
}


/**
 *  @brief Put char in cell
 *  
 *  @param [in] b burger
 *  @param [in] x cell index
 *  @param [in] y cell index
 *  @param [in] c char to be put
 */
void put_burger_int(burger* b, int x, int y, char c)
{
      update_frame(b,x,y);
      b->burger_matrix[y+(x*b->w)] = c;
}

/**
 *  @brief Put char in cell
 *  
 *  @param [in] b burger
 *  @param [in] x cell index
 *  @param [in] y cell index
 *  @param [in] c char to be put
 */
void soft_put_burger_int(burger* b, int x, int y, char c)
{
      if (b->burger_matrix[y+(x*b->w)] == ' ') put_burger_int(b,x,y,c);
}

void set_color_scooch(burger* b, double dx, double dy, char* color, int direction) 
{
    int x = get_norm_x(b, dx);
    int y = get_norm_y(b, dy);
    if (occupied(b, x, y)) x += direction;
    b->color_matrix[y+(x*b->w)] = color;
}

void set_color(burger* b, double dx, double dy, char* color) 
{
    int x = get_norm_x(b, dx);
    int y = get_norm_y(b, dy);
    b->color_matrix[y+(x*b->w)] = color;
}

/**
 *  @brief Print the current burger
 *  
     *  @param [in] bgfx 
 */
void print_burger(burger* bgfx)
{
      int i = 0, j = 0;

      //Header
      printf("\n");
      int mid = ((bgfx->maxx-bgfx->minx)/2);
      for (;i<mid;i++) printf(" ");
      printf(ANSI_COLOR_YELLOW "Burger" ANSI_COLOR_RESET);
      printf("\n");
      
      //Content
      for (i = bgfx->miny; i < lt(bgfx->maxy + 1, bgfx->h); i++)
      {
            for (j=bgfx->minx; j < lt(bgfx->maxx + 1, bgfx->w); j++)
            {
                  char* color = bgfx->color_matrix[i+(j*bgfx->w)];
                  if (color) printf("%s", color);
                  printf("%c",bgfx->burger_matrix[i+(j*bgfx->w)]);
                  printf(ANSI_COLOR_RESET);
            }
            printf("\n");
      }
      //DBG("[GFX] Current frame: min(%d, %d), max(%d, %d)\n",bgfx->minx,bgfx->miny,bgfx->maxx,bgfx->maxy);
}

/**
 *  @brief Draw line from point 1 to point 2 on burger
 *  
 *  @param [in] bgfx 
 *  @param [in] dx1  point 1 normalized x coord
 *  @param [in] dy1  point 1 normalized y coord
 *  @param [in] dx2  point 2 normalized x coord
 *  @param [in] dy2  point 2 normalized y coord
 */
void put_line(burger* bgfx, double dx1, double dy1, double dx2, double dy2)
{
    int x1 = get_norm_x(bgfx, dx1);
    int y1 = get_norm_y(bgfx, dy1);
    int x2 = get_norm_x(bgfx, dx2);
    int y2 = get_norm_y(bgfx, dy2);
    put_line_int(bgfx, x1, y1, x2, y2); 
}

void put_line_int(burger* bgfx, int x1, int y1, int x2, int y2)
{
    if (x2<x1) {
        exch(&x1,&x2);
        exch(&y1,&y2);
        //DBG("\nDRAWING LINE @ (%d,%d, %d,%d)",x1,y1,x2,y2);
    }

    float a = (float)(y2-y1)/(float)(x2-x1);
    int i;
    if (x1!=x2) {
        for (i=x1; i<x2 ;i++) {
          int x = i - x1;
          int y = (int) (a*x) + y1;
          soft_put_burger_int(bgfx, i, y, '.');
        }
    }
    else {
        for (i=y1; i<y2; i++) {
          soft_put_burger_int(bgfx, x1, i, '.');
        }
    }
}

