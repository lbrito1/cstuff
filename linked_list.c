//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#ifndef TEST_SIZE
#define TEST_SIZE 10
#endif

//======================
//          Algorithm
//======================

typedef struct Element
{
      void *data_ptr;
      struct Element *next;
} Element;

int compare(void *data1, void *data2);

Element *search(void *list_head, void *data);

Element *new_element(void *data)
{
      Element *e = (Element*) malloc(sizeof(Element));
      e->data_ptr = data;
      e->next = NULL;
}

int compare(void *data1, void *data2)
{
      return (strcmp((char*) data1, (char*)data2) == 0 ? TRUE : FALSE);
}

void add(Element *list_head, void *data)
{
      Element *e = list_head;
      while (e->next != NULL) e = e->next;
      Element *toadd = new_element(data);
      e->next = toadd;
}

Element *search(void *list_head, void *data)
{
      Element *e = list_head;
      Element *prev = e;
      if (compare(data, e->data_ptr)) return NULL; // exception for list head
      do
      {
            if (compare(data, e->data_ptr)) return prev;
            prev = e;
      } while ((e = e->next) != NULL);
      return NULL;
}

int delete(Element *list_head, void *data)	
{
      Element *searched = search(list_head, data);
      if (searched) 
      {
            Element *removed = searched->next;

            // >3 elements
            if (searched->next->next)        
            searched->next = searched->next->next;

            // <3 elements
            else 								
            searched->next = NULL;

            free(removed->data_ptr);
            free(removed);
           
            return TRUE;
      }
      else return FALSE;
}

//======================
//          Tests
//======================

Element *build_list() 
{	
      char *head_data = "I'm the (permanent) list head. You can't delete me.";
      Element *head = new_element(head_data);
      char *basetext = "I'm element number ";
      int i=1;
      for (;i<TEST_SIZE;i++) 
      {
            char *text1 = malloc(sizeof(char)*strlen(basetext));
            strcpy(text1, basetext);
            char numb[10];
            sprintf(numb, "%d", i);
            strcat(text1, numb);
            add(head, text1);
      }
      
      return head;
}

void print_list(Element *head) 
{
      printf("\n==============");
      Element *e = head;
      int i = 0;
      do 
      {
            printf("\nList [%d]:\t%s",i++,(char**)e->data_ptr);
      } while ((e = e->next) != NULL);
      printf("\n==============\n");
}

void test_delete(Element *head, int eln) 
{
      char data[20];
      sprintf(data, "I'm element number %d", eln);
      if (delete(head, data)) printf("\nSuccessfully deleted element #%d",eln); 
}

void test_add(Element *head, int eln)
{ 
      char *data = malloc(sizeof(char)*50);
      sprintf(data, "I'm NEW element number %d", eln);
      add(head, data); 
      printf("\nSuccessfully added NEW element #%d",eln); 
}

int main()
{
      Element *head = build_list();
      
      print_list(head);
      test_delete(head, 1);
      test_delete(head, 4);
      test_delete(head, 5);
      test_add(head, 1337);
      test_delete(head, 2);
      test_add(head, 98);
      print_list(head);
      
      return 0;
}
