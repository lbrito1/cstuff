//======================
//      Linked list
// CC-BY Leonardo Brito
// lbrito@gmail.com
//======================

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#if !defined _TEST_SIZE_LIST && defined _DEBUGGING
#define _TEST_SIZE_LIST 10
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
      size_t typesize;
} linked_list;

linked_list *new_list(int (*comparator) (void*, void*), size_t typesize);

element *new_element(linked_list *list, void *data);

void add_ll(linked_list *list, void *data);

element *search(linked_list *list, void *data);

int delete_ll(linked_list *list, void *data);

void print_ll(linked_list *list);

#endif