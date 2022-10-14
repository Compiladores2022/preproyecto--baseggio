#include "assemblerGenerator.h"
#include <stdio.h>
#include <stdlib.h>

void translate(FILE* fp, Instruction instruction) {
	Code iCode = instruction.code; //getICode(instruction);
	switch (iCode) {
		case code_ADDITION:
			break;
		case code_SUBSTRACTION:
			break;
		case code_MULTIPLICATION:
			break;
		case code_DIVISION:
			break;
		case code_MOD:
			break;
		case code_OR:
			break;
		case code_AND:
			break;
		case code_LT:
			break;
		case code_GT:
			break;
		case code_EQT:
			break;
		case code_FALSE_CONDITIONAL:
			break;
		case code_JMP:
			break;
		case code_LABEL:
			break;
		case code_LABEL_START_OF_FUNCTION:
			break;
		case code_LABEL_END_OF_FUNCTION:
			break;
		case code_RETURN:
			break;
		case code_ASSIGNMENT:
			break;
		case code_MINUS:
			break;
		case code_NEG:
			break;
		case code_CALL:
			break;
		case code_LOAD:
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
