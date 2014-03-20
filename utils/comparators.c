#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define ORD_ASC 0
#define ORD_DES 1

typedef struct {
      int k;
      void* v;
} kv;

kv* new_kv(int ki, void* vi)
{
      kv* a = malloc(sizeof(kv));
      a->k = ki;
      a->v = vi;
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

int compare_kv(void *data1, void* data2)
{
      kv* kv1 = (kv*) data1;
      kv* kv2 = (kv*) data2;
      return (kv2->k - kv1->k);
}

