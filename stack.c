#include "doubly_linked_list.c"

typedef d_linked_list stack;
typedef d_element elem;

stack *new_stack(int (*comparator) (void*, void*))
{
      return new_list(comparator);
}

void push(stack* s, void *data)
{
      add(s, data);
}

void* pop(stack* s)
{
      elem* tail = s->tail;
      if (tail!=NULL) 
      {
            s->tail = tail->prev;
            s->tail->next = NULL;
      }
      return tail->data;
}

void* peek(stack* s)
{
      return s->tail;
}


int main()
{
      
      return 0;
}