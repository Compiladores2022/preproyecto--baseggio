#include "listOfLists.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

int numberOfLists(ListOfLists listOfLists) {
	return listOfLists.lists;
}

List* constructList() {
	List* list = (List*) malloc(sizeof(List));
	if(list == NULL) { exit(EXIT_FAILURE); }
	constructQueue(&(list->queue));
	return list;
}

void constructListOfLists(ListOfLists* listOfLists) {
	listOfLists->peek   = constructList();
	listOfLists->lists = 1;
}

void addList(ListOfLists* listOfLists) {
	List* List = constructList();
	List->next  = listOfLists->peek;
	listOfLists->peek = List;
	listOfLists->lists++;
}

void removeList(ListOfLists* listOfLists) {
	List* List = listOfLists->peek;
	listOfLists->peek = listOfLists->peek->next;
	free(List);
	listOfLists->lists--;
}

int add(ListOfLists* listOfLists, void* data, size_t dataSize) {
	enqueue(&(listOfLists->peek->queue), data, dataSize);
	return TRUE;
}

void printListOfLists(ListOfLists listOfLists, void (*f) (void*)) {
	List* list = listOfLists.peek;
	int i = 0;
	while(list) {
	    printf("\nList %d: \n", listOfLists.lists - i);
	    showQueue(list->queue, f);
	    list = list->next;
	    i++;
	}
}
