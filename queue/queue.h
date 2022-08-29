#ifndef QUEUE_H

typedef struct node {
    int data;
    struct node* next;
} TNode;

typedef struct {
   TNode* head;
   int length; 
} Queue;

int length(Queue queue);
int isEmpty(Queue queue);
void enqueue(Queue* queue, int data);
void dequeue(Queue* queue);
void construct(Queue* queue);
void show(Queue queue);

#endif
