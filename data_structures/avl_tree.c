/*











todo: rotate está identificando casos errados após rotações corretas por conta de balances desatualizados
solucao: realizar sempre o update do balance

todo 2: evitar printar um no em cima do outro
















*/

#include <time.h>
#include <math.h>
#include "binary_search_tree.c"
#include "..\utils\burgergfx.c"

#ifdef _DEBUG
burger* burg;
#endif


void print_tree(burger* burg, node* r, float sx, float sy, int pair)
{
      put_burger(burg, sx,sy,*(char*)r->data);
      
      float rf = 0;//(pair==0) ? -0.05 : 0;
      
      if (r->left_child) 
      {
            print_tree(burg, r->left_child, sx-0.1+rf, sy+0.1, (pair==0) ? 1 : 0);
            put_line(burg, sx, sy, sx-0.1+rf, sy+0.1);
      }
      if (r->right_child) 
      {
            print_tree(burg, r->right_child,sx+0.1,sy+0.1, (pair==0) ? 1 : 0);
            put_line(burg, sx, sy, sx+0.1+rf, sy+0.1);
      }
}
/**
 *  @brief AVL tree rotation
 *  
 *  There are four rotation cases for AVL trees. They are
 *  classified according to the subtree root's balance.
 *  
 *  If bal = +2, we need to do a LEFT ROTATION, which has
 *  two subcases: left-left and left-right. If bal = -2,
 *  we do a RIGHT ROTATION, also with two subcases.
 *  
 *  The following figures describe all four rotations. 
 *  X is the root with +2 or -2 balance, pivot to the 
 *  rotations. Y and Z are non-null nodes that will also
 *  be moved around during the rotation. A,B,C and D are
 *  (possibly empty) subtrees of X,Y,Z.
 *  
 *  The crucial thing is to remember that Y < Z < X . 
 *  Therefore, our objective will always be to get Z
 *  on the top and Y, X as its children. That is enough
 *  information to deduct these rotations in case you
 *  don't want to learn them by heart: simply move up
 *  Z until it's the root, and manage the subtrees
 *  according to their values.
 *  
 *  LEFT-RIGHT and RIGHT-LEFT cases need to be rotated to
 *  LEFT-LEFT and RIGHT-RIGHT cases first, and then rotated
 *  once more to achieve a balanced tree.
 *  
 *  LEFT-RIGHT CASE        LEFT-LEFT CASE             BALANCED
 *  (Y bal = -1)            (Y bal = +1)           
 *                                                        
 *       +2                      +2                    (0)
 *          X                       X                      Z
 *         / \                     / \                    /  \
 *    -1  /   D               +1  /   D                  /    \
 *       Y            \          Z              \       Y      X
 *      / \        ----\        / \          ----\     / \    / \  
 *     A   \       ----/       /   C         ----/    A   B  C   D
 *          Z         /       Y                 /  
 *         / \               / \                   
 *        B   C             A   B                  
 *                                   
 *  RIGHT-LEFT CASE            RIGHT-RIGHT CASE            BALANCED
 *  (Y bal = +1)                (Y bal = -1)
 *                 
 *     -2                   -2                        
 *         Y                    Y                          (0)
 *        / \                  / \                             Z
 *       A   \  +1     \      A   \  -1        \              /  \
 *            X     ----\          Z        ----\            /    \
 *           / \    ----/         / \       ----/           Y      X
 *          /   D      /         B   \         /           / \    / \  
 *         Z                          X                   A   B  C   D
 *        / \                        / \                
 *       B   C                      C   D         
 *   
 *                 
 *  
 *  @param [in] bt 
 *  @param [in] n  
 *  @return 
 */
node* rotate(node* n)
{
      int bal = n->bal;
      if ((bal<-2) | (bal>2)) return NULL;  // shouldn't ever happen
      
      node *x,*y,*z,*a,*b,*c,*d;
      
      DBG("\nROTATING NODE %d (%c)... ",*(int*)n->data, *(int*)n->data);
      
      // LEFT ROTATION
      if (bal == 2)
      {
            // LEFT-RIGHT
            if (n->left_child->bal == -1)
            {
                  DBG("LR ROTATION...");
                  
                  x = n;
                  y = x->left_child;
                  z = y->right_child;
                  
                  a = y->left_child;
                  b = z->left_child;
                  c = z->right_child;
                  d = x->right_child;
                  
                  x->left_child = z;
                  z->parent = x;
                  z->left_child = y;
                  y->parent = z;
                  y->right_child = b;
                  if (b) b->parent = y;
            }
            // LEFT-LEFT
   
            DBG("LL ROTATION\n\n");
            
            x = n;
            z = x->left_child;
            y = z->left_child;

            DBG("XYZ = %c, %c, %c\n",
            *(int*)x->data,*(int*)y->data,*(int*)z->data);
            
            a = y->left_child;
            b = y->right_child;
            c = z->right_child;
            d = x->right_child;
            
            
            z->parent = x->parent;
            
            if (x->parent) 
            {
                  if ((x->parent->left_child) && (x->parent->left_child == x))
                        z->parent->left_child = z;
                  else if ((x->parent->right_child) && (x->parent->right_child == x))
                        z->parent->right_child = z;
            }
            z->right_child = x;
            x->parent = z;
            x->left_child = c;
            if (c) c->parent = x;
            
            // Extremely important!!!!!! 
            // These heights will be
            // re-calculated bottom-up when we rebalance
            // this branch later, so if we don't update 
            // the heights now, rebalance will see the old
            // heights, i.e. the values prior to the rotation,
            // and thus will think the branch is still not
            // balanced!
            
            y->height =
                  (a&&b) ? fmax(a->height, b->height) :
                  a ? a->height :
                  b ? b->height : -1;
            y->height++;
            
            x->height =
                  (c&&d) ? fmax(c->height, d->height) :
                  c ? c->height :
                  d ? d->height : -1;
            x->height++;
            
            z->height = fmax(x->height, y->height);
            z->height++;
            
            return z;
 
      }
      
      // RIGHT ROTATION
      else if (bal == -2)
      {
            //RIGHT-LEFT
            if (n->right_child->bal == 1)
            {
                  DBG("RL ROTATION...");
                  
                  y = n;
                  x = y->right_child;
                  z = x->left_child;
                  
                  a = y->left_child;
                  b = z->left_child;
                  c = z->right_child;
                  d = x->right_child;
                  
                  y->right_child = z;
                  z->parent = y;
                  z->right_child = x;
                  x->parent = z;
                  x->left_child = c;
                  if (c) c->parent = x;
            }
            
            //RIGHT-RIGHT
      
            DBG("RR ROTATION\n\n");
            
            y = n;
            z = y->right_child;
            x = z->right_child;
            
            a = y->left_child;
            b = z->left_child;
            c = x->left_child;
            d = x->right_child;
            
            z->parent = y->parent;
            
            if (y->parent) 
            {
                  if ((y->parent->left_child) && (y->parent->left_child == y))
                        z->parent->left_child = z;
                  else if ((y->parent->right_child) && (y->parent->right_child == y))
                        z->parent->right_child = z;
            }
            
            
            z->left_child = y;
            y->parent = z;
            y->right_child = b;
            if(b) b->parent = y;
            
            
            y->height =
                  (a&&b) ? fmax(a->height, b->height) :
                  a ? a->height :
                  b ? b->height : -1;
            y->height++;
            
            x->height =
                  (c&&d) ? fmax(c->height, d->height) :
                  c ? c->height :
                  d ? d->height : -1;
            x->height++;
            
            z->height = fmax(x->height, y->height);
            z->height++;
            
            
            return z;
      
      }
      
      else return n;    // no balance needed bal=(-1,0,+1)
}



/**
 *  @brief Recalculate heights in all nodes
 *  affected by a insertion, i.e. every node
 *  in the branch traversed during insertion.
 *  
 *  After recalculating lheight and rheight
 *  of a node, calculte balance (lh-rh) and
 *  call the apropriate rotation case if
 *  bal = -2 or +2. bal should always be
 *  
 *  
 *  Should be called after insertion.
 *  
 *  Runs in O(h) time, which is guaranteed
 *  1.44log n time in an AVL tree.
 *  
 *  @param [in] bt   Parameter_Description
 *  @param [in] leaf Parameter_Description
 *  @return Return_Description
 */
void rebalance(binary_tree* bt, node* leaf)
{
      DBG("\n\nSTARTED CHECKING NODE %d (%c)\n=====================\n\n",
      *(int*)leaf->data,*(int*)leaf->data);

      int branch_h = 0;
      node* next = leaf;
      while (next)
      {
            DBG("\nnode in path %d (%c)\n-----------------\n", 
            *(int*)next->data,*(int*)next->data);
            
            if (branch_h > next->height) 
            { 
                  next->height = branch_h;
                  DBG("Node %d new height: %d\n",*(int*)next->data, next->height);
            }
            
            
            if (next) 
            {
                  int lh = 0;
                  if (next->left_child) lh = next->left_child->height+1;
                  int rh = 0;
                  if (next->right_child) rh = next->right_child->height+1;
                  
                  next->bal = lh-rh;
                  DBG("Node %d (%c)\tlh=%d, rh=%d\tBAL = %d\n",
                  *(int*)next->data,*(int*)next->data,lh,rh,next->bal);
            }
            
            

            #ifdef _VERBOSE
            DBG("\n====================\nBefore rotate\n=============\n\n");
            clean_burger(burg);
            print_tree(burg,bt->root,0.5,0.1, 0);
            print_burger(burg);
            #endif
            
            node* new_subtree_root = rotate(next);
            if (new_subtree_root) 
            {
                  next = new_subtree_root;
            }
            
            node* r = bt->root;
            while (r)
            {
                  bt->root = r;
                  DBG("R %d\t",*(int*)r->data);
                  
                  r = r->parent;
            }
            
            #ifdef _VERBOSE
            if (new_subtree_root) 
            {
            DBG("\n====================\nAfter rotate\n=============\n\n");
            clean_burger(burg);
            print_tree(burg,bt->root,0.5,0.1, 0);
            print_burger(burg);
            }
            #endif
     
            DBG("Finished checking node %d (%c), now checking " ,*(int*) next->data, *(int*) next->data);
            next = next->parent;
            if(next) DBG("\tnode %d (%c)\n" ,*(int*) next->data, *(int*) next->data);
            else DBG("(NULL - finished branch)\n");
            
            branch_h++;
      }
}


void avl_insert(binary_tree* bt, node* n)
{
      #ifdef _DEBUG
      if (tree_search(bt,n->data)) return;      //checks for repeated nodes
      #endif

      tree_insert(bt, n);   
      rebalance(bt, n);
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


void print_avl(burger* burg, binary_tree* bt)
{
      clean_burger(burg);
      print_tree(burg,bt->root,0.5,0.1, 0);
      print_burger(burg);
}

int main()
{
      burg = create(48,48);
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 8;     
      srand(time(NULL));
      int i;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%(25));
            node* n = new_node((void*) data);
            DBG("\n\n===============\nPRE-INSERT\n===============\n\n");
            if (bt->root) print_avl(burg, bt);
            avl_insert(bt, n);
            DBG("\n\n===============\nPOST-INSERT\n===============\n\n");
            print_avl(burg, bt);            
      }
      
      depth_first(bt, visit, IN_ORDER);

      

      


      return 0;
}
#endif