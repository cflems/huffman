#include "tree.h"
#include <stdio.h>

int tree_depth (tree* root) {
  if (root == 0) return 0;
  int la = tree_depth(root->left), lb = tree_depth(root->right);
  return 1+max(la, lb);
}
