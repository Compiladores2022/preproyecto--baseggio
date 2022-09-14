#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threeAddressCode.h"

TACNode* constructTACNode(Instruction instruction) {
    TACNode* node = (TACNode*) malloc(sizeof(TACNode));
    if(node == NULL) { exit(EXIT_FAILURE); }
    node->instruction = instruction;
    return node;
}

Instruction constructInstruction(Flag op, Symbol* fstOperand, Symbol* sndOperand, Symbol* dest) {
    Instruction i;
    i.op = op;
    i.fstOperand = fstOperand;
    i.sndOperand = sndOperand;
    i.dest = dest;
    return i;
}

int isEmptyThreeAddressCode(ThreeAddressCode threeAddressCode) {
    return threeAddressCode.head == NULL;
}

void addInstruction(ThreeAddressCode* threeAddressCode, Instruction instruction) {
    TACNode* node = constructTACNode(instruction);
    if(isEmptyThreeAddressCode(*threeAddressCode)) {
        threeAddressCode->head = node;
        threeAddressCode->last = node;
    } else {
        threeAddressCode->last->next = node;
        threeAddressCode->last       = node;
    }
}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode) {
    if(node) {
        if(isLeave(node)) { return node->symbol; }
        Flag flag = node->symbol->flag;
        if(isABinaryOperator(flag)) {
            Symbol* fstOperand = generateIntermediateCode(node->lSide, threeAddressCode);
            Symbol* sndOperand = generateIntermediateCode(node->rSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, fstOperand, sndOperand, node->symbol);
            addInstruction(threeAddressCode, instruction);
            sprintf(node->symbol->name, "t%d", threeAddressCode->ctr++);
            //FOR DEBUG
            printf("%s %s %s %s\n", flagToString(flag), fstOperand->name, sndOperand->name, node->symbol->name);
            return node->symbol;
        }
        
        if(flag == flag_ASSIGNMENT) {
            Symbol* expr = generateIntermediateCode(node->rSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, expr, NULL, node->symbol);
            addInstruction(threeAddressCode, instruction);
            //FOR DEBUG
            printf("%s %s NULL %s\n", flagToString(flag), expr->name, node->lSide->symbol->name);
        }
        
        if(flag == flag_RETURN) {
            Symbol* expr = generateIntermediateCode(node->lSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, NULL, NULL, expr);
            addInstruction(threeAddressCode, instruction);
            printf("%s NULL NULL %s\n", flagToString(flag), expr->name);
        }
        
        if(flag == flag_SEMICOLON) {
            generateIntermediateCode(node->lSide, threeAddressCode);
            generateIntermediateCode(node->rSide, threeAddressCode);
        }
    }
    
    return NULL;
}

/*void constructThreeAddressCode(ThreeAddressCode* threeAddressCode) {
    threeAddressCode->head = NULL;
    threeAddressCode->last = NULL;
    threeAddressCode->ctr  = 0;
}*/
