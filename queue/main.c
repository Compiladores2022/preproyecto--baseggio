#include <stdio.h>
#include <stdlib.h>
#include "symbolTable.h"

Queue queue;

int main() {
    SymbolTable symbolTable;
    constructSymbolTable(&symbolTable);

    Symbol s1, s2;
    s1.flag = ID;
    s1.name = "x";
    s1.value = 0;
    s2.flag = ID;
    s2.name = "y";
    s2.value = 1;
    addSymbol(&symbolTable, &s1);
    addSymbol(&symbolTable, &s2);
    openLevel(&symbolTable);
    showSymbolTable(symbolTable);
}
