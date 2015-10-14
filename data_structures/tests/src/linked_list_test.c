//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/linked_list.h"
#include "../../../utils/include/comparators.h"

#define TEST_SIZE 10
#define TRUE 1
#define FALSE 0

void print_list(element *head) 
{
      printf("\n==============");
      element *e = head;
      int i = 0;
      do 
      {
            printf("\nList [%d]:\t%d",i++,*(int*)e->data);
      } while ((e = e->next) != NULL);
      printf("\n==============\n");
}

int main()
{
      linked_list *list = new_list(compare_integer);
      int predef[] = {93, 68, 79, 91, 85, 89, 79};     
      int ts = 7;     
      srand(time(NULL));
      int i;
      int* lastdata;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%(ts));
            *data = predef[i];
            add_ll(list, data);
            lastdata = data;
      }

      print_list(list->head);
      printf("\nWill remove (first occurence of) %d",*lastdata);
      delete_ll(list, lastdata);
      print_list(list->head);
      
      return 0;
}
