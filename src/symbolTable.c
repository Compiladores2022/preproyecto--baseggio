#include "symbolTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

int numberOfLocals(SymbolTable symbolTable) {
    return length(symbolTable.peek->queue);
}

int compareByName(void* s, void* name) {
  Symbol* symbol = (Symbol*) s;
  return strcmp(getName(*symbol), name) == 0;
}

void printData(void* data) {
  Symbol* symbol = (Symbol*) data;
  printf("%s ", getName(*symbol));
}

int addSymbol(SymbolTable* symbolTable, Symbol* symbol) {
    int found = lookUp(symbolTable->peek->queue, compareByName, getName(*symbol)) != NULL;
    if(!found) {
      enqueue(&(symbolTable->peek->queue), (void*) symbol, sizeof(Symbol*));
      return TRUE;
    }

    return FALSE;
}

Level* constructLevel() {
    Level* level = (Level*) malloc(sizeof(Level));
    if(level == NULL) { exit(EXIT_FAILURE); }
    constructQueue(&level->queue);
    return level;
}

void constructSymbolTable(SymbolTable* symbolTable) {
    symbolTable->peek   = constructLevel();
    symbolTable->levels = 1;
}

void openLevel(SymbolTable* symbolTable) {
    Level* level = constructLevel();
    level->next  = symbolTable->peek;
    symbolTable->peek = level;
    symbolTable->levels++;
}

void closeLevel(SymbolTable* symbolTable) {
    Level* level = symbolTable->peek;
    symbolTable->peek = symbolTable->peek->next;
    free(level);
    symbolTable->levels--;
}

void printSymbolTable(SymbolTable symbolTable) {
    Level* level = symbolTable.peek;
    int i = 0;
    printf("\n--- SYMBOL TABLE ---\n");
    while(level) {
	    printf("\nLevel %d: \n", symbolTable.levels - i);
        showQueue(level->queue, printData);
	    level = level->next;
	    i++;
    }

    printf("\n--- SYMBOL TABLE ---\n");
}

Symbol* lookUpSymbol(SymbolTable symbolTable, char* name) {
    Level* level = symbolTable.peek;
    Symbol* symbol;
    while(level) {
	if((symbol = lookUp(level->queue, compareByName, name)))
	    return symbol;
	level = level->next;
    }

    return NULL;
}

Symbol* checkIdentifierIsDeclared(SymbolTable symbolTable, char* name) {
    Symbol* symbol;
    if(!(symbol = lookUpSymbol(symbolTable, name))) {
        printf("Undeclared identifier: %s\n", name);
	exit(EXIT_FAILURE);
    }

    return symbol;
}
