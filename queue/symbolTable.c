#include "symbolTable.h"
#include "queue.c"

void addSymbol(SymbolTable* symbolTable, Symbol* symbol) {
    enqueue(&symbolTable->peek->queue, symbol);
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
