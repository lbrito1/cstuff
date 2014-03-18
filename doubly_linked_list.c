/**
 *  @file doubly_linked_list.c
 *  @brief Brief
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparators.c"

#if !defined _TEST_SIZE_LIST && defined _DEBUGGING
#define _TEST_SIZE_LIST 10
#endif

#define TRUE 1
#define FALSE 0

typedef struct d_element
{
      void *data;
      struct d_element *next, *prev;
} d_element;

typedef struct d_linked_list
{
      d_element *head;
      d_element *tail;
      unsigned size;
      int (*cmp) (void*, void*);
} d_linked_list;

/**
 *  @brief create a new doubly linked list
 *  
 *  @param [in] comparator
 *  @return
 */
d_linked_list *new_list(int (*comparator) (void*, void*))
{
      d_linked_list *l = malloc(sizeof(d_linked_list));
      l->size = 0;
      l->cmp = comparator;
      return l;
}

/**
 *  @brief create a new d_element
 *  
 *  @param [in] data 
 *  @return 
 */
d_element *new_d_element(void *data)
{
      d_element *e = (d_element*) malloc(sizeof(d_element));
      e->data = data;
      e->next = NULL;
      e->prev = NULL;
      return e;
}

/**
 *  @brief add data to list
 *  
 *  @param [in] list 
 *  @param [in] data 
 */
void add(d_linked_list *list, void *data)
{
      if (list->size == 0) 
      {
            list->head = new_d_element(data);
            list->tail = list->head;
      }
      else
      {
            d_element *toadd = new_d_element(data);
            list->tail->next = toadd;
            toadd->prev = list->tail;
            list->tail = toadd;
      }
      ++list->size;
}

/**
 *  @brief search for data in list
 *  
 *  @param [in] list
 *  @param [in] data
 *  @return searched element
 */
d_element *search(d_linked_list *list, void *data)
{
      d_element *e = list->head;
      do
      {
            if (list->cmp(data, e->data) == 0) return e;
      } while ((e = e->next) != NULL);
      return NULL;
}

/**
 *  @brief Brief
 *  
 *  @param [in] list Parameter_Description
 *  @param [in] data Parameter_Description
 *  @return Return_Description
 */
int delete(d_linked_list *list, void *data)	
{
      d_element *searched = search(list, data);
      if (searched) 
      {
            int ishead = !list->cmp(searched->data, list->head->data);
            if (!ishead) 
            {
                  if (searched != NULL) 
                  {
                        searched->next->prev = searched->prev;
                        searched->prev->next = searched->next;
                  }
                  else
                  {
                        list->head = NULL;      // LAST ELEMENT IN LIST
                        list->tail = NULL;
                  }
            }
            else 
            {
                  if (list->head->next != NULL) 
                  {
                        list->head = list->head->next; 
                        list->head->prev = NULL;
                  }
                  else 
                  {
                        list->head = NULL;      // LAST ELEMENT IN LIST
                        list->tail = NULL;
                  }
            }
            free(searched->data);
            free(searched);
            --list->size;
            return TRUE;
      }
      else return FALSE;
}

//======================
//          Tests
//======================

#ifdef _DEBUGGING

d_linked_list *build_list() 
{	
      d_linked_list *list = new_list(compare_string);
      char *basetext = "I'm d_element number ";
      int i=1;
      for (;i<_TEST_SIZE_LIST;i++) 
      {
            char *text1 = malloc(sizeof(char)*strlen(basetext));
            strcpy(text1, basetext);
            char numb[10];
            sprintf(numb, "%d", i);
            strcat(text1, numb);
            add(list, text1);
      }
      
      return list;
}

void print_list(d_linked_list *list) 
{
      if (list->size == 0) 
      {
            printf("\nList empty.");
      }
      else 
      {
            printf("\n==============");
            d_element *e = list->head;
            int i = 0;
            do 
            {
                  printf("\nList [%d]:\t%s",i++,(char*)e->data);
            } while ((e = e->next) != NULL);
            printf("\n==============\n");
      }
}

void test_delete(d_linked_list *list, int eln) 
{
      char data[20];
      sprintf(data, "I'm d_element number %d", eln);
      if (delete(list, data)) printf("\nSuccessfully deleted d_element #%d, %d elems in list",eln,list->size); 
      else printf("\nElem #%d not found",eln);
}

void test_add(d_linked_list *list, int eln)
{ 
      char *data = malloc(sizeof(char)*50);
      sprintf(data, "I'm NEW d_element number %d", eln);
      add(list, data); 
      printf("\nSuccessfully added NEW d_element #%d, %d elems in list",eln,list->size); 
}

int main()
{
      d_linked_list *list = build_list();
      
      print_list(list);
      test_delete(list, 1);
      test_delete(list, 2);
      test_delete(list, 7);
      test_delete(list, 3);
      test_delete(list, 4);
      test_delete(list, 5);
      test_add(list, 13);
      test_delete(list, 6);
      test_delete(list, 8);
      test_delete(list, 9);
      print_list(list);
      test_add(list, 1337);
      print_list(list);
      test_delete(list, 2);
      test_add(list, 98);
      print_list(list);
      
      return 0;
}

#endif
