#ifndef __TREE_H
#define __TREE_H 1
#define max(a,b) ((a>b)?a:b)

struct __tree {
  struct __tree* left;    // Link to the left subtree.
  struct __tree* right;   // Link to the right subtree.
  char value;             // Character stored if this is a leaf.
};
typedef struct __tree tree;

int tree_depth (tree*);
#endif
