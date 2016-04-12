#ifndef __QUEUE_H
#define __QUEUE_H 1
#include "tree.h"
#include <stdlib.h>

struct __q_node {
  int key;
  tree* value;
  struct __q_node* next;
};
typedef struct __q_node q_node;
typedef struct {
  q_node* head;
  int length;
} q;

q* q_create ();
void q_insert (q*, int, tree*);
q_node* q_pull (q*);
#endif
