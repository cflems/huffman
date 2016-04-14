#include "queue.h"

// initialize a null priority queue
q* q_create() {
  q* newq = calloc(1, sizeof(q));
  return newq;
}

// insert a given element into the queue
void q_insert (q* header, int key, tree* value) {
  if (header == 0) return;
  q_node* new;
  if (header->head == 0) { // if the queue is empty, take a shortcut
    header->head = malloc(sizeof(q_node));
    new = header->head;
    new->next = 0;
  } else if (key < header->head->key) { // new node is at the head, another
                                        // shortcut
    new = malloc(sizeof(q_node));
    new->next = header->head;
    header->head = new;
  } else { // traverse the queue to find the appropriate spot
    q_node* head = header->head;
    while (head->next != 0) {
      if (head->next->key > key) break;
      head = head->next;
    }
    new = malloc(sizeof(q_node));
    if (head->next == 0) {
      head->next = new;
      new->next = 0;
    } else {
      new->next = head->next;
      head->next = new;
    }
  }
  // assign the values to the new element and increase the length value
  new->key = key;
  new->value = value;
  header->length++;
}

// remove the first element in the queue
q_node* q_pull (q* header) {
  if (header == 0) return 0;
  q_node* pulled = header->head; // grab the first element
  if (pulled != 0) { // the queue isn't different if we remove null
    header->head = pulled->next;
    header->length--;
  }
  return pulled;
}
