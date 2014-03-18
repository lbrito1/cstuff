#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <math.h>
#include <assert.h>
#include "comparators.c"

#define PARENT(i) i>>1
#define LEFT(i) i<<1
#define RIGHT(i) (i<<1)+1
static inline void exch(void** a, void** b) { void* p = *a; *a = *b; *b = p; }

typedef struct {
      void** array;
      int array_size;
      int heap_size;
      int (*cmp) (void*, void*);
} heap;

heap* new_heap(int size, int (*compare) (void*, void*))
{
      heap* h = malloc(sizeof(heap));
      h->array = malloc(sizeof(void*)*size);
      h->array_size = size;
      h->heap_size = 0;
      h->cmp = compare;
      return h;
}

void heapify(heap* h, int idx)
{
      int l = LEFT(idx);
      int r = RIGHT(idx);
      int largest = idx;
      
      if ((l<=h->heap_size) && (h->cmp(h->array[l], h->array[idx]) > 0)) largest = l;
      if ((r<=h->heap_size) && (h->cmp(h->array[r], h->array[largest]) > 0)) largest = r;
      
      if (largest != idx) 
      {
            exch(&h->array[idx], &h->array[largest]);
            heapify(h, largest);
      }
}
void build_heap(heap* h)
{
      int i;
      for(i = h->heap_size>>1; i>0; i--) heapify(h, i);
}

void heapsort(heap* h)
{
      build_heap(h);
      int i;
      for (i = h->heap_size; i>1; i--)
      {
            exch(&(h->array[1]), &h->array[i]);
            h->heap_size--;
            heapify(h,1);
      }
}

void* pop(heap* h)
{
      if(h->heap_size<1) return NULL;
      void* max = h->array[1];
      h->array[1] = h->array[h->heap_size--];
      heapify(h,1);
      return max;
}

void push(heap* h, void* k)
{
      h->heap_size++;
      int i;
      for (i = h->heap_size; i>1 && h->cmp(h->array[PARENT(i)], k) < 0; i = PARENT(i)) h->array[i] = h->array[PARENT(i)];
      h->array[i] = k;
}

#ifdef _DEBUGGING
int main() 
{
      heap* h = new_heap(20, compare_integer);
      srand(time(NULL));
      int i;
      for (i=1;i<20;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = rand()%1000;
            //h->array[i] = data;
            push(h,data);
      }
      for (i=1;i<20;i++) printf("\n[%d]\t%d",i,*(int*)h->array[i]);
      h->heap_size = 19;
      
      printf("\n\n\n");
           
      for (i=1;i<20;i++) printf("\n[%d]\t%d",i,*(int*)pop(h));
      
      return 0;
}
#endif