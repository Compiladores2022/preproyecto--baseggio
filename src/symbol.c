#include "symbol.h"
#include "utils.h"
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

Symbol* getParams(Symbol symbol) {
    return symbol.params;
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

void setIsFunction(Symbol* symbol) {
    symbol->isFunction = 1;
}

void setIsTemporal(Symbol* symbol) {
	symbol->isTemporal = 1;
}

Symbol* constructPtrToEmptySymbol() {
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->name = allocateChar(32);
    return symbol;
}

Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value) {
    Symbol* symbol = constructPtrToEmptySymbol();
    symbol->flag = flag;
    symbol->type = type;
    strcpy(symbol->name, name);
    symbol->value = value;
    return symbol;
}

Symbol* copy(Symbol* symbol) {
    Symbol* c = constructPtrToSymbol(symbol->flag, symbol->type, symbol->name, symbol->value);
    c->isFunction = symbol->isFunction;
    if(symbol->params) {
        c->params = copy(symbol->params);
    }

    return c;
}

int isFunction(Symbol symbol) {
    return symbol.isFunction;
}

int isGlobal(Symbol symbol) {
	return symbol.global;
}

int isTemporal(Symbol symbol) {
	return symbol.isTemporal;
}

void showSymbol(Symbol symbol) {
    printf("FLAG: %d, NAME: %s, VALUE: %d\n", symbol.flag, symbol.name, symbol.value);
}
