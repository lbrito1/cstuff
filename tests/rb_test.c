
#include <time.h>
#include "../data_structures/red_black_tree.c"
#include "../utils/burgergfx.c"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy, int pair)
{
    char should_put = r->color == 0 ? 'R' : 'B';
    put_burger(burg, sx,sy,*(char*) r->data);
    int x = get_norm_x(burg,sx);
    int y = get_norm_y(burg,sy);
    put_burger_int(burg, x+1,y-1,'(');
    put_burger_int(burg, x+2,y-1,should_put);
    put_burger_int(burg, x+3,y-1,')');

    float rf = 0;//(pair==0) ? -0.05 : 0;

    if (r->left_child) 
    {
        print_tree(burg, r->left_child, sx-default_spacing+rf, sy+default_spacing, (pair==0) ? 1 : 0);
        put_line(burg, sx, sy, sx-default_spacing+rf, sy+default_spacing);
    }
    if (r->right_child) 
    {
        print_tree(burg, r->right_child,sx+default_spacing,sy+default_spacing, (pair==0) ? 1 : 0);
        put_line(burg, sx, sy, sx+default_spacing+rf, sy+default_spacing);
    }
}

#ifdef _DEBUG
void visit(node* n)
{
      DBG("Visited node #%d (%c) \tPARENT=%d (%c)\tHEIGHT=%d\n",
      *(int*)n->data,
      *(int*)n->data,
      n->parent?*(int*)n->parent->data:-1,
      n->parent?*(int*)n->parent->data:'*',
      n->height
      );
}


void print_rb(burger* burg, binary_tree* bt)
{
      clean_burger(burg);
      print_tree(burg,bt->root,0.5,0.1, 0);
      print_burger(burg);
}

int main(void)
{
    burg = create(48,48);
    binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);
       
    int ts = 8;     
    srand(time(NULL));
    int i;

    int predef[] = {65, 90, 80, 75, 66};

    for(i=0;i<ts;i++) 
    {           
        DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
        if (bt->root) print_rb(burg, bt);
        int* data = malloc(sizeof(int));
        *data = 65+(rand()%(25));
        //*data = predef[i];
        rb_insert(bt, (void*)data);
        DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
        print_rb(burg, bt);            
    }
    
    depth_first(bt, visit, IN_ORDER);
    return 0;
}
#endif
