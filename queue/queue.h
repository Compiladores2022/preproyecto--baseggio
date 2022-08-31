#ifndef QUEUE_H
#define QUEUE_H
#include "symbol.h"

typedef struct node {
    Symbol* symbol;
    struct node* next;
} TNode;

typedef struct {
   TNode* head;
   int length; 
} Queue;

int length(Queue queue);
int isEmpty(Queue queue);
Symbol* head(Queue queue);
Symbol* lookUp(Queue queue, char* name);
void enqueue(Queue* queue, Symbol* symbol);
void dequeue(Queue* queue);
void construct(Queue* queue);
void show(Queue queue);
void showSymbol(Symbol symbol);
#endif
