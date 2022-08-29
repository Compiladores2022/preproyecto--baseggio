#include <stdlib.h>
#include "stack.h"

int length(Stack stack) {
    return stack.length;
}

int isEmpty(Stack stack) {
    return stack.length == 0;
}

TNode* constructNode(int data) {
    TNode* node = (TNode*) malloc(sizeof(TNode));
    if(node == NULL) { exit(EXIT_FAILURE); }
    node->data = data;
    return node;
}

void destructNode(TNode* node) { free(node); }

void push(Stack* stack, int data) {
    TNode* node = constructNode(data);
    node->next  = stack->peek;
    stack->peek = node;
    stack->length++;
}

void pop(Stack* stack) {
    TNode* node = stack->peek;
    stack->peek = stack->peek->next;
    destructNode(node);
    stack->length--;
}

void construct(Stack* stack) {
    stack->peek   = NULL;
    stack->length = 0;
}

void show(Stack stack) {
    TNode* ptr = stack.peek;
    while(ptr) {
        printf(" %d ->", ptr->data);
	ptr = ptr->next;
    }
    printf(" NULL\n");
}
