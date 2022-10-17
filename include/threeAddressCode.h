#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "ast.h"
#include "symbol.h"
#include "symbolTable.h"
#include "code.h"
#include "queue.h"

typedef struct instruction{
    Code code;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* dest;
} Instruction;

typedef struct threeAddressCode {
    Queue queue;
} ThreeAddressCode;

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset, int* numberOfLabel);
void showThreeAddressCode(ThreeAddressCode threeAddressCode);
#endif
