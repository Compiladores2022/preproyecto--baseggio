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
    int numberOfTemporaries; /* TODO: numberOfTemporaries changes in each level */
} ThreeAddressCode;

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset);
//void generateAssembler(ThreeAddressCode threeAddressCode, SymbolTable symbolTable);
void showThreeAddressCode(ThreeAddressCode threeAddressCode);
#endif
