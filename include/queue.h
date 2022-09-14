#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct node {
  void* data;
  struct node* next;
} TNode;

typedef struct {
  TNode* head;
  TNode* last;
  int length;
} Queue;

int length(Queue queue);
int isEmpty(Queue queue);
void* head(Queue queue);
void* lookUp(Queue queue, int (*f) (void*, void*), void* e);
void enqueue(Queue* queue, void* data, size_t dataSize);
void dequeue(Queue* queue);
void constructQueue(Queue* queue);
void showQueue(Queue queue, void (*f) (void*));
#endif
