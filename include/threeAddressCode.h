#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "symbol.h"
#include "operator.h"

typedef struct instruction{
    Operator op;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* result;
} Instruction;

typedef struct threeAddressCode {
    Instruction instruction;
    struct threeAddressCode* nextInstruction;
} ThreeAddressCode;

void constructThreeAddressCode(ThreeAddressCode* threeAddressCode);
void addInstruction(ThreeAddressCode* threeAddressCode, Instruction instruction);
#endif
