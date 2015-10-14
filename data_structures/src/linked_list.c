//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/include/comparators.h"
#include "../include/linked_list.h"

linked_list *new_list(int (*comparator) (void*, void*))
{
      linked_list *l = malloc(sizeof(linked_list));
      l->size = 0;
      l->cmp = comparator;
      return l;
}

element *new_element(void *data)
{
      element *e = (element*) malloc(sizeof(element));
      e->data = data;
      e->next = NULL;
      return e;
}

void add_ll(linked_list *list, void *data)
{
      if (list->size == 0) 
      {
            list->head = new_element(data);
            list->tail = list->head;
      }
      else
      {
            element *toadd = new_element(data);
            list->tail->next = toadd;
            list->tail = list->tail->next;
      }
      ++list->size;
}

element *search(linked_list *list, void *data)
{
      element *e = list->head;
      element *prev = e;
      do
      {
            if (list->cmp(data, e->data) == 0) return prev;
            prev = e;
      } while ((e = e->next) != NULL);
      return NULL;
}

int delete_ll(linked_list *list, void *data)	
{
      element *searched = search(list, data);
      if (searched) 
      {
            int ishead = !(list->cmp(searched->data, list->head->data));
            element *removed = (ishead) ? searched : searched->next;
            if (!ishead) searched->next = searched->next->next;
            else list->head = list->head->next;
            free(removed->data);
            free(removed);
            --list->size;
            return TRUE;
      }
      else return FALSE;
}
