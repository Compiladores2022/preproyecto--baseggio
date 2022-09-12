#include <stdlib.h>
#include "threeAddressCode.h"

void constructThreeAddressCode(ThreeAddressCode* threeAddressCode) {
    threeAddressCode = NULL;
}

Instruction createInstruction(Flag operator, Symbol* fstOperand, Symbol* sndOperand, Symbol* result) {
    Instruction i;
    i.op = operator;
    i.fstOperand = fstOperand;
    i.sndOperand = sndOperand;
    i.result = result;
    return i;
}

void addInstruction(ThreeAddressCode* threeAddressCode, Instruction instruction) {

}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode) {
    if(node) {
        if(isLeave(node)) { return node->symbol; }
        Flag flag = node->symbol->flag;
        if(isABinaryOperator(flag)) {
            Symbol* fstOperand = generateIntermediateCode(node->lSide, threeAddressCode);
            Symbol* sndOperand = generateIntermediateCode(node->rSide, threeAddressCode);
            // renombrar node->symbol
            addInstruction(threeAddressCode, createInstruction(flag, fstOperand, sndOperand, node->symbol));
            return node->symbol;
        }
        
        if(flag == flag_ASSIGNMENT) {
            Symbol* expr = generateIntermediateCode(node->rSide, threeAddressCode);
            addInstruction(threeAddressCode, createInstruction(flag, expr, NULL, node->symbol));
        }
        
        if(flag == flag_RETURN) {
            Symbol* expr = generateIntermediateCode(node->lSide, threeAddressCode);
            addInstruction(threeAddressCode, createInstruction(flag, NULL, NULL, expr));
        }
        
        if(flag == flag_SEMICOLON) {
            generateIntermediateCode(node->lSide, threeAddressCode);
            generateIntermediateCode(node->rSide, threeAddressCode);
        }
    }
    
    return NULL;
}
