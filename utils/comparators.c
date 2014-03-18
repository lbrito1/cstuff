#include <string.h>

#define TRUE 1
#define FALSE 0

#define ORD_ASC 0
#define ORD_DES 1

int compare_string(void *data1, void *data2)
{
      return strcmp((char*) data1, (char*)data2);
}

int compare_integer(void *data1, void* data2)
{
      return (( *((int*) data2) - *((int*) data1) ));
}

