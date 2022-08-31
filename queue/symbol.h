#ifndef SYMBOL_H
#define SYMBOL_H
#include "flag.h"

typedef struct {
    Flag flag;
    char* name;
    int value;
} Symbol;
#endif
