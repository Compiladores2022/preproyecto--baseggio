#ifndef LISTOFLISTS_H
#define LISTOFLISTS_H
#include "symbol.h"
#include "list.h"

typedef struct ListOfLists_level {
	List list;
	struct ListOfLists_level* next;
} ListOfLists_Level;

typedef struct {
    ListOfLists_Level* peek;
    int levels;
} ListOfLists;

int     ListOfLists_levels(ListOfLists list);

void*	ListOfLists_head(ListOfLists list);

void    ListOfLists_construct(ListOfLists* list);

void    ListOfLists_openLevel(ListOfLists* list);

void    ListOfLists_closeLevel(ListOfLists* list);

int     ListOfLists_add(ListOfLists* list, void* data, size_t dataSize);

void	ListOfLists_remove(ListOfLists* list);

void    ListOfLists_print(ListOfLists list, char* (*toString) (void*));

void* 	ListOfLists_lookUp(ListOfLists list, int (*f) (void*, void*), void* e);

#endif
