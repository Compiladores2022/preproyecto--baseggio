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

/* The 'constructPtrToEmptySymbol' function returns a reference to an empty symbol. */
Symbol*	constructPtrToEmptySymbol();

/* The 'constructPtrToSymbol' function constructs a symbol and returns a reference to that symbol. */
Symbol*	constructPtrToSymbol(Flag flag, Type type, char* name, int value);

/* The 'getFlag' function returns the Flag associated to the symbol. */
Flag getFlag(Symbol symbol);

/* The 'getType' function returns the Type associated to the symbol. */
Type getType(Symbol symbol);

/* The 'getName' function returns the name associated to the symbol. */
char* getName(Symbol symbol);

/* The 'getValue' function returns the value associated to the symbol. */
int getValue(Symbol symbol);

/* The 'getOffset' function returns the offset associated to the symbol. */
int getOffset(Symbol symbol);

/* The 'getParams' function returns a reference to the first parameter of the symbol,
 * If it has no parameters returns NULL.
 */
Symbol* getParams(Symbol symbol);

/* The 'isFunction' function returns TRUE iff the symbol corresponds to a function. */
int isFunction(Symbol symbol);

/* The 'isGlobal' function returns TRUE iff the scope of the symbol is global. */
int isGlobal(Symbol symbol);

/* The 'isTemporal' function returns TRUE iff the symbol corresponds to a temporal identifier. */
int isTemporal(Symbol symbol);

/* The 'hasOffset' function returns TRUE iff the symbol has an associated offset. */
int hasOffset(Symbol symbol);

/* The 'setFlag' function associates the symbol with a given Flag. */
void setFlag(Symbol* symbol, Flag flag);

/* The 'setType' function associates the symbol with a given Type. */
void setType(Symbol* symbol, Type type);

/* The 'setName' function associates the symbol with a given name. */
void setName(Symbol* symbol, const char* name);

/* The 'setValue' function associates the symbol with a given value. */
void setValue(Symbol* symbol, int value);

/* The 'setOffset' function associates the symbol with a given offset. */
void setOffset(Symbol* symbol, int offset);

/* The 'setIsGlobal' function sets the symbol with a global scope. */
void setIsGlobal(Symbol* symbol);

/* The 'setIsFunction' function sets the symbol as a function. */
void setIsFunction(Symbol* symbol);

/* The 'setIsTemporal' function sets the symbol as a temporal. */
void setIsTemporal(Symbol* symbol);

/* The 'copy' function returns a reference to a copy of a given symbol. */
Symbol* copy(Symbol* symbol);

/* The 'showSymbol' function prints the symbol to the STDOUT. */
void showSymbol(Symbol symbol);
#endif
