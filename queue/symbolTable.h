#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "queue.h"
#include "symbol.h"

typedef struct level {
    Queue queue;
    struct level* next;
} Level;

typedef struct {
    Level* peek;
    int levels;
} SymbolTable;

void constructSymbolTable(SymbolTable* symbolTable);
void openLevel(SymbolTable* symbolTable);
void closeLevel(SymbolTable* symbolTable);
void addSymbol(SymbolTable* symbolTable, Symbol* symbol);
void showSymbolTable(SymbolTable symbolTable);
Symbol* lookUpSymbol(SymbolTable symbolTable);
#endif
