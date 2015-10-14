#include "../../include/binary_search_tree.h"
#include "../../../utils/include/comparators.h"
#include "../../../utils/include/debug.h"

#include <time.h>

void visit(node* n)
{
      DBG("Visited node #%d\n",*(int*)n->data);
}

#ifdef _DEBUG
int main()
{
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 10;     
      
      srand(time(NULL));
      int i;
      void* to_delete = NULL;
      node* suc = NULL;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%ts);
            if (i==ts-1) to_delete = (void*)data;
            node* n = tree_insert(bt, data, TRUE);
            if (i==3) suc=n;
      }
      
      depth_first(bt, visit, IN_ORDER);

      
      node* min = tree_min(bt->root);
      DBG("Tree min = %d\n",*(int*)min->data);
      
      node* sucn = tree_successor(bt, suc);
      if (sucn) DBG("Successor to %d is %d\n",*(int*)suc->data,*(int*)sucn->data);
      
      node* del = tree_delete(bt, to_delete);
      DBG("Deleted node %d\n",*(int*)del->data);
      
      depth_first(bt,visit,IN_ORDER);
      
      return 0;
}
#endif
