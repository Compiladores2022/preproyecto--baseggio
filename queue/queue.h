#ifndef QUEUE_H

typedef struct node {
    void* data;
    struct node* next;
} TNode;

typedef struct {
   TNode* head;
   int length; 
} Queue;

int length(Queue queue);
int isEmpty(Queue queue);
void* head(Queue queue);
void enqueue(Queue* queue, void* data);
void dequeue(Queue* queue);
void construct(Queue* queue);
#endif
