#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "ast.h"
#include "symbol.h"
#include "flag.h"

typedef struct instruction{
    Flag op;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* result;
} Instruction;

typedef struct threeAddressCode {
    Instruction instruction;
    struct threeAddressCode* nextInstruction;
} ThreeAddressCode;

void constructThreeAddressCode(ThreeAddressCode* threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode);
#endif
