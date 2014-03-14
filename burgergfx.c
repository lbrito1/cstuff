#include <stdio.h>
#include <stdlib.h>

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
      return (int) (b->w*x);
}

int get_norm_y(burger* b, double y)
{
      return (int) (b->h*y);
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
      int i = 0, j = 0,z=0;
      for (;i<bgfx->h;i++)
      {
            if (i==0) 
            {
                  z = 0;
                  printf("/"); 
                  for (;z<bgfx->w;z++) printf("--");
                  printf("\\"); 
            }
            else if (i==bgfx->h-1)
            {
                  z = 0;
                  printf("\\"); 
                  for (;z<bgfx->w;z++) printf("--");
                  printf("/"); int z = 0;
            }
            for (j=0;j<bgfx->w;j++)
            {
                  printf("%c ",bgfx->burger_matrix[i+(j*bgfx->w)]);
            }
            printf("\n");
      }
}

void put_line(burger* bgfx, double dx1, double dx2, double dy1, double dy2)
{
      int x1 = get_norm_x(bgfx, dx1);
      int y1 = get_norm_y(bgfx, dy1);
      int x2 = get_norm_x(bgfx, dy1);
      int y2 = get_norm_y(bgfx, dy2);
      

      float a = (float)(y1-y2)/(float)(x1-x2);
      int i = 0;
      for (i=x1; i<x2 ;i++)
      {
            int y = (int) (a*i) + y1;
            put_burger_int(bgfx, i, y, '*');
      }
}

/*
int main() 
{
      burger* b = create(32,32);
      clean_burger(b);
      put_line(b, 0.1,0.1, 0.9,0.7);
      put_burger(b,0.05,0.5,'c');
      print_burger(b);
      return 0;
}


*/




















