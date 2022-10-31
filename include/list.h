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
 * The 'length' function returns the number of elements in this list.
 */
int length(List list);

/*
 * The 'isEmpty' function returns true if this list contains no elements.
 */
int isEmpty(List list);

/*
 * The 'head' function returns the first element of this list.
 */
void* head(List list);

/*
 * The 'getByIndex' function returns the element at the specified position in this list.
 */
void* getByIndex(List list, int index);

/*
 * The 'lookUp' function returns the first ocurrence of the specified element from this list.
 */
void* lookUp(List list, int (*f) (void*, void*), void* e);

/*
 * The 'add' function appends the specified element to the end of this list.
 */
void add(List* list, void* data, size_t dataSize, int isPtr);

/*
 * The 'addByIndex' inserts the specified element at the specified position in this list.
 */
void addByIndex(List* list, void* data, size_t dataSize, int index, int isPtr);

/*
 * The 'removeFirst' function removes the first element of this list
 */
void removeFirst(List* list);

/*
 * The 'constructList' function constructs an empty list<
 */
void constructList(List* list);

/*
 * The 'print' function prints the elements of this list to the STDOUT
 */
void print(List list, void (*f) (void*));
#endif
