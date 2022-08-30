#ifndef QUEUE_H

typedef struct node {
    void* data;
    struct node* next;
} TNode;

typedef struct {
   TNode* head;
   int length; 
} Queue;

/* The 'length' function returns the length of the 'queue'. */
int length(Queue queue);

/* The 'isEmpty' function returns ZERO iff the 'queue' is not empty. Otherwise it returns a non-zero number. */
int isEmpty(Queue queue);

/* The 'head' function returns a pointer to void which corresponds to the 'data' stored at the head of the 'queue'. */
void* head(Queue queue);

/* The 'enqueue' function add the element 'data' to the 'queue'. To prevent data corruption the caller must pass as parameter a copy of 'data'. */
void enqueue(Queue* queue, void* data);

/* The 'dequeue' function remove the head of the 'queue'. */
void dequeue(Queue* queue);

/* The 'construct' function initializes the 'queue'. */
void construct(Queue* queue);
#endif
