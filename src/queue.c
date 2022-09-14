#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

int length(Queue queue) {
  return queue.length;
}

int isEmpty(Queue queue) {
  return length(queue) == 0;
}

void* head(Queue queue) {
  return queue.head;
}

void* lookUp(Queue queue, int (*f) (void*, void*), void* e) {
  TNode* node = head(queue);
  while(node) {
    if((*f) (node->data, e)) {
      return node->data;
    }
    node = node->next;
  }

  return NULL;
}

TNode* constructNode(void* data, size_t dataSize) {
  TNode* node = (TNode*) malloc(sizeof(TNode));
  if(node == NULL) {
    printf("Error allocating memory for TNode\n");
    exit(EXIT_FAILURE);
  }
  node->data = malloc(dataSize);

  if(node->data == NULL) {
    printf("Error allocating memory for data");
    exit(EXIT_FAILURE);
  }

  node->data = data;
  return node;
}

void enqueue(Queue* queue, void* data, size_t dataSize) {
  TNode* node = constructNode(data, dataSize);
  if(isEmpty(*queue)) {
    queue->head = node;
    queue->last = node;
  } else {
    queue->last->next = node;
    queue->last       = node;
  }

  queue->length++;
}

void dequeue(Queue* queue) {
  TNode* node = head(*queue);
  queue->head = queue->head->next;
  free(node);
  queue->length--;
}

void showQueue(Queue queue, void (*f) (void*)) {
  TNode* node = queue.head;
  while(node) {
    (*f) (node->data);
    node = node->next;
  }
}

void constructQueue(Queue* queue) {
  queue->head = queue->last = NULL;
  queue->length = 0;
}
