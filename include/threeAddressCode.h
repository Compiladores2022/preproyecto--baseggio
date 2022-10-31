#ifndef THREEADDRESSCODE_H
#define THREEADDRESSCODE_H
#include "symbol.h"
#include "symbolTable.h"
#include "listOfLists.h"
#include "ast.h"
#include "code.h"
#include "list.h"

typedef struct instruction{
    Code code;
    Symbol* fstOperand;
    Symbol* sndOperand;
    Symbol* dest;
} Instruction;

typedef struct threeAddressCode {
    List list;
    List freeOffsets;
    //ListOfLists freeOffsets;
    int numberOfTemporaries;
    int offset;
    int numberOfLabel;
} ThreeAddressCode;

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode);
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode);
void ThreeAddressCode_construct(ThreeAddressCode* threeAddressCode);
void showThreeAddressCode(ThreeAddressCode threeAddressCode);
#endif
