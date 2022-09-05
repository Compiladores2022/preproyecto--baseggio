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

void showSymbol(Symbol symbol);
#endif
