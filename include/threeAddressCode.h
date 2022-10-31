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
    int numberOfTemporaries;
    int offset;
    int numberOfLabel;
} ThreeAddressCode;

/* The 'generateIntermediateCode' function generates the three address code from the AST. */
Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode);

/* The 'ThreeAddressCode_construct' function initializes the ThreeAddressCode */
void ThreeAddressCode_construct(ThreeAddressCode* threeAddressCode);

/* The 'ThreeAddressCode_print' function prints the ThreeAddressCode */
void ThreeAddressCode_print(ThreeAddressCode threeAddressCode);
#endif
