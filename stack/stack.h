#ifndef STACK_H

typedef struct node {
    void* data;
    struct node* next;
} TNode;

typedef struct {
    TNode* peek;
    int length;
} Stack;

/* The 'length' function returns the length of the 'stack'. */
int length(Stack stack);

/* The 'isEmpty' function returns ZERO iff the 'stack' is not empty. Otherwise it returns a non-zero number.  */
int isEmpty(Stack stack);

/* The 'peek' function returns a pointer to void which corresponds to the 'data' stored at the peek of the 'stack' */
void* peek(Stack stack);

/* The 'push' function add the element 'data' to the 'stack'. To prevent data corruption the caller must pass as parameter a copy of 'data'. */
void push(Stack* stack, void* data);

/* The 'pop' function remove the peek of the 'stack'. */
void pop(Stack* stack);

/* The 'construct' function initializes the 'stack'. */
void construct(Stack* stack);

#endif
