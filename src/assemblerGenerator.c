#include "assemblerGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* translateOperand(Symbol operand) {
	char* result = (char*) malloc(16 * sizeof(char));
	
	if(isFunction(operand)) {
		sprintf(result, "%%rax");
	} else if(isAConstant(getFlag(operand))) {
		sprintf(result, "$%d", getValue(operand));
	} else {
		if(isGlobal(operand)) {
			sprintf(result, "%s(%%rip)", getName(operand));		
		} else {
			sprintf(result, "-%d(%%rbp)", getOffset(operand));
		}
	}

	return result;
}

void translateADDITION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*instruction.fstOperand));
	fprintf(fp, "\n\taddq %s, %%r10", translateOperand(*instruction.sndOperand));
	fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*instruction.dest));
}

void translateSUBSTRACTION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*instruction.fstOperand));
	fprintf(fp, "\n\tsubq %s, %%r10", translateOperand(*instruction.sndOperand));
	fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*instruction.dest));
}

void translateMULTIPLICATION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*instruction.fstOperand));
	fprintf(fp, "\n\timulq %s, %%r10", translateOperand(*instruction.sndOperand));
	fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*instruction.dest));
}

void translateDIVISION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq  $0, %%rdx");
	fprintf(fp, "\n\tmovq  %s, %%r10", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tmovq  %s, %%rax", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tidivq %%r10");
	fprintf(fp, "\n\tmovq  %%rax, -%d(%%rbp)", getOffset(*(instruction.dest)));
}

void translateMOD(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq  $0, %%rdx");
	fprintf(fp, "\n\tmovq  %s, %%r10", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tmovq  %s, %%rax", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tidivq %%r10");
	fprintf(fp, "\n\tmovq  %%rdx, -%d(%%rbp)", getOffset(*(instruction.dest)));
}

void translateOR(FILE* fp, Instruction instruction, int* numberOfLabel) {
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
    fprintf(fp, "\n\tmovq $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.sndOperand)));
    fprintf(fp, "\n\tmovq $1, %%r11");
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
    fprintf(fp, "\n.L%d:", *numberOfLabel + 1);

    *numberOfLabel += 2;
}

void translateAND(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
    fprintf(fp, "\n\tmovq $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n.L%d:", *numberOfLabel);
    fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.sndOperand)));
    fprintf(fp, "\n\tmovq $%d, %%r11", 1);
    fprintf(fp, "\n\tcmp %%r10, %%r11");
    fprintf(fp, "\n\tje .L%d", *numberOfLabel + 1);
    fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
    fprintf(fp, "\n\tjmp .L%d", *numberOfLabel + 2);
    fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);
    fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
    fprintf(fp, "\n\n.L%d:", *numberOfLabel + 2);

    *numberOfLabel += 3;
}

void translateLT(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq %s, %%r11", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tcmp  %%r11, %%r10");
	fprintf(fp, "\n\tjl  .L%d", *numberOfLabel);
	fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\tjmp  .L%d", *numberOfLabel + 1);
	fprintf(fp, "\n\n.L%d:", *numberOfLabel);
	fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);

	*numberOfLabel += 2;
}

void translateGT(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq %s, %%r11", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tcmp  %%r11, %%r10");
	fprintf(fp, "\n\tjg  .L%d", *numberOfLabel);
	fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\tjmp  .L%d", *numberOfLabel + 1);
	fprintf(fp, "\n\n.L%d:", *numberOfLabel);
	fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);

	*numberOfLabel += 2;
}

void translateEQ(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq %s, %%r11", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tcmp  %%r11, %%r10");
	fprintf(fp, "\n\tje  .L%d", *numberOfLabel);
	fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\tjmp  .L%d", *numberOfLabel + 1);
	fprintf(fp, "\n\n.L%d:", *numberOfLabel);
	fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);

	*numberOfLabel += 2;
}

void translateFALSE_CONDITIONAL(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq $1, %%r11");
	fprintf(fp, "\n\tcmp  %%r10, %%r11");
	fprintf(fp, "\n\tjne  .%s", getName(*(instruction.dest)));
}

void translateJMP(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tjmp .%s", getName(*(instruction.dest)));
}

void translateLABEL(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\n.%s:", getName(*(instruction.dest)));
	*numberOfLabel += 1;
}

void translateSTART_OF_FUNCTION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\t.text");
	fprintf(fp, "\n\t.globl %s", getName(*(instruction.fstOperand)));
	fprintf(fp, "\n%s:", getName(*(instruction.fstOperand)));
	
	int m = getOffset(*(instruction.fstOperand)) + (getOffset(*(instruction.fstOperand)) % 16);
	
	fprintf(fp, "\n\tenter $(%d), $0", m);

	int numberOfParameter = 1;
	Symbol* symbol = getParams(*(instruction.fstOperand));
	while(symbol) {
		switch (numberOfParameter) {
		case 1:
			fprintf(fp, "\n\tmov %%rdi, -%d(%%rbp)", getOffset(*symbol));
			break;
		case 2:
			fprintf(fp, "\n\tmov %%rsi, -%d(%%rbp)", getOffset(*symbol));
			break;
		case 3:
			fprintf(fp, "\n\tmov %%rdx, -%d(%%rbp)", getOffset(*symbol));
			break;
		case 4:
			fprintf(fp, "\n\tmov %%rcx, -%d(%%rbp)", getOffset(*symbol));
			break;
		case 5:
			fprintf(fp, "\n\tmov %%r8, -%d(%%rbp)", getOffset(*symbol));
			break;
		case 6:
			fprintf(fp, "\n\tmov %%r9, -%d(%%rbp)", getOffset(*symbol));
			break;
		default:
			break;
		}
		numberOfParameter++;
		symbol = getParams(*symbol);
	}
}

void translateEND_OF_FUNCTION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tleave");
	fprintf(fp, "\n\tret");
}

void translateRETURN(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%rax", translateOperand(*(instruction.dest)));
}

void translateASSIGNMENT(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq %%r10, %s", translateOperand(*(instruction.dest)));
}

void translateNEG(FILE* fp, Instruction instruction, int* numberOfLabel) {
	fprintf(fp, "\n\tmovq $1, %%r10");
	fprintf(fp, "\n\tcmp  %s, %%r10", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tje  .L%d", *numberOfLabel);
	fprintf(fp, "\n\tmovq $1, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\tjmp  .L%d", *numberOfLabel + 1);
	fprintf(fp, "\n\n.L%d:", *numberOfLabel);
	fprintf(fp, "\n\tmovq $0, -%d(%%rbp)", getOffset(*(instruction.dest)));
	fprintf(fp, "\n\n.L%d:", *numberOfLabel + 1);
	
	*numberOfLabel += 2;
}

void translateCALL(FILE* fp, Instruction instruction, int* numberOfParameter) {
	fprintf(fp, "\n\tcall %s", getName(*(instruction.dest)));
	if(getType(*(instruction.dest)) == TYPE_INT || getType(*(instruction.dest)) == TYPE_BOOL) {
		fprintf(fp, "\n\tmovq %%rax, -%d(%%rbp)", getOffset(*(instruction.fstOperand)));	
	}
	*numberOfParameter = 1;
}

void translateLOAD(FILE* fp, Instruction instruction, int* numberOfParameter) {
	char* from = (char*) malloc(16 * sizeof(char));
	sprintf(from, "%s", translateOperand(*(instruction.dest)));

	switch (*numberOfParameter) {
		case 1:
			fprintf(fp, "\n\tmov %s, %%rdi", from);
			break;
		case 2:
			fprintf(fp, "\n\tmov %s, %%rsi", from);
			break;
		case 3:
			fprintf(fp, "\n\tmov %s, %%rdx", from);
			break;
		case 4:
			fprintf(fp, "\n\tmov %s, %%rcx", from);
			break;
		case 5:
			fprintf(fp, "\n\tmov %s, %%r8", from);
			break;
		case 6:
			fprintf(fp, "\n\tmov %s, %%r9", from);
			break;
		default:
			break;
	}
	*numberOfParameter += 1;

}

void translateGLOBAL_VAR_DECL(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\t.text");
	fprintf(fp, "\n\t.globl %s", getName(*(instruction.dest)));
	fprintf(fp, "\n\t.data");
	fprintf(fp, "\n%s:", getName(*(instruction.dest)));
	fprintf(fp, "\n\t.long %d", getValue(*(instruction.fstOperand)));
}

void translate(FILE* fp, Instruction instruction, int* numberOfLabel, int* numberOfParameter) {
	Code iCode = instruction.code; //getICode(instruction);
	switch (iCode) {
		case code_ADDITION:
			translateADDITION(fp, instruction);
			break;
		case code_SUBSTRACTION:
			translateSUBSTRACTION(fp, instruction);
			break;
		case code_MULTIPLICATION:
			translateMULTIPLICATION(fp, instruction);
			break;
		case code_DIVISION:
			translateDIVISION(fp, instruction);
			break;
		case code_MOD:
			translateMOD(fp, instruction);
			break;
		case code_OR:
			translateOR(fp, instruction, numberOfLabel);
			break;
		case code_AND:
			translateAND(fp, instruction, numberOfLabel);
			break;
		case code_LT:
			translateLT(fp, instruction, numberOfLabel);
			break;
		case code_GT:
			translateGT(fp, instruction, numberOfLabel);
			break;
		case code_EQT:
			translateEQ(fp, instruction, numberOfLabel);
			break;
		case code_FALSE_CONDITIONAL:
			translateFALSE_CONDITIONAL(fp, instruction, numberOfLabel);
			break;
		case code_JMP:
			translateJMP(fp, instruction, numberOfLabel);
			break;
		case code_LABEL:
			translateLABEL(fp, instruction, numberOfLabel);
			break;
		case code_LABEL_START_OF_FUNCTION:
			translateSTART_OF_FUNCTION(fp, instruction);
			break;
		case code_LABEL_END_OF_FUNCTION:
			translateEND_OF_FUNCTION(fp, instruction);
			break;
		case code_RETURN:
			translateRETURN(fp, instruction);
			break;
		case code_ASSIGNMENT:
			translateASSIGNMENT(fp, instruction);
			break;
		case code_MINUS:
			translateSUBSTRACTION(fp, instruction);
			break;
		case code_NEG:
			translateNEG(fp, instruction, numberOfLabel);
			break;
		case code_CALL:
			translateCALL(fp, instruction, numberOfParameter);
			break;
		case code_LOAD:
			translateLOAD(fp, instruction, numberOfParameter);
			break;
		case code_GLOBAL_VAR_DECL:
			translateGLOBAL_VAR_DECL(fp, instruction);
			break;
		default:
			printf("Instruction not recognized\n");
			exit(EXIT_FAILURE);
			break;
	}
}

void generateAssembler(ThreeAddressCode threeAddressCode) {

	char* target = (char*) malloc(100 * sizeof(char));
	sprintf(target, "./output/%s.s", filename);
	FILE* fp = fopen(target, "w");
	if(fp == NULL) {
		printf("File can't be opened\n");
		exit(EXIT_FAILURE);
	}

	int numberOfLabel     = 0;
	int numberOfParameter = 1;

	while(!isEmpty(threeAddressCode.list)) {
		Instruction instruction = *(Instruction*) head(threeAddressCode.list); // getHead(threeAddressCode);
		translate(fp, instruction, &numberOfLabel, &numberOfParameter);
		removeFirst(&(threeAddressCode.list)); // removeHead(&threeAddressCode);
	}
	
	fprintf(fp, "\n");
	
	free(target);
}
