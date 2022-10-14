#include "assemblerGenerator.h"
#include <stdio.h>
#include <stdlib.h>

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
	fprintf(fp, "\n\tadd  %s, %%r10", translateOperand(*instruction.sndOperand));
	fprintf(fp, "\n\tmovq %%r10, -%d(%%rbp)", getOffset(*instruction.dest));
}

void translateSUBSTRACTION(FILE* fp, Instruction instruction) {

}

void translateMULTIPLICATION(FILE* fp, Instruction instruction) {

}

void translateDIVISION(FILE* fp, Instruction instruction) {

}

void translateMOD(FILE* fp, Instruction instruction) {

}

void translateOR(FILE* fp, Instruction instruction) {

}

void translateAND(FILE* fp, Instruction instruction) {

}

void translateLT(FILE* fp, Instruction instruction) {

}

void translateGT(FILE* fp, Instruction instruction) {

}

void translateEQ(FILE* fp, Instruction instruction) {

}

void translateFALSE_CONDITIONAL(FILE* fp, Instruction instruction) {

}

void translateJMP(FILE* fp, Instruction instruction) {

}

void translateLABEL(FILE* fp, Instruction instruction) {

}

void translateSTART_OF_FUNCTION(FILE* fp, Instruction instruction) {

}

void translateEND_OF_FUNCTION(FILE* fp, Instruction instruction) {

}

void translateRETURN(FILE* fp, Instruction instruction) {

}

void translateASSIGNMENT(FILE* fp, Instruction instruction) {

}

void translateMINUS(FILE* fp, Instruction instruction) {

}

void translateNEG(FILE* fp, Instruction instruction) {

}

void translateCALL(FILE* fp, Instruction instruction) {

}

void translateLOAD(FILE* fp, Instruction instruction) {

}

void translate(FILE* fp, Instruction instruction) {
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
			translateOR(fp, instruction);
			break;
		case code_AND:
			translateAND(fp, instruction);
			break;
		case code_LT:
			translateLT(fp, instruction);
			break;
		case code_GT:
			translateGT(fp, instruction);
			break;
		case code_EQT:
			translateEQ(fp, instruction);
			break;
		case code_FALSE_CONDITIONAL:
			translateFALSE_CONDITIONAL(fp, instruction);
			break;
		case code_JMP:
			translateJMP(fp, instruction);
			break;
		case code_LABEL:
			translateLABEL(fp, instruction);
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
			translateCALL(fp, instruction);
			break;
		case code_LOAD:
			translateLOAD(fp, instruction);
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

	while(!isEmpty(threeAddressCode.queue)) {
		Instruction instruction = *(Instruction*) head(threeAddressCode.queue); // getHead(threeAddressCode);
		translate(fp, instruction);
		dequeue(&(threeAddressCode.queue)); // removeHead(&threeAddressCode);
	}
}
