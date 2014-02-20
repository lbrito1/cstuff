//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TEST_SIZE
#define TEST_SIZE 10
#endif

#define TRUE 1
#define FALSE 0

//======================
//          Algorithm
//======================

typedef struct element
{
      void *data;
      struct element *next;
} element;

typedef struct linked_list
{
      element *head;
      element *tail;
      unsigned size;
      int (*cmp) (void*, void*);
} linked_list;

linked_list *new_list(int (*comparator) (void*, void*))
{
      linked_list *l = malloc(sizeof(linked_list));
      l->size = 0;
      l->cmp = comparator;
}

element *new_element(void *data)
{
      element *e = (element*) malloc(sizeof(element));
      e->data = data;
      e->next = NULL;
}

int compare_string(void *data1, void *data2)
{
      return (strcmp((char*) data1, (char*)data2) == 0 ? TRUE : FALSE);
}

int compare_integer(void *data1, void* data2)
{
      //printf("%d - %d = %d",( *((int*) data2) ),( *((int*) data1) ), ( *((int*) data2) - *((int*) data1) )  )  ;
      return (( *((int*) data2) - *((int*) data1) ));
}

void add(linked_list *list, void *data)
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
            if (list->cmp(data, e->data)) return prev;
            prev = e;
      } while ((e = e->next) != NULL);
      return NULL;
}

int delete(linked_list *list, void *data)	
{
      element *searched = search(list, data);
      if (searched) 
      {
            int ishead = list->cmp(searched->data, list->head->data);
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

//======================
//          Tests
//======================

#ifdef DEBUGGING

linked_list *build_list() 
{	
      linked_list *list = new_list(compare_string);
      char *basetext = "I'm element number ";
      int i=1;
      for (;i<TEST_SIZE;i++) 
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

void print_list(linked_list *list) 
{
      if (list->size == 0) 
      {
            printf("\nList empty.");
      }
      else 
      {
            printf("\n==============");
            element *e = list->head;
            int i = 0;
            do 
            {
                  printf("\nList [%d]:\t%s",i++,(char**)e->data);
            } while ((e = e->next) != NULL);
            printf("\n==============\n");
      }
}

void test_delete(linked_list *list, int eln) 
{
      char data[20];
      sprintf(data, "I'm element number %d", eln);
      if (delete(list, data)) printf("\nSuccessfully deleted element #%d, %d elems in list",eln,list->size); 
      else printf("\nElem #%d not found",eln);
}

void test_add(linked_list *list, int eln)
{ 
      char *data = malloc(sizeof(char)*50);
      sprintf(data, "I'm NEW element number %d", eln);
      add(list, data); 
      printf("\nSuccessfully added NEW element #%d, %d elems in list",eln,list->size); 
}

int main()
{
      linked_list *list = build_list();
      
      print_list(list);
      test_delete(list, 1);
      test_delete(list, 2);
      test_delete(list, 3);
      test_delete(list, 4);
      test_delete(list, 5);
      test_delete(list, 6);
      test_delete(list, 7);
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
