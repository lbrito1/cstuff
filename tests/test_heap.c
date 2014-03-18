#include "../utils/comparators.c"
#include "../data_structures/heap.c"
#include <time.h> 
#include <stdio.h>

#ifndef _TEST_SIZE
#define _TEST_SIZE 100
#endif

int main() 
{
      heap* h = new_heap(_TEST_SIZE, ORD_ASC, compare_integer);
      srand(time(NULL));
      int i;
      for (i=0;i<_TEST_SIZE;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = rand()%1000;
            push(h,data);
            printf("\n[%d]\t%d",i+1,*(int*)h->array[i+1]);
      }
      printf("\n\n\n");
           
      for (i=0;i<_TEST_SIZE+5;i++) 
      {
            int* x = pop(h);
            if (x!=NULL) printf("\n[%d]\t%d",i+1,*x);
      }
      
      return 0;
}