#include <time.h>
#include "binary_search_tree.c"
#include "..\utils\burgergfx.c"

#ifdef _DEBUG
float v_step;
#endif

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
int rotate(binary_tree* bt, node* n)
{
      int bal = n->bal;
      if ((bal<-2) | (bal>2)) return -1;  // shouldn't ever happen
      
      node *x,*y,*z,*a,*b,*c,*d;
      
     
      
      // LEFT ROTATION
      if (bal == 2)
      {
            // LEFT-RIGHT
            if (n->left_child->bal == -1)
            {
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
            if ((n->left_child->bal == 1) | (n->left_child->bal == 0))
            {
                  x = n;
                  z = x->left_child;
                  y = z->left_child;
                  
                  bt->root = z;     // z will always be the new tree root
                  
                  a = y->left_child;
                  b = y->right_child;
                  c = z->right_child;
                  d = x->right_child;
                  
                  z->right_child = x;
                  x->parent = z;
                  x->left_child = c;
                  c->parent = x;
                  
                  return 0;
            }
            else return -2; // shouldn't ever happen
      }
      
      // RIGHT ROTATION
      else if (bal == -2)
      {
            //RIGHT-LEFT
            if (n->right_child->bal == 1)
            {
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
            if ((n->right_child->bal == -1) | (n->right_child->bal == 0))
            {
                  y = n;
                  z = y->right_child;
                  x = z->right_child;
                  
                  bt->root = z;     // z will always be the new tree root
                  
                  a = y->left_child;
                  b = z->left_child;
                  c = x->left_child;
                  d = x->right_child;
                  
                  z->left_child = y;
                  y->parent = z;
                  y->right_child = b;
                  b->parent = y;
                  
                  return 0;
            }
            else return -3; // shouldn't ever happen
      }
      
      else return 1;    // no balance needed bal=(-1,0,+1)
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
      int branch_h = 0;
      node* next = leaf;
      while (next)
      {
            next->height = (branch_h > next->height) ? branch_h : next->height;
            DBG("Node %d new height: %d\n",*(int*)next->data, next->height);
            
            if (next) 
            {
                  int lh = (next->left_child) ? next->left_child->height : 0;
                  int rh = (next->right_child) ? next->right_child->height : 0;
                  next->bal = lh-rh;
                  DBG("Node %d\tlh=%d, rh=%d\tBAL = %d\n",
                  *(int*)next->data,lh,rh,next->bal);
            }
            
            //int rotate_err = rotate(bt, next);
            //DBG("Calling rotate @node %d. newbal=%d, Return: %d\t",
            //*(int*)next->data, next->bal, rotate_err);
            
            next = next->parent;
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
      n->height);
}

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

int main()
{
      binary_tree* bt = new_binary_tree(compare_integer, ORD_ASC);

      int ts = 8;     
      srand(time(NULL));
      int i;
      for(i=0;i<ts;i++) 
      {
            int* data = malloc(sizeof(int));
            *data = 65+(rand()%(25));
            node* n = new_node((void*) data);
            avl_insert(bt, n);     
      }
      depth_first(bt, visit, IN_ORDER);

      
      
      v_step = 1/(float)(bt->root->height);
      
      burger* burg = create(48,48);
      clean_burger(burg);
      print_tree(burg,bt->root,0.5,0.1, 0);
      print_burger(burg);


      return 0;
}
#endif