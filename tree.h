#ifndef __TREE_H
#define __TREE_H 1
#define max(a,b) ((a>b)?a:b)

struct __tree {
  struct __tree* left;
  struct __tree* right;
  char value;
};
typedef struct __tree tree;

int tree_depth (tree*);
#endif
