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
        if(isLeave(node)) { 
        node->symbol->name = (char*) malloc(sizeof(char));
        sprintf(node->symbol->name, "%d", node->symbol->value);
        return node->symbol; }
        Flag flag = node->symbol->flag;
        if(isABinaryOperator(flag)) {
            Symbol* fstOperand = generateIntermediateCode(node->lSide, threeAddressCode);
            Symbol* sndOperand = generateIntermediateCode(node->rSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, fstOperand, sndOperand, node->symbol);
            addInstruction(threeAddressCode, instruction);
            
            //FOR DEBUG
            sprintf(node->symbol->name, "t%d", threeAddressCode->ctr++);
            return node->symbol;
        }
        
        if(flag == flag_ASSIGNMENT) {
            Symbol* expr = generateIntermediateCode(node->rSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, expr, NULL, node->lSide->symbol);
            addInstruction(threeAddressCode, instruction);
        }
        
        if(flag == flag_RETURN) {
            Symbol* expr = generateIntermediateCode(node->lSide, threeAddressCode);
            Instruction instruction = constructInstruction(flag, NULL, NULL, expr);
            addInstruction(threeAddressCode, instruction);
        }
        
        if(flag == flag_SEMICOLON) {
            generateIntermediateCode(node->lSide, threeAddressCode);
            generateIntermediateCode(node->rSide, threeAddressCode);
        }
    }
    
    return NULL;
}

void showThreeAddressCode(ThreeAddressCode threeAddressCode) {
    TACNode* node = threeAddressCode.head;
    while(node) {
    
        Flag flag = node->instruction.op;
        
        if(isABinaryOperator(flag)) {
            printf("%s %s %s %s\n", flagToString(flag), node->instruction.fstOperand->name, node->instruction.sndOperand->name, node->instruction.dest->name);
        }
        
        if(flag == flag_ASSIGNMENT) {
            printf("%s %s NULL %s\n", flagToString(flag), node->instruction.fstOperand->name, node->instruction.dest->name);
        }
        
        if(flag == flag_RETURN) {
            printf("%s NULL NULL %s\n", flagToString(flag), node->instruction.dest->name);
        }
    
        node = node->next;
    }
}
