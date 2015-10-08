#include "../data_structures/vector.c"
#include <stdlib.h>

static inline void exch(void** a, void** b) { void* p = *a; *a = *b; *b = p; }

void ins_sort(vector* a) {
  if (a->used == 1) return;
  int i = 1, j;
  for (; i < a->used; i++)
    for (j = i; j > 0 && a->cmp(a->array[j], a->array[j-1]) > 0; j--) exch(a->array[j],a->array[j-1]);
}