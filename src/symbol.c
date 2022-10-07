#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Flag getFlag(Symbol symbol) {
    return symbol.flag;
}

Type getType(Symbol symbol) {
    return symbol.type;
}

char* getName(Symbol symbol) {
    return symbol.name;
}

int getValue(Symbol symbol) {
    return symbol.value;
}

int getOffset(Symbol symbol) {
    return symbol.offset;
}

void setFlag(Symbol* symbol, Flag flag) {
    symbol->flag = flag;
}

void setType(Symbol* symbol, Type type) {
    symbol->type = type;
}

void setName(Symbol* symbol, const char* name) {
    strcpy(symbol->name, name);
}

void setValue(Symbol* symbol, int value) {
    symbol->value = value;
}

void setOffset(Symbol* symbol, int offset) {
    symbol->offset = offset;
}

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
