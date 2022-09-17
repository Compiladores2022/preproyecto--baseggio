#ifndef SYMBOL_H
#define SYMBOL_H
#include "type.h"
#include "flag.h"

typedef struct {
    Flag flag;
    Type type;
    char* name;
    int value;
} Symbol;

Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value);
void showSymbol(Symbol symbol);
#endif
