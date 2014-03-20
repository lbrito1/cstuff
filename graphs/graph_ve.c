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

int visit(vertex* v) 
{
      if (v->status == UNMARKED) 
      {
            v->status = MARKED;
            return TRUE;
      }
      return FALSE;
}

typedef struct edge
{
      vertex* from, *to;
      int cost;
} edge;

edge* new_edge(vertex* from, vertex* to, int cost)
{
      edge* e = malloc(sizeof(edge));
      e->from = from;
      e->to = to;
      e->cost = cost;
      return e;
}

int compare_e(void* e1, void* e2)
{
      if ((e1 == NULL) | (e2 == NULL)) return -1;
      return  (((edge*)e1)->from->id) == (((edge*)e2)->from->id)
      && (((edge*)e1)->to->id) == (((edge*)e2)->to->id);
}
