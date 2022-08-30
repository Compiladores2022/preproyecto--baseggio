#ifndef STACK_H

typedef struct node {
    void* data;
    struct node* next;
} TNode;

typedef struct {
    TNode* peek;
    int length;
} Stack;

int length(Stack stack);
int isEmpty(Stack stack);
void* peek(Stack stack);
void push(Stack* stack, void* data);
void pop(Stack* stack);
void construct(Stack* stack);

#endif
