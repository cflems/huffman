#include "queue.h"

q* q_create() {
  q* newq = calloc(1, sizeof(q));
  return newq;
}

void q_insert (q* header, int key, tree* value) {
  if (header == 0) return;
  q_node* new;
  if (header->head == 0) {
    header->head = malloc(sizeof(q_node));
    new = header->head;
    new->next = 0;
  } else if (key < header->head->key) {
    new = malloc(sizeof(q_node));
    new->next = header->head;
    header->head = new;
  } else {
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
  new->key = key;
  new->value = value;
  header->length++;
}

q_node* q_pull (q* header) {
  if (header == 0) return 0;
  q_node* pulled = header->head;
  if (pulled != 0) {
    header->head = pulled->next;
    header->length--;
  }
  return pulled;
}
