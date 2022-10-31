#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "symbol.h"
#include "list.h"

typedef struct SymbolTable_level {
	List list;
	struct SymbolTable_level* next;
} SymbolTable_Level;

typedef struct {
    SymbolTable_Level* peek;
    int levels;
} SymbolTable;

int     SymbolTable_levels(SymbolTable symbolTable);

/* The 'constructSymbolTable' function constructs an empty 'symbolTable'. */
void    SymbolTable_construct(SymbolTable* symbolTable);

/* The 'openLevel' function adds a new level to the 'symbolTable'. */
void    SymbolTable_openLevel(SymbolTable* symbolTable);

/* The 'closeLevel' function closes the most recently opened level in the 'symbolTable'. 
 * It is assumed that the 'symbolTable' has at least one level. */
void    SymbolTable_closeLevel(SymbolTable* symbolTable);

/* The 'addSymbol' function adds a new reference to a symbol in the 'symbolTable'. */
void	SymbolTable_add(SymbolTable* symbolTable, Symbol* symbol);

/* The 'printSymbolTable' function prints the elements in the 'symbolTable' to the stdout. */
void    SymbolTable_print(SymbolTable symbolTable);

/* The 'lookUpSymbol' function look for a symbol by its name in the 'symbolTable'. 
 * It returns a reference to the symbol if it is found otherwise returns NULL. */
Symbol* SymbolTable_lookUp(SymbolTable symbolTable, char* name);

Symbol* checkIdentifierIsDeclared(SymbolTable symbolTable, char* name);
#endif
