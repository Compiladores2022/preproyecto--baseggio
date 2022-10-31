#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int length(List list) {
  return list.length;
}

int isEmpty(List list) {
  return length(list) == 0;
}

void* head(List list) {
  return list.head->data;
}

void* getByIndex(List list, int index) {
	if(index < length(list)) {
			TNode* ptr = list.head;
			while(index > 0) {
				ptr = ptr->next;
				index--;
			}
			
			return ptr->data;
	}
	return NULL;
}

void* lookUp(List list, int (*f) (void*, void*), void* e) {
  TNode* node = list.head;
  while(node) {
    if((*f) (node->data, e)) {
      return node->data;
    }
    node = node->next;
  }

  return NULL;
}

TNode* constructNode(void* data, size_t dataSize, int isPtr) {
  TNode* node = (TNode*) malloc(sizeof(TNode));
  if(node == NULL) {
    printf("Error allocating memory for TNode\n");
    exit(EXIT_FAILURE);
  }

  node->data = malloc(dataSize);

  if(node->data == NULL) {
    printf("Error allocating memory for data");
    exit(EXIT_FAILURE);
  }

  if(isPtr) {
  	node->data = data;
  } else {
  	memcpy(node->data, data, dataSize);
  }

  return node;
}

void add(List* list, void* data, size_t dataSize, int isPtr) {
  TNode* node = constructNode(data, dataSize, isPtr);
  if(isEmpty(*list)) {
    list->head = node;
    list->last = node;
  } else {
    list->last->next = node;
    list->last       = node;
  }

  list->length++;
}

void addByIndex(List* list, void* data, size_t dataSize, int index, int isPtr) {
	if(index <= length(*list)) {
		TNode* node = constructNode(data, dataSize, isPtr);
		if(index == 0) {
			if(isEmpty(*list)) {
				list->head = node;
				list->last    = node;
			} else {
				node->next = list->head;
				list->head = node;
			}
		} else {
			TNode* ptr = list->head;
			while(index - 1 > 0) {
				ptr = ptr->next;
				index--;
			}
		
			node->next = ptr->next;
			ptr->next = node;
		}
		
		list->length++;
	}
}

void removeFirst(List* list) {
	if(!isEmpty(*list)) {
		TNode* node = list->head;
		list->head = list->head->next;
		free(node);
		list->length--;
	}
}

void print(List list, void (*f) (void*)) {
	TNode* node = list.head;
	while(node) {
		(*f) (node->data);
		node = node->next;
	}
}

void constructList(List* list) {
  list->head = list->last = NULL;
  list->length = 0;
}
