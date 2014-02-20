#include "linked_list.c"
#include <stdint.h>


void halve(linked_list* list, linked_list* left, linked_list* right);
element* merge(element* a, element* b, int (*cmp) (void*, void*));

element* mergesort(linked_list* list)
{
      linked_list *left = new_list(list->cmp);
      linked_list *right = new_list(list->cmp);
      
      if (list->head == NULL || list->head->next == NULL) return list->head;
      
          halve(list, left, right);
      
      element* l, *r;
      l = left->head;
      r = right->head;
      if (l!=NULL && r!=NULL) 
      {
            do {printf("\nL\t%d",*(int*)l->data);} while ((l=l->next)!=NULL);
            printf("\n");
            do {printf("\nR\t%d",*(int*)r->data);} while ((r=r->next)!=NULL);
      }
      
  
      
      return merge(mergesort(left),mergesort(right), list->cmp);
}

void halve(linked_list* list, linked_list* left, linked_list* right)
{
      element* middle = list->head;
      if (middle!=NULL) {
      int half = (int) ((list->size)/2.0f), i=0;
      while (i++<half) middle = middle->next;
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
            printf("\ncomparing %d and %d = %d",*(int*)a->data, *(int*)b->data,cmp(a,b));
            if (cmp(a,b) > 0)
            {
                  printf("\tchose %d",*(int*)a->data);
                  c->next = a;
                  a = a->next;
            }
            else
            {
            printf("\tchose %d",*(int*)b->data);
                  c->next = b;
                  b = b->next;
            }
            c = c->next;
      }
      c->next = (a == NULL) ? b : a;
      
      element* t = merged;
      while ((t = t->next) != NULL) printf("\n\t%d",*(int*)t->data);
      
      return merged->next;
}


int main()
{
      linked_list* list = new_list(compare_integer);
      int* x = malloc(sizeof(int));
      int* y = malloc(sizeof(int));
      int* w = malloc(sizeof(int));
      
      *x = 10;
      *y = 100;
      *w = 0;
            
     
      
      add(list, x);
      add(list, y);
      add(list, w);

       //list->cmp(list->head->data, list->head->next->data);
      
      element* xx = list->head;
      int i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      xx = mergesort(list);
      list->head = xx;
      i=0;
      do { printf("\n[%d]\t%d",i++,*((int*)xx->data)); 
      } while ((xx=xx->next)!=NULL);

      return 0;
}