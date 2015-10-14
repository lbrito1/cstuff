#include "../../include/quicksort.h"

int main() {
  vector* v = new_vector(2, sizeof(int), compare_integer);
  int **y = malloc(sizeof(int*)*8);
  int i;
  int predef[] = {7, 2, 1, 6, 8, 5, 3, 4};
  for (i = 0; i < 8; i++) { 
    y[i] = malloc(sizeof(int));
    // *y[i] = rand()%1000;
    *y[i] = predef[i];
  }
  add_all_vec(v, (void**) y, 8);

  DBG("\nArray:");
  print_vector(v);
  _qsort(v);
  DBG("\nSorted:");
  print_vector(v);

  return 0;
}
