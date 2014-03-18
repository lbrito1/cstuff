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
            if (tail->prev != NULL)
            {
                  s->tail = tail->prev;
                  s->tail->next = NULL;   
            }
            else
            {
                  s->tail = s->head;                  
            }
      }
      return tail->data;
}

void* peek(stack* s)
{
      return s->tail;
}

#ifdef _DEBUGGING
int main()
{
      stack* s = new_stack(compare_integer);
      int i, *data;
      for (i=0; i<100; i++) 
      {
            data = malloc(sizeof(int));
            *data = i;
            push(s, data);
      } 
      
      for (i=0; i<100; i++) 
      {
            data = (int*) pop(s);
            printf("\nPopped %d",*((int*) data));
            free(data);
      } 
      return 0;
}
#endif