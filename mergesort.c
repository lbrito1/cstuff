#include "linked_list.c"
#include <time.h>
#include <stdlib.h>

#if !defined _TEST_SIZE_MSORT && defined _DEBUGGING
#define _TEST_SIZE_MSORT 10
#endif


void halve(linked_list* list, linked_list* left, linked_list* right);
element* merge(element* a, element* b, int (*cmp) (void*, void*));

element* mergesort(linked_list* list)
{
      linked_list *left = new_list(list->cmp);
      linked_list *right = new_list(list->cmp);
      
      if (list->head == NULL || list->head->next == NULL) return list->head;
      
      halve(list, left, right);
      
      return merge(mergesort(left),mergesort(right), list->cmp);
}

void halve(linked_list* list, linked_list* left, linked_list* right)
{
      element* middle = list->head;
      if (middle!=NULL) {
      int half = (int) ((list->size)/2.0f), i=0;
      while (++i<half) middle = middle->next;
      element* middle_head = middle->next;
      middle->next = NULL;
      
      left->head = list->head;
      left->size = (list->size)-half;
      
      right->head = middle_head;
      right->size = half;}
}

element* merge(element* a, element* b, int (*cmp) (void*, void*))
{
      element* c = new_element(NULL);
      element* merged = c;
      while (a != NULL && b != NULL) 
      {
            if (cmp(a->data, b->data) > 0)
            {
                  c->next = a;
                  a = a->next;
            }
            else
            {
                  c->next = b;
                  b = b->next;
            }
            c = c->next;
      }
      c->next = (a == NULL) ? b : a;
      return merged->next;
}


int main()
{
      linked_list* list = new_list(compare_integer);
      
      srand(time(NULL));
      
      int* x = malloc(sizeof(int)*_TEST_SIZE_MSORT);
      
      int i=0;
      for (;i<_TEST_SIZE_MSORT;i++)
      {
            x[i] = rand();
            add(list, &(x[i]));
      }
      
      element* xx = list->head;
      i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      printf("\n\nSorted:");
      xx = mergesort(list);
      list->head = xx;
      i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      return 0;
}