#include "graph_adj.c"
#include "burgergfx.c"

typedef struct vertex_pt {
      vertex* v;
      double x,y;
      char c;
} vertex_pt;

vertex_pt* create_pt(vertex* v, double x, double y) 
{
      vertex_pt* pt = malloc(sizeof(vertex_pt));
      pt->v = v;
      pt->x = x;
      pt->y = y;
      pt->c = *((char*) v->data);
      return pt;
}

void add_pt(burger* b, vertex_pt* pt) 
{
      put_burger(b, pt->x, pt->y, pt->c);
}

int main()
{
      graph* g = new_graph(10);
      char mydata = 'A';
      char mydata2 = 'B';
      char mydata3 = 'C';
      
      vertex* v1 = add_vertex(g, &mydata);
      vertex* v2 = add_vertex(g, &mydata2);
      vertex* v3 = add_vertex(g, &mydata3);
      
      add_edge(g, v1, v2);
      
      // testing
      
      burger* bgfx = create(16,16);
      
      vertex_pt* pt1 = create_pt(v1, 0.1, 0.1);
      vertex_pt* pt2 = create_pt(v2, 0.5, 0.1);
      vertex_pt* pt3 = create_pt(v3, 0.1, 0.5);
      
      add_pt(bgfx, pt1);
      add_pt(bgfx, pt2);
      add_pt(bgfx, pt3);
      
      print_burger(bgfx);
      
      return 0;
}