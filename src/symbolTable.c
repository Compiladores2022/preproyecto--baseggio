#include "symbolTable.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
/* #include "queue.c"
#include "symbol.c" */

#define TRUE  1
#define FALSE 0

int addSymbol(SymbolTable* symbolTable, Symbol* symbol) {
    if(lookUp(symbolTable->peek->queue, symbol->name) == NULL) {
        enqueue(&symbolTable->peek->queue, symbol);
        return TRUE;
    }
    return FALSE;
}

Level* constructLevel() {
    Level* level = (Level*) malloc(sizeof(Level));
    if(level == NULL) { exit(EXIT_FAILURE); }
    construct(&level->queue);
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

void showSymbolTable(SymbolTable symbolTable) {
    Level* level = symbolTable.peek;
    int i = 0;
    while(level) {
	printf("Level %d: \n", symbolTable.levels - i);
        show(level->queue);
	level = level->next;
	i++;
    }
}

Symbol* lookUpSymbol(SymbolTable symbolTable, char* name) {
    Level* level = symbolTable.peek;
    Symbol* symbol;
    while(level) {
	if((symbol = lookUp(level->queue, name)))
	    return symbol;
	level = level->next;
    }

    return NULL;
}
