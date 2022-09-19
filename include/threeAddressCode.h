#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "ast.h"
#include "symbol.h"
#include "flag.h"
#include "queue.h"

typedef struct instruction{
    Flag op;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* dest;
} Instruction;

typedef struct threeAddressCode {
    Queue queue;
    int ctr;
} ThreeAddressCode;

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset);

void showThreeAddressCode(ThreeAddressCode threeAddressCode);
#endif
