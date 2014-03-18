#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <math.h>
#include "comparators.c"

#define PARENT(i) i>>1
#define LEFT(i) i<<1
#define RIGHT(i) (i<<1)+1

typedef struct {
      void** array;
      int array_size;
      int heap_size;
      int (*cmp) (void*, void*);
} heap;

inline void* get(heap* h, int idx) { return h->array[idx]; }
inline void set(heap* h, int idx, void* d) { h->array[idx] = d; }

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
      
      if ((l<=h->heap_size) && (h->cmp(get(h,l), get(h,idx)) > 0)) largest = l;
      if ((r<=h->heap_size) && (h->cmp(get(h,r), get(h,largest)) > 0)) largest = r;
      
      if (largest != idx) 
      {
            void* temp = get(h,largest);
            set(h, largest, get(h,idx));
            set(h, idx, temp);
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
      for (i = h->heap_size; i>2; i--)
      {
            void* temp = get(h,1);
            set(h,1,get(h,i));
            set(h,i,temp);
            h->heap_size--;
            heapify(h,1);
      }
}

int main() 
{
      heap* h = new_heap(10, compare_integer);
      srand(time(NULL));
      int i;
      for (i=1;i<8;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = rand()%1000;
            h->array[i] = data;
      }
      for (i=1;i<8;i++) printf("\n[%d]\t%d",i,*(int*)h->array[i]);
      h->heap_size = 7;
      heapsort(h);
      printf("\n\nHeapified\n\n");
      
      for (i=1;i<8;i++) printf("\n[%d]\t%d",i,*(int*)h->array[i]);
      
      
      
      return 0;
}