#ifndef STACK_H

typedef struct node {
    int data;
    struct node* next;
} TNode;

typedef struct {
    TNode* peek;
    int length;
} Stack;

int length(Stack stack);
int isEmpty(Stack stack);
void push(Stack* stack, int data);
void pop(Stack* stack);
void construct(Stack* stack);
void show(Stack stack);

#endif
