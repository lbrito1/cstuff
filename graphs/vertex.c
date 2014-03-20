#define UNMARKED 0
#define MARKED 1

typedef struct vertex
{
      unsigned long id;
      int status;
      double x,y;
      void* data;
} vertex;


vertex* new_vertex(unsigned long id, void* data)
{
      vertex* v = malloc(sizeof(vertex));
      v->data = data;
      v->status = UNMARKED;
      v->id = id;
      v->x = 0.0;
      v->y = 0.0;
      return v;
}

int compare_v(void* v1, void* v2) 
{
      if ((v1 == NULL) | (v2 == NULL)) return -1;
      return ((((vertex*) v1)->id) == (((vertex*) v2)->id));
}