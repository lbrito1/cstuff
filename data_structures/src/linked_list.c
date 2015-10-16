//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#ifdef PYLIB
#include <Python.h>
#else
#include <string.h>
#endif

#include "../../utils/include/comparators.h"
#include "../include/linked_list.h"

linked_list *new_list(int (*comparator) (void*, void*), size_t typesize)
{
      linked_list *l = malloc(sizeof(linked_list));
      l->size = 0;
      l->cmp = comparator;
      l->typesize = typesize;
      return l;
}

element *new_element(linked_list *list, void *data)
{
      element *e = (element*) malloc(sizeof(element));
      e->data = malloc(sizeof(list->typesize));
      memcpy(e->data, data, list->typesize);
      e->next = NULL;
      return e;
}

void add_ll(linked_list *list, void *data)
{
      element *toadd = new_element(list, data);
      if (list->size == 0) 
      {
            list->head = toadd;
            list->tail = list->head;
      }
      else
      {
            list->tail->next = toadd;
            list->tail = list->tail->next;
      }
      ++list->size;
      print_ll(list);
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

void print_ll(linked_list *list) 
{
      if (list->size == 0) {
            printf("\nList empty.\n");
      }
      else {
            element *e = list->head;
            printf("\n----------------------------");
            printf("\nList[idx]\tValue\tAddress");
            printf("\n----------------------------");
            int i = 0;
            do 
            {
                  printf("\nList [%d]:\t%d\t%p",i++,*(int*)e->data,(void*)e);
            } while ((e = e->next) != NULL);
            printf("\n==============\n");
      }
}