#include "../../../utils/include/comparators.h"
#include "../../include/heap.h"
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>

#ifndef _TEST_SIZE
#define _TEST_SIZE 100
#endif

#ifdef _DEBUG
int main() 
{
      heap* h = new_heap(_TEST_SIZE, ORD_ASC, compare_integer);
      srand(time(NULL));
      int i;
      for (i=0;i<_TEST_SIZE;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = rand()%1000;
            push_heap(h,data);
            printf("\n[%d]\t%d",i+1,*(int*)h->array[i+1]);
      }
      printf("\n\n\n");
           
      for (i=0;i<_TEST_SIZE+5;i++) 
      {
            int* x = pop_heap(h);
            if (x!=NULL) printf("\n[%d]\t%d",i+1,*x);
      }
      
      return 0;
}
#endif