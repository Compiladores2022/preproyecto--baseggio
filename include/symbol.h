#ifndef SYMBOL_H
#define SYMBOL_H
#include "type.h"
#include "flag.h"

typedef struct symbol {
    Flag flag;
    Type type;
    char* name;
    int value;
    struct symbol* params;
    int offset;
    int isFunction;
} Symbol;

Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value);
Symbol* copy(Symbol* symbol);
int isFunction(Symbol symbol);

void showSymbol(Symbol symbol);
#endif
