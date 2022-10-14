#include "assemblerGenerator.h"
#include <stdio.h>
#include <stdlib.h>

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
