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
      l->head = NULL;
      l->tail = NULL;
      return l;
}

void delete_linked_list(linked_list* l) {
      element* e = l->head;
      while (e) {
            free(e->data);
            element *t = e->next;
            free(e);
            e = t;
      }
      free(l);
}

void custom_delete_linked_list(linked_list* l, void (*delfun) (void*)) {
      element* e = l->head;
      while (e) {
            delfun(e->data);
            element *t = e->next;
            free(e);
            e = t;
      }
      free(l);
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
}

element *search_ll(linked_list *list, void *data)
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
      // Special case: empty list
      if (list->size == 0) return FALSE;

      // Special case: list head
      else if (list->head && (list->cmp(data, list->head->data)) == 0) {
            free(list->head->data);
            if (list->head->next) {
                  list->head = list->head->next;
            }
            else {
                  free(list->head); // head == tail, need only 1 free
                  list->head = NULL;
                  list->tail = NULL;
            }
            --list->size;
            return TRUE;
      }

      // General case: any element in list except head
      else {
            element *prev = search_ll(list, data);
            if (prev) 
            {
                  element *toremove = prev->next;

                  // Special case: list tail
                  if (toremove == list->tail) {
                        list->tail = prev;
                        list->tail->next = NULL;
                  }

                  // General case: not tail
                  else {
                        prev->next = prev->next->next;
                  }

                  free(toremove->data);
                  free(toremove);
                  --list->size;
                  return TRUE;
            }
            else return FALSE;
      }
}

void print_ll(linked_list *list) 
{
      if (list->size == 0) {
            printf("\nList empty.\n");
      }
      else {
            element *e = list->head;
            printf("\nPrinting list. Size = %d", list->size);
            printf("\nhead = %d (%p)\t tail = %d (%p)", 
                  *(int*) list->head->data, (void*) list->head,
                  *(int*) list->tail->data, (void*) list->tail);
            printf("\n----------------------------------");
            printf("\nList[idx]\tValue\tAddress");
            printf("\n----------------------------------");
            int i = 0;
            do 
            {
                  printf("\nList [%d]:\t%d\t%p",i++,*(int*)e->data,(void*)e);
            } while ((e = e->next) != NULL);
            printf("\n----------------------------------\n");
      }
}