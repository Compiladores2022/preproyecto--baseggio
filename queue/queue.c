#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int length(Queue queue) {
    return queue.length;
}

int isEmpty(Queue queue) {
    return queue.length == 0;
}

Symbol* head(Queue queue) {
    return queue.head->symbol;
}

TNode* constructNode(Symbol* symbol) {
    TNode* node = (TNode*) malloc(sizeof(TNode));
    if(node == NULL) { exit(EXIT_FAILURE); }
    node->symbol = symbol;
    return node;
}

void destructNode(TNode* node) { free(node); }

void enqueue(Queue* queue, Symbol* symbol) {
    TNode* node = constructNode(symbol);
    if(queue->head == NULL) {
        queue->head = node;
    } else {
        TNode* ptr = queue->head;
	while(ptr->next) {
	    ptr = ptr->next;
	}
	ptr->next = node;
    }
    queue->length++;
}

void dequeue(Queue* queue) {
    TNode* node = queue->head;
    queue->head = queue->head->next;
    destructNode(node);
    queue->length--;
}

void construct(Queue* queue) {
    queue->head   = NULL;
    queue->length = 0;
}

Symbol* lookUp(Queue queue, char* name) {
    TNode* ptr = queue.head;
    while(ptr) {
        if(strcmp(ptr->symbol->name, name) == 0) { 
	    return ptr->symbol; 
	} else {
	    ptr = ptr->next;
	}
    }
    return NULL;
}

void show(Queue queue) {
    TNode* ptr = queue.head;
    while(ptr) {
        showSymbol(*(ptr->symbol));
	ptr = ptr->next;
    }
}

void showSymbol(Symbol symbol) {
    printf("FLAG:  %d\n", symbol.flag);
    printf("NAME:  %s\n", symbol.name);
    printf("VALUE: %d\n", symbol.value);
}
