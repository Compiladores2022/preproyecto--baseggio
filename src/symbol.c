#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value) {
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->flag = flag;
    symbol->type = type;
    symbol->name = (char*) malloc(sizeof(char));
    strcpy(symbol->name, name);
    symbol->value = value;
    return symbol;
}

Symbol* copy(Symbol* symbol) {
    Symbol* c = constructPtrToSymbol(symbol->flag, symbol->type, symbol->name, symbol->value);
    if(symbol->params) {
        c->params = copy(symbol->params);
    }

    return c;
}

int isFunction(Symbol symbol) {
    return symbol.isFunction;
}

void showSymbol(Symbol symbol) {
    printf("FLAG: %d, NAME: %s, VALUE: %d\n", symbol.flag, symbol.name, symbol.value);
}
