#include "../data_structures/vector.c"
#include <time.h>

#ifdef _DEBUG
int main()
{
  srand(time(NULL));
  vector* v = new_vector(2, sizeof(int), compare_integer);
  vector* q = new_vector(2, sizeof(int), compare_integer);


  int **y = malloc(sizeof(int*)*8);
  int i;
  int predef[] = {1, 50, 12, 68, 3, 4, 78, 2};
  for (i = 0; i < 8; i++) { 
    y[i] = malloc(sizeof(int));
    // *y[i] = rand()%1000;
    *y[i] = predef[i];
  }

  int *z = malloc(sizeof(int));
  *z = 888;
  add_all(v, (void**) y, 8);
  add(v, z);
  delete(v, &y[0]);
  print_vector(v);

  return 0;
}
#endif
