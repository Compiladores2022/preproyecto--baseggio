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

/* The 'constructSymbolTable' function constructs an empty 'symbolTable'. */
void constructSymbolTable(SymbolTable* symbolTable);

/* The 'openLevel' function adds a new level to the 'symbolTable'. */
void openLevel(SymbolTable* symbolTable);

/* The 'closeLevel' function closes the most recently opened level in the 'symbolTable'. 
 * It is assumed that the 'symbolTable' has at least one level. */
void closeLevel(SymbolTable* symbolTable);

/* The 'addSymbol' function adds a new reference to a symbol in the 'symbolTable'. */
int addSymbol(SymbolTable* symbolTable, Symbol* symbol);

/* The 'printSymbolTable' function prints the elements in the 'symbolTable' to the stdout. */
void showSymbolTable(SymbolTable symbolTable);

/* The 'lookUpSymbol' function look for a symbol by its name in the 'symbolTable'. 
 * It returns a reference to the symbol if it is found otherwise returns NULL. */
Symbol* lookUpSymbol(SymbolTable symbolTable, char* name);

Symbol* checkIdentifierIsDeclared(SymbolTable symbolTable, char* name);
#endif
