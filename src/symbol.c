#include "symbol.h"
#include <stdio.h>

void showSymbol(Symbol symbol) {
    printf("FLAG: %d, NAME: %s, VALUE: %d\n", symbol.flag, symbol.name, symbol.value);
}
