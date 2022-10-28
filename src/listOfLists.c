#include "listOfLists.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

int numberOfLevels(ListOfLists listOfLists) {
	return listOfLists.levels;
}

Level* constructList() {
	Level* level = (Level*) malloc(sizeof(Level));
	if(level == NULL) { exit(EXIT_FAILURE); }
	constructQueue(&(level->queue));
	return level;
}

void constructListOfLists(ListOfLists* listOfLists) {
	listOfLists->peek   = constructList();
	listOfLists->levels = 1;
}

void addList(ListOfLists* listOfLists) {
	Level* level = constructList();
	level->next  = listOfLists->peek;
	listOfLists->peek = level;
	listOfLists->levels++;
}

void removeList(ListOfLists* listOfLists) {
	Level* level = listOfLists->peek;
	listOfLists->peek = listOfLists->peek->next;
	free(level);
	listOfLists->levels--;
}

int add(ListOfLists* listOfLists, void* data, size_t dataSize) {
	enqueue(&(listOfLists->peek->queue), data, dataSize);
	return TRUE;
}

void printListOfLists(ListOfLists listOfLists, void (*f) (void*)) {
	Level* level = listOfLists.peek;
	int i = 0;
	while(level) {
	    printf("\nLevel %d: \n", listOfLists.levels - i);
	    showQueue(level->queue, f);
	    level = level->next;
	    i++;
	}
}
