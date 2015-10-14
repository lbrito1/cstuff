#ifndef COMPARATORS_H
#define COMPARATORS_H

#define TRUE 1
#define FALSE 0

#define ORD_ASC 0
#define ORD_DES 1

typedef struct kv {
      int k;
      void* v;
      int (*cmp) (void*, void*);
} kv;

kv* new_kv(int ki, void* vi, int (*comp) (void*, void*));

int compare_string(void *data1, void *data2);
int compare_integer(void *data1, void* data2);
int compare_kv(void* v1, void* v2);

kv* get_kv(void** array, int length, int key, int* pos);

#endif