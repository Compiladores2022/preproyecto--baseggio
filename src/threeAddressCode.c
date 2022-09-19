#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threeAddressCode.h"

Instruction constructInstruction(Flag op, Symbol* fstOperand, Symbol* sndOperand, Symbol* dest) {
    Instruction i;
    i.op = op;
    i.fstOperand = fstOperand;
    i.sndOperand = sndOperand;
    i.dest = dest;
    return i;
}

void addInstruction(ThreeAddressCode* threeAddressCode, Instruction instruction) {
    void* data = malloc(sizeof(Instruction));
    (*(Instruction*) data) = instruction;
    enqueue(&threeAddressCode->queue, data, sizeof(instruction));
}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset) {
    if(node) {
        if(isLeave(node)) { 
            return node->symbol; 
        }
        
        Flag flag = node->symbol->flag;
        if(isABinaryOperator(flag)) {
            Symbol* fstOperand = generateIntermediateCode(node->lSide, threeAddressCode, offset);
            Symbol* sndOperand = generateIntermediateCode(node->rSide, threeAddressCode, offset);
            Instruction instruction = constructInstruction(flag, fstOperand, sndOperand, node->symbol);
            addInstruction(threeAddressCode, instruction);
            
            node->symbol->offset = *offset;
            printf("%X\n", *offset);
            *offset += 0x8;
            return node->symbol;
        }
        
        if(flag == flag_ASSIGNMENT) {
            Symbol* expr = generateIntermediateCode(node->rSide, threeAddressCode, offset);
            Instruction instruction = constructInstruction(flag, expr, NULL, node->lSide->symbol);
            addInstruction(threeAddressCode, instruction);
        }
        
        if(flag == flag_RETURN) {
            Symbol* expr = generateIntermediateCode(node->lSide, threeAddressCode, offset);
            Instruction instruction = constructInstruction(flag, NULL, NULL, expr);
            addInstruction(threeAddressCode, instruction);
        }
        
        if(flag == flag_SEMICOLON) {
            generateIntermediateCode(node->lSide, threeAddressCode, offset);
            generateIntermediateCode(node->rSide, threeAddressCode, offset);
        }
    }
    
    return NULL;
}

void printInstruction(void* i) {
  Instruction instruction = *(Instruction*) i;
  Flag op = instruction.op;
  if(isABinaryOperator(op)) {
    char* oprnd1 = instruction.fstOperand->name;
    char* oprnd2 = instruction.sndOperand->name;
    char* dest   = instruction.dest->name;
    printf("%s %s %s %s\n", flagToString(op), oprnd1, oprnd2, dest);
  }

  if(op == flag_ASSIGNMENT) {
    char* expr = instruction.fstOperand->name;
    char* dest = instruction.dest->name;
    printf("%s %s - %s\n", flagToString(op), expr, dest);
  }

  if(op == flag_RETURN) {
    char* expr = instruction.dest->name;
    printf("%s - - %s\n", flagToString(op), expr);
  }
}

void showThreeAddressCode(ThreeAddressCode threeAddressCode) {
    showQueue(threeAddressCode.queue, printInstruction);
}
