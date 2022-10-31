#include "listOfLists.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

int     ListOfLists_levels(ListOfLists list) {
	return list.levels;
}

void*	ListOfLists_head(ListOfLists list) {
	return head(list.peek->list);
}

ListOfLists_Level* Level_construct() {
    ListOfLists_Level* level = (ListOfLists_Level*) malloc(sizeof(ListOfLists_Level));
    if(level == NULL) { exit(EXIT_FAILURE); }
    constructList(&level->list);
    return level;
}

void    ListOfLists_construct(ListOfLists* list) {
	list->peek = Level_construct();
	list->peek->next = NULL;
	list->levels = 1;
}

void    ListOfLists_openLevel(ListOfLists* list) {
	ListOfLists_Level* level = Level_construct();
	level->next = list->peek;
	list->peek = level;
	list->levels++;
}

void    ListOfLists_closeLevel(ListOfLists* list) {
	ListOfLists_Level* level = list->peek;
	list->peek = list->peek->next;
	free(level);
	list->levels--;
}

int     ListOfLists_add(ListOfLists* list, void* data, size_t dataSize) {
	add(&list->peek->list, data, dataSize, FALSE);
	return TRUE;
}

void 	ListOfLists_remove(ListOfLists* list) {
	removeFirst(&list->peek->list);
}

void    ListOfLists_print(ListOfLists list, char* (*toString) (void*)) {
	ListOfLists_Level* level = list.peek;
	int i = 0;
	while(level) {
		printf("\nLevel %d: \n", list.levels - i);
		for(int j = 0; j < length(level->list); j++) {
			void* data = getByIndex(level->list, j);
			printf("%s ", (*toString) (data));
		}
		level = level->next;
		i++;
	}
}

void* 	ListOfLists_lookUp(ListOfLists list, int (*f) (void*, void*), void* e) {
	ListOfLists_Level* level = list.peek;
	void* data;
	while(level) {
		if((data = lookUp(level->list, f, e))) {
			return data;
		}
		level = level->next;
	}

	return NULL;
}
