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

void translateBinaryOperation(FILE* fp, char* operation, Symbol* fstOperand, Symbol* sndOperand, Symbol* dest) {
    int cond1 = fstOperand->flag == flag_IDENTIFIER || isAnArithmeticBinaryOperator(fstOperand->flag);
    int cond2 = sndOperand->flag == flag_IDENTIFIER || isAnArithmeticBinaryOperator(sndOperand->flag);
    if(cond1 && cond2) {
        fprintf(fp, "\n\tmov -%d(%%rbp), %%r10", fstOperand->offset);
	fprintf(fp, "\n\t%s -%d(%%rbp), %%r10", operation, sndOperand->offset);
    } else if (cond1) {
        fprintf(fp, "\n\tmov -%d(%%rbp), %%r10", fstOperand->offset);
	fprintf(fp, "\n\t%s $%d, %%r10", operation, sndOperand->value);
    } else if (cond2) {
        fprintf(fp, "\n\tmov $%d, %%r10", fstOperand->value);
	fprintf(fp, "\n\t%s -%d(%%rbp), %%r10", operation, sndOperand->offset);
    } else {
        fprintf(fp, "\n\tmov $%d, %%r10", fstOperand->value);
	fprintf(fp, "\n\t%s $%d, %%r10", operation, sndOperand->value);
    }

    fprintf(fp, "\n\tmov %%r10, -%d(%%rbp)", dest->offset);
}

char* translateOperand(Symbol* symbol) {
    char* res = (char*) malloc(sizeof(char));
    if(isValue(symbol->flag)) {
        sprintf(res, "$%d", symbol->value);
    } else {
        sprintf(res, "-%d(%%rbp)", symbol->offset);
    }

    return res;
}

void translateOR(FILE* fp, Instruction i, int* numberOfLabel) {
    fprintf(fp, "\n\tmov %s, %%r10", translateOperand(i.fstOperand));
    fprintf(fp, "\n\tmov $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmov %s, %%r10", translateOperand(i.sndOperand));
    fprintf(fp, "\n\tmov $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmov $0, -%d(%%rbp)", i.dest->offset);
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n\t.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmov $1, -%d(%%rbp)", i.dest->offset);
    fprintf(fp, "\n\t.L%d:", *numberOfLabel + 1);

    *numberOfLabel += 2;
}

void translateAND(FILE* fp, Instruction i, int* numberOfLabel) {
    fprintf(fp, "\n\tmov %s, %%r10", translateOperand(i.fstOperand));
    fprintf(fp, "\n\tmov $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmov $0, -%d(%%rbp)", i.dest->offset);
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n\t.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmov %s, %%r10", translateOperand(i.sndOperand));
    fprintf(fp, "\n\tmov $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n\tmov $0, -%d(%%rbp)", i.dest->offset);
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n\t.L%d:", *numberOfLabel + 1);
    fprintf(fp, "\n\tmov $1, -%d(%%rbp)", i.dest->offset);
    fprintf(fp, "\n\n\t.L%d:", *numberOfLabel + 2);

    *numberOfLabel += 3;
}

void translate(FILE* fp, Instruction i, int* numberOfLabel) {
    Flag op = i.op;
    switch (op) {
        case flag_ADDITION:
		translateBinaryOperation(fp, "add", i.fstOperand, i.sndOperand, i.dest);
		break;
	case flag_MULTIPLICATION:
		translateBinaryOperation(fp, "imult", i.fstOperand, i.sndOperand, i.dest);
		break;
	case flag_OR:
		translateOR(fp, i, numberOfLabel);
		break;
	case flag_AND:
		translateAND(fp, i, numberOfLabel);
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
   int numberOfLabel = 1;
   if(fp == NULL) {
       printf("File can't be opened\n");
       exit(1);
   }

   fprintf(fp, "\t.globl main");
   fprintf(fp, "\nmain:");
   fprintf(fp, "\n\tenter $(8 * %d), $0", threeAddressCode.ctr);

   while(!isEmpty(threeAddressCode.queue)) {
       Instruction instruction = *(Instruction*) head(threeAddressCode.queue);
       translate(fp, instruction, &numberOfLabel);
       dequeue(&(threeAddressCode.queue));
   }

   fprintf(fp, "\n\tmov $0, %%rax");
   fprintf(fp, "\n\tleave");
   fprintf(fp, "\n\tret\n");
}
