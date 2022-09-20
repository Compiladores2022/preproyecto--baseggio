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
           
            threeAddressCode->ctr++;

            node->symbol->offset = *offset;
            *offset += 8;
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

void translate(FILE* fp, Instruction i) {
    Flag op = i.op;
    switch (op) {
        case flag_ADDITION:
		if(i.fstOperand->flag == flag_IDENTIFIER && i.sndOperand->flag == flag_IDENTIFIER) {
		    fprintf(fp, "\n\tmov -%d(%%rbp), %%r10", i.sndOperand->offset);
		    fprintf(fp, "\n\tadd -%d(%%rbp), %%r10", i.fstOperand->offset);
		    fprintf(fp, "\n\tmov %%r10, -%d(%%rbp)", i.dest->offset);
		}

		if(i.fstOperand->flag == flag_IDENTIFIER) {
		    fprintf(fp, "\n\tmov $%d, %%r10", i.sndOperand->value);
		    fprintf(fp, "\n\tadd -%d(%%rbp), %%r10", i.fstOperand->offset);
		    fprintf(fp, "\n\tmov %%r10, -%d(%%rbp)", i.dest->offset);
		}

		if(i.sndOperand->flag == flag_IDENTIFIER) {
		    fprintf(fp, "\n\tmov -%d(%%rbp), %%r10", i.sndOperand->offset);
		    fprintf(fp, "\n\tadd $%d, %%r10", i.fstOperand->value);
		    fprintf(fp, "\n\tmov %%r10, -%d(%%rbp)", i.dest->offset);
		}

		if(i.fstOperand->flag != flag_IDENTIFIER && i.sndOperand != flag_IDENTIFIER) {
		    fprintf(fp, "\n\tmov $%d, %%r10", i.fstOperand->value);
		    fprintf(fp, "\n\tadd $%d, %%r10", i.sndOperand->value);
		    fprintf(fp, "\n\tmov %%r10, -%d(%%rbp)", i.dest->offset);
		}

		break;
	case flag_MULTIPLICATION:
		break;
	case flag_OR:
		break;
	case flag_AND:
		break;
	case flag_RETURN:
		break;
	case flag_ASSIGNMENT:
		if(i.fstOperand->flag == flag_IDENTIFIER ||
	          isABinaryOperator(i.fstOperand->flag)) {
		    fprintf(fp, "\n\tmov -%d(%%rbp), -%d(%%rbp)", i.fstOperand->offset, i.dest->offset);
		} else {
		    fprintf(fp, "\n\tmov $%d, -%d(%%rbp)", i.fstOperand->value, i.dest->offset);
		}
		break;
	default:
		break;
    }
}

void generateAssembler(ThreeAddressCode threeAddressCode) {
   FILE* fp = fopen("./output.s", "w");
   if(fp == NULL) {
       printf("File can't be opened\n");
       exit(1);
   }

   fprintf(fp, "\t.globl main");
   fprintf(fp, "\nmain:");
   fprintf(fp, "\n\tenter $(8 * %d), $0", threeAddressCode.ctr);

   while(!isEmpty(threeAddressCode.queue)) {
       Instruction instruction = *(Instruction*) head(threeAddressCode.queue);
       translate(fp, instruction);
       dequeue(&(threeAddressCode.queue));
   }

   fprintf(fp, "\n\tmov $0, %%rax");
   fprintf(fp, "\n\tleave");
   fprintf(fp, "\n\tret");
}
