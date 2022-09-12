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
            Symbol* fstOperand = generateThreeAddressCode(node->lSide, threeAddressCode);
            Symbol* sndOperand = generateThreeAddressCode(node->rSide, threeAddressCode);
            // renombrar node->symbol
            addInstruction(threeAddressCode, createInstruction(flag, fstOperand, sndOperand, node->symbol));
            return node->symbol;
        }
        
        if(flag == flag_ASSIGNMENT) {
            Symbol* expr = generateThreeAddressCode(node->rSide, threeAddressCode);
            addInstruction(threeAddressCode, createInstruction(flag, expr, NULL, node->symbol));
        }
        
        if(flag == flag_RETURN) {
            Symbol* expr = generateThreeAddressCode(node->lSide, threeAddressCode);
            addInstruction(threeAddressCode, createInstruction(flag, NULL, NULL, expr));
        }
        
        if(flag == flag_SEMICOLON) {
            generateThreeAddressCode(node->lSide, threeAddressCode);
            generateThreeAddressCode(node->rSide, threeAddressCode);
        }
    }
    
    return NULL;
}
