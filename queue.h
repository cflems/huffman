#ifndef __QUEUE_H
#define __QUEUE_H 1
#include "tree.h"
#include <stdlib.h>

struct __q_node {
  int key;                // The number of times it appears.
  tree* value;            // The subtree to be built on.
  struct __q_node* next;  // Link to the next element in the queue.
};
typedef struct __q_node q_node;
typedef struct {
  q_node* head;           // Link to the first element in the queue.
  int length;
} q;

q* q_create ();
void q_insert (q*, int, tree*);
q_node* q_pull (q*);
#endif
