#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct node {
  void* data;
  struct node* next;
} TNode;

typedef struct {
  TNode* head;
  TNode* last;
  int length;
} List;

/*
 * Returns the number of elements in this list.
 */
int length(List list);

/*
 * Returns true if this list contains no elements.
 */
int isEmpty(List list);

/*
 * Returns the first element of this list.
 */
void* head(List list);

/*
 * Returns the element at the specified position in this list.
 */
void* getByIndex(List list, int index);

/*
 * Returns the first ocurrence of the specified element from this list.
 */
void* lookUp(List list, int (*f) (void*, void*), void* e);

/*
 * Appends the specified element to the end of this list.
 */
void add(List* list, void* data, size_t dataSize, int isPtr);

/*
 * Inserts the specified element at the specified position in this list.
 */
void addByIndex(List* list, void* data, size_t dataSize, int index, int isPtr);

/*
 * Removes the first element of this list
 */
void removeFirst(List* list);

/*
 * Constructs an empty list
 */
void constructList(List* list);

/*
 * Prints the elements of this list
 */
void print(List list, void (*f) (void*));
#endif
