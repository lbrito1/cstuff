#include "../include/comparators.h"

#include <string.h>
#include <stdlib.h>

kv* new_kv(int ki, void* vi, int (*comp) (void*, void*))
{
      kv* a = malloc(sizeof(kv));
      a->k = ki;
      a->v = vi;
      a->cmp = comp;
      return a;
}

int compare_string(void *data1, void *data2)
{
      return strcmp((char*) data1, (char*)data2);
}

int compare_integer(void *data1, void* data2)
{
      return (( *((int*) data2) - *((int*) data1) ));
}

int compare_kv(void* v1, void* v2)
{
      if ((v1 == NULL) || (v2 == NULL)) return 0;
      kv* kv1 = (kv*) v1;
      kv* kv2 = (kv*) v2;
      return kv1->cmp(kv1->v, kv2->v);
      return 0;
}

kv* get_kv(void** array, int length, int key, int* pos)
{
      int i;
      kv* val = NULL;
      *pos = -1;
      for (i=0;i<length;i++) 
      {
            if (array[i]!=NULL) 
            {
                  val = (kv*)array[i];
                  if (val->k == key) 
                  {
                        *pos = i;
                        return val;
                  }
            }
      }
      return NULL;
}