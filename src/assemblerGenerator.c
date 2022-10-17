#include "assemblerGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* translateOperand(Symbol operand) {
	char* result = (char*) malloc(16 * sizeof(char));
	if(isAConstant(getFlag(operand))) {
		sprintf(result, "$%d", getValue(operand));
	} else {
		sprintf(result, "-%d(%%rbp)", getOffset(operand));
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
	fprintf(fp, "\n\tmovq  %s, %%rax", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq  %s, %%r10", translateOperand(*(instruction.sndOperand)));
	fprintf(fp, "\n\tidivq %%r10");
	fprintf(fp, "\n\tmovq  %%rax, -%d(%%rbp)", getOffset(*(instruction.dest)));
}

void translateMOD(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq  $0, %%rdx");
	fprintf(fp, "\n\tmovq  %s, %%rax", translateOperand(*(instruction.fstOperand)));
	fprintf(fp, "\n\tmovq  %s, %%r10", translateOperand(*(instruction.sndOperand)));
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
	if( strcmp(getName(*(instruction.fstOperand)), "main") == 0 ) {
		fprintf(fp, "\n\n\t.globl main");
	}

	fprintf(fp, "\n%s:", getName(*(instruction.fstOperand)));
	fprintf(fp, "\n\tenter $(%d), $0", getOffset(*(instruction.fstOperand)));
}

void translateEND_OF_FUNCTION(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tleave");
	fprintf(fp, "\n\tret");
}

void translateRETURN(FILE* fp, Instruction instruction) {
	fprintf(fp, "\n\tmovq %s, %%rax", translateOperand(*(instruction.dest)));
}

void translateASSIGNMENT(FILE* fp, Instruction instruction) {
	if(isAConstant(getFlag(*(instruction.fstOperand)))) {
		fprintf(fp, "\n\tmovq $%d, -%d(%%rbp)", getValue(*(instruction.fstOperand)), getOffset(*(instruction.dest)));
	} else {
		fprintf(fp, "\n\tmovq -%d(%%rbp), %%r10", getOffset(*(instruction.fstOperand)));
		fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*(instruction.dest)));
	}
}

void translateMINUS(FILE* fp, Instruction instruction) {

}

void translateNEG(FILE* fp, Instruction instruction) {

}

void translateCALL(FILE* fp, Instruction instruction, int* numberOfParameter) {
	fprintf(fp, "\n\tcall %s", getName(*(instruction.dest)));
	*numberOfParameter = 1;
}

void translateLOAD(FILE* fp, Instruction instruction, int* numberOfParameter) {
	//fprintf(fp, "\n\tmov %s, %%edi", translateOperand(*(instruction.dest)));
	switch (*numberOfParameter) {
		case 1:
			fprintf(fp, "\n\tmov %s, %%rdi", translateOperand(*(instruction.dest)));
			break;
		case 2:
			fprintf(fp, "\n\tmov %s, %%rsi", translateOperand(*(instruction.dest)));
			break;
		case 3:
			fprintf(fp, "\n\tmov %s, %%rdx", translateOperand(*(instruction.dest)));
			break;
		case 4:
			fprintf(fp, "\n\tmov %s, %%rcx", translateOperand(*(instruction.dest)));
			break;
		case 5:
			fprintf(fp, "\n\tmov %s, %%r8", translateOperand(*(instruction.dest)));
			break;
		case 6:
			fprintf(fp, "\n\tmov %s, %%r9", translateOperand(*(instruction.dest)));
			break;
		default:
			break;
	}
	*numberOfParameter += 1;

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
			translateMINUS(fp, instruction);
			break;
		case code_NEG:
			translateNEG(fp, instruction);
			break;
		case code_CALL:
			translateCALL(fp, instruction, numberOfParameter);
			break;
		case code_LOAD:
			translateLOAD(fp, instruction, numberOfParameter);
			break;
		default:
			printf("Instruction not recognized\n");
			exit(EXIT_FAILURE);
			break;
	}
}

void generateAssembler(ThreeAddressCode threeAddressCode) {
	FILE* fp = fopen("./output/a.s", "w");
	if(fp == NULL) {
		printf("File can't be opened\n");
		exit(EXIT_FAILURE);
	}

	int numberOfLabel     = 0;
	int numberOfParameter = 1;

	while(!isEmpty(threeAddressCode.queue)) {
		Instruction instruction = *(Instruction*) head(threeAddressCode.queue); // getHead(threeAddressCode);
		translate(fp, instruction, &numberOfLabel, &numberOfParameter);
		dequeue(&(threeAddressCode.queue)); // removeHead(&threeAddressCode);
	}
}
