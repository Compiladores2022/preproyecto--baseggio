#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "ast.h"
#include "symbol.h"
#include "flag.h"

typedef struct instruction{
    Flag op;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* dest;
} Instruction;

typedef struct threeAddressCodeNode {
    Instruction instruction;
    struct threeAddressCodeNode* next;
} TACNode;

typedef struct threeAddressCode {
    TACNode* head;
    TACNode* last;
    int ctr;
} ThreeAddressCode;

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode);

void showThreeAddressCode(ThreeAddressCode threeAddressCode);
#endif
