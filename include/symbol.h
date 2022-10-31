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
    int global;
    int isTemporal;
    int hasOffset;
} Symbol;

Flag getFlag(Symbol symbol);
Type getType(Symbol symbol);
char* getName(Symbol symbol);
int getValue(Symbol symbol);
int getOffset(Symbol symbol);

Symbol* getParams(Symbol symbol);

void setFlag(Symbol* symbol, Flag flag);
void setType(Symbol* symbol, Type type);
void setName(Symbol* symbol, const char* name);
void setValue(Symbol* symbol, int value);
void setOffset(Symbol* symbol, int offset);

void setIsFunction(Symbol* symbol);
void setIsTemporal(Symbol* symbol);

Symbol* constructPtrToEmptySymbol();
Symbol* constructPtrToSymbol(Flag flag, Type type, char* name, int value);
Symbol* copy(Symbol* symbol);
int isFunction(Symbol symbol);
int isGlobal(Symbol symbol);
int isTemporal(Symbol symbol);
int hasOffset(Symbol symbol);

void showSymbol(Symbol symbol);
#endif
