#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
      int w,h;
      char* burger_matrix;
} burger;

burger* create(int w, int h)
{
      burger* bgfx = malloc(sizeof(burger));
      bgfx->w = w; 
      bgfx->h = h;
      bgfx->burger_matrix = malloc(sizeof(char)*w*h);
      int i=0;
      for (;i<w*h;i++) bgfx->burger_matrix[i] = '.';
      return bgfx;
}

int get_norm_x(burger* b, double x)
{
      return (int) round(b->w*x);
}

int get_norm_y(burger* b, double y)
{
      return (int) round(b->h*y);
}

void clean_burger(burger* b)
{
      int i=0;
      for (;i<b->w*b->h;i++) b->burger_matrix[i] = ' ';
}

void put_burger(burger* b, double dx, double dy, char c)
{
      int x = get_norm_x(b, dx);
      int y = get_norm_y(b, dy);
      b->burger_matrix[y+(x*b->w)] = c;
}

void put_burger_int(burger* b, int x, int y, char c)
{
      b->burger_matrix[y+(x*b->w)] = c;
}

void print_burger(burger* bgfx)
{
      
      int i = 0, j = 0;
      printf("\n");
      for (;i<(bgfx->w/2)-2;i++) printf("  ");
      printf("Burger\n");
      for (i=0;i<bgfx->h;i++)
      {
            for (j=0;j<bgfx->w;j++)
            {
                  printf("%c ",bgfx->burger_matrix[i+(j*bgfx->w)]);
            }
            printf("\n");
      }
}

void put_line(burger* bgfx, double dx1, double dy1, double dx2, double dy2)
{
      int x1 = get_norm_x(bgfx, dx1);
      int y1 = get_norm_y(bgfx, dy1);
      int x2 = get_norm_x(bgfx, dx2);
      int y2 = get_norm_y(bgfx, dy2);
   
      int i = 0;


      
      float a = (float)(y2-y1)/(float)(x2-x1);
      
      if (x1<x2) 
      {
            for (i=x1; i<x2 ;i++)
            {
                  int x = i - x1;
                  int y = (int) (a*x) + (y1<y2 ? y2 : y1);
                  put_burger_int(bgfx, i, y, '.');
            }
      }
      else 
      {
            for (i=x2; i<x1; i++)
            {
                  int x = i - x2;
                  int y = (int) (a*x) + (y1<y2 ? y2 : y1);
                  put_burger_int(bgfx, i, y, '.');
            }
      }
}

/*
int main() 
{
      burger* b = create(30,30);
      
      double x1, x2, y1, y2;
      x1 = 0.9;
      y1= 0.9;
      x2 = 0.1;
      y2 = 0.1;
      
      put_line(b, x1,y1,x2,y2);
      
      put_burger(b,x1,y1,'F');
      put_burger(b,x2,y2,'T');

      print_burger(b);
      return 0;
}
*/






















