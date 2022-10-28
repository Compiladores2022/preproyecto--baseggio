#ifndef LISTOFLISTS_H
#define LISTOFLISTS_H

#include <stdlib.h>
#include "queue.h"

typedef struct list {
	Queue queue;
	struct list *next;
} List;

typedef struct {
	List* peek;
	int lists;
} ListOfLists;

int numberOfLevels(ListOfLists listOfLists);

void constructListOfLists(ListOfLists* listOfLists);

void addList(ListOfLists* listOfLists);

void removeList(ListOfLists* listOfLists);

int add(ListOfLists* listOfLists, void* data, size_t dataSize);

void printListOfLists(ListOfLists listOfLists, void (*f) (void*));

#endif
