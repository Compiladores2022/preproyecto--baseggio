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
        
        Flag flag = getFlag(*(node->symbol));
        if(isABinaryOperator(flag)) {
            Symbol* fstOperand = generateIntermediateCode(node->lSide, threeAddressCode, offset);
            Symbol* sndOperand = generateIntermediateCode(node->rSide, threeAddressCode, offset);
            Instruction instruction = constructInstruction(flag, fstOperand, sndOperand, node->symbol);
            addInstruction(threeAddressCode, instruction);
           
            threeAddressCode->numberOfTemporaries++;
            setOffset(node->symbol, *offset);
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
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s %s %s %s\n", flagToString(op), oprnd1, oprnd2, dest);
  }

  if(op == flag_ASSIGNMENT) {
    char* expr = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* dest = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s %s - %s\n", flagToString(op), expr, dest);
  }

  if(op == flag_RETURN) {
    char* expr = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s - - %s\n", flagToString(op), expr);
  }
}

void showThreeAddressCode(ThreeAddressCode threeAddressCode) {
    showQueue(threeAddressCode.queue, printInstruction);
}

void translateBinaryOperation(FILE* fp, char* operation, Symbol* fstOperand, Symbol* sndOperand, Symbol* dest) {
    int cond1 = getFlag(*fstOperand) == flag_IDENTIFIER || isAnArithmeticBinaryOperator(getFlag(*fstOperand));
    int cond2 = getFlag(*sndOperand) == flag_IDENTIFIER || isAnArithmeticBinaryOperator(getFlag(*sndOperand));
    if(cond1 && cond2) {
        fprintf(fp, "\n\tmovq -%d(%%rbp), %%r10", getOffset(*fstOperand));
	    fprintf(fp, "\n\t%s -%d(%%rbp), %%r10", operation, getOffset(*sndOperand));
    } else if (cond1) {
        fprintf(fp, "\n\tmovq -%d(%%rbp), %%r10", getOffset(*fstOperand));
	    fprintf(fp, "\n\t%s $%d, %%r10", operation, getValue(*sndOperand));
    } else if (cond2) {
        fprintf(fp, "\n\tmovq $%d, %%r10", getValue(*fstOperand));
	    fprintf(fp, "\n\t%s -%d(%%rbp), %%r10", operation, getOffset(*sndOperand));
    } else {
        fprintf(fp, "\n\tmovq $%d, %%r10", getValue(*fstOperand));
	    fprintf(fp, "\n\t%s $%d, %%r10", operation, getValue(*sndOperand));
    }

    fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*dest));
}

char* translateOperand(Symbol* symbol) {
    char* res = (char*) malloc(sizeof(char));
    if(isValue(getFlag(*symbol))) {
        sprintf(res, "$%d", getValue(*symbol));
    } else {
        sprintf(res, "-%d(%%rbp)", getOffset(*symbol));
    }

    return res;
}

void translateOR(FILE* fp, Instruction i, int* numberOfLabel) {
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(i.fstOperand));
    fprintf(fp, "\n\tmovq $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(i.sndOperand));
    fprintf(fp, "\n\tmovq $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(i.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(i.dest)));
    fprintf(fp, "\n.L%d:", *numberOfLabel + 1);

    *numberOfLabel += 2;
}

void translateAND(FILE* fp, Instruction i, int* numberOfLabel) {
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(i.fstOperand));
    fprintf(fp, "\n\tmovq $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(i.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(i.sndOperand));
    fprintf(fp, "\n\tmovq $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(i.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);
    fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(i.dest)));
    fprintf(fp, "\n\n.L%d:", *numberOfLabel + 2);

    *numberOfLabel += 3;
}

void translate(FILE* fp, Instruction i, int* numberOfLabel) {
    Flag op = i.op;
    switch (op) {
        case flag_ADDITION:
		translateBinaryOperation(fp, "add", i.fstOperand, i.sndOperand, i.dest);
		break;
	case flag_MULTIPLICATION:
		translateBinaryOperation(fp, "imul", i.fstOperand, i.sndOperand, i.dest);
		break;
	case flag_OR:
		translateOR(fp, i, numberOfLabel);
		break;
	case flag_AND:
		translateAND(fp, i, numberOfLabel);
		break;
	case flag_RETURN:
		fprintf(fp, "\n\tmov %s, %%edi", translateOperand(i.dest));
		fprintf(fp, "\n\tcall print");
		break;
	case flag_ASSIGNMENT:
		if(getFlag(*(i.fstOperand)) == flag_IDENTIFIER ||
	        isABinaryOperator(getFlag(*(i.fstOperand)))) {
		    fprintf(fp, "\n\tmovq -%d(%%rbp), %%r10", getOffset(*(i.fstOperand)));
		    fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*(i.dest)));
		} else {
		    fprintf(fp, "\n\tmovq $%d, -%d(%%rbp)", getValue(*(i.fstOperand)), i.dest->offset);
		}
		break;
	default:
		break;
    }
}

int memoryNeeded(int numberOfLocals, int numberOfTemporaries) {
    int memoryNeeded = 8 * (numberOfLocals + numberOfTemporaries);
    return memoryNeeded + (memoryNeeded % 16);
}

void generateAssembler(ThreeAddressCode threeAddressCode, SymbolTable symbolTable) {
   FILE* fp = fopen("./output/a.s", "w");
   int numberOfLabel = 1;
   if(fp == NULL) {
       printf("File can't be opened\n");
       exit(1);
   }

   fprintf(fp, "\t.globl main");
   fprintf(fp, "\nmain:");
   fprintf(fp, "\n\tenter $%d, $0", memoryNeeded(numberOfLocals(symbolTable), threeAddressCode.numberOfTemporaries));

   while(!isEmpty(threeAddressCode.queue)) {
       Instruction instruction = *(Instruction*) head(threeAddressCode.queue);
       translate(fp, instruction, &numberOfLabel);
       dequeue(&(threeAddressCode.queue));
   }

   fprintf(fp, "\n\tmovq $0, %%rax");
   fprintf(fp, "\n\tleave");
   fprintf(fp, "\n\tret\n");
}
