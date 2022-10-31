#include "symbolTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

int SymbolTable_levels(SymbolTable symbolTable) {
	return symbolTable.levels;
}

int compareByName(void* s, void* name) {
  Symbol* symbol = (Symbol*) s;
  return strcmp(getName(*symbol), (char*) name) == 0;
}

void printData(void* data) {
  printf("%s", getName(*((Symbol*) data)));
}

int SymbolTable_add(SymbolTable* symbolTable, Symbol* symbol) {
    int found = lookUp(symbolTable->peek->list, compareByName, getName(*symbol)) != NULL;
    if(!found) {
      add(&symbolTable->peek->list, (void*) symbol, sizeof(Symbol*), TRUE);
      return TRUE;
    }

    return FALSE;
}

SymbolTable_Level* Level_construct() {
    SymbolTable_Level* level = (SymbolTable_Level*) malloc(sizeof(SymbolTable_Level));
    if(level == NULL) { exit(EXIT_FAILURE); }
    constructList(&level->list);
    return level;
}

void SymbolTable_construct(SymbolTable* symbolTable) {
    symbolTable->peek = Level_construct();
    symbolTable->peek->next = NULL;
    symbolTable->levels = 1;
}

void SymbolTable_openLevel(SymbolTable* symbolTable) {
    SymbolTable_Level* level = Level_construct();
    level->next = symbolTable->peek;
    symbolTable->peek = level;
    symbolTable->levels++;
}

void SymbolTable_closeLevel(SymbolTable* symbolTable) {
    SymbolTable_Level* level = symbolTable->peek;
    symbolTable->peek = symbolTable->peek->next;
    free(level);
    symbolTable->levels--;
}

void SymbolTable_print(SymbolTable symbolTable) {
    SymbolTable_Level* level = symbolTable.peek;
    int i = 0;
    printf("\n--- SYMBOL TABLE ---\n");
    while(level) {
		printf("\nLevel %d: \n", symbolTable.levels - i);
        	print(level->list, printData);
	    	level = level->next;
	    	i++;
    }

    printf("\n--- SYMBOL TABLE ---\n");
}

Symbol* SymbolTable_lookUp(SymbolTable symbolTable, char* name) {
    SymbolTable_Level* level = symbolTable.peek;
    Symbol* symbol;
    while(level) {
	if((symbol = lookUp(level->list, compareByName, name))) {
		return symbol;
	}
	level = level->next;
    }

    return NULL;
}

Symbol* checkIdentifierIsDeclared(SymbolTable symbolTable, char* name) {
    Symbol* symbol;
    if(!(symbol = SymbolTable_lookUp(symbolTable, name))) {
        printf("Undeclared identifier: %s\n", name);
	exit(EXIT_FAILURE);
    }

    return symbol;
}
