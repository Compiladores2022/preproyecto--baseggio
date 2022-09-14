#ifndef QUEUE_H
#define QUEUE_H
#include "symbol.h"

typedef struct node {
    Symbol* symbol;
    struct node* next;
} TNode;

typedef struct {
   TNode* head;
   TNode* last;
   int length; 
} Queue;

/* The function 'length' returns the length of the Queue 'queue' */
int length(Queue queue);

/* The function 'isEmpty' returns true iff the Queue 'queue' is empty */
int isEmpty(Queue queue);

/* The function 'head' returns the a pointer to the symbol on the head of the 'queue'.
 * It is assumed that the 'queue' is not empty. */
Symbol* head(Queue queue);

/* The function 'lookUp' look for a symbol by its name in the 'queue'.
 * It returns a reference to the symbol if it is found otherwise returns NULL. */
Symbol* lookUp(Queue queue, char* name);

/* The 'enqueue' function add a reference to a symbol in the 'queue'. */
void enqueue(Queue* queue, Symbol* symbol);

/* The 'dequeue' function remove the head of the 'queue'.
 * It is assumed that the 'queue' is not empty. */
void dequeue(Queue* queue);

/* The 'construct' function constructs an empty 'queue'. */
void construct(Queue* queue);

/* The 'printQueue' function prints the elements in the 'queue' to the stdout. */
void printQueue(Queue queue);
#endif
