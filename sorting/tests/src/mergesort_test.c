#include "../../include/mergesort.h"
#include "../../../utils/include/comparators.h"

int main()
{
      linked_list* list = new_list(compare_integer, sizeof(int));
      
      int testsize = 20;

      srand(time(NULL));
      
      int* x = malloc(sizeof(int));
      
      int i=0;
      for (;i<testsize;i++)
      {
            *x = rand()%100;
            add_ll(list, x);
      }
      free(x);
      
      element* xx = list->head;
      i=0;
      do { printf("\n[%d]\t%d\t%p",i++,*((int*)xx->data),(void*)xx); 
      } while ((xx=xx->next)!=NULL);

      printf("\n\nSorted:");
      xx = mergesort(list, DEC);
      list->head = xx;
      i=0;
      do { printf("\n[%d]\t%d\t%p",i++,*((int*)xx->data),(void*)xx); 
      } while ((xx=xx->next)!=NULL);
      printf("\n");

      delete_linked_list(list);

      return 0;
}