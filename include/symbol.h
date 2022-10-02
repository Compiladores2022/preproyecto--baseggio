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
} Symbol;

Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value);
void showSymbol(Symbol symbol);
#endif
