#include <stdlib.h>
#include "queue.h"

int length(Queue queue) {
    return queue.length;
}

int isEmpty(Queue queue) {
    return queue.length == 0;
}

TNode* constructNode(int data) {
    TNode* node = (TNode*) malloc(sizeof(TNode));
    if(node == NULL) { exit(EXIT_FAILURE); }
    node->data = data;
    return node;
}

void destructNode(TNode* node) {
    free(node);
}

void enqueue(Queue* queue, int data) {
    TNode* node = constructNode(data);
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
    queue->head  = queue->head->next;
    destructNode(node);
    queue->length--;
}

void construct(Queue* queue) {
    queue->head   = NULL;
    queue->length = 0;
}

void show(Queue queue) {
    TNode* ptr = queue.head;
    while(ptr) {
        printf(" %d ->", ptr->data);
	ptr = ptr->next;
    }
    printf(" NULL\n");
}
