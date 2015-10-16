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

int main()
{
      linked_list *list = new_list(compare_integer, sizeof(int));
      print_ll(list);
      int predef[] = {93, 68, 79, 91, 85, 89, 79};     
      int ts = 7;     
      srand(time(NULL));
      int i;
      int* lastdata;
      int* data = malloc(sizeof(int));
      for(i=0;i<ts;i++) 
      {
            *data = 65+(rand()%(ts));
            *data = predef[i];
            add_ll(list, data);
            lastdata = data;
      }

      print_ll(list);
      printf("\nWill remove (first occurence of) %d",*lastdata);
      delete_ll(list, lastdata);
      print_ll(list);
      
      return 0;
}
