/*
    File: burgergfx.h

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

#ifndef BURGERGFX_H
#define BURGERGFX_H

typedef struct {
      int w,h;
      char* burger_matrix;
      char** color_matrix;
      int minx,maxx,miny,maxy; // framing
      float default_spacing;
} burger;

burger* create(int w, int h);
int get_norm_x(burger* b, double x);
int get_norm_y(burger* b, double y);
void clean_burger(burger* b);
void update_frame(burger* b, int x, int y);
void put_burger(burger* b, double dx, double dy, char c);
int occupied(burger* b, int x, int y);
void put_burger_scooch(burger* b, double dx, double dy, char c, int direction);
void put_burger_int(burger* b, int x, int y, char c);
void soft_put_burger_int(burger* b, int x, int y, char c);
void set_color_scooch(burger* b, double dx, double dy, char* color, int direction);
void set_color(burger* b, double dx, double dy, char* color);
void print_burger(burger* bgfx);
void put_line(burger* bgfx, double dx1, double dy1, double dx2, double dy2);
void put_line_int(burger* bgfx, int x1, int y1, int x2, int y2);

#endif