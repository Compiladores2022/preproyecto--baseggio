#include <stdlib.h>
#include "queue.h"

int length(Queue queue) {
    return queue.length;
}

int isEmpty(Queue queue) {
    return queue.length == 0;
}

void* head(Queue queue) {
    return queue.head->data;
}

TNode* constructNode(void* data) {
    TNode* node = (TNode*) malloc(sizeof(TNode));
    if(node == NULL) { exit(EXIT_FAILURE); }
    node->data = data;
    return node;
}

void destructNode(TNode* node) {
    free(node);
}

void enqueue(Queue* queue, void* data) {
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
    queue->head = queue->head->next;
    destructNode(node);
    queue->length--;
}

void construct(Queue* queue) {
    queue->head   = NULL;
    queue->length = 0;
}
