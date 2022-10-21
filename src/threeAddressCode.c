#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threeAddressCode.h"

Instruction constructInstruction(Code code, Symbol* fstOperand, Symbol* sndOperand, Symbol* dest) {
    Instruction i;
    i.code = code;
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

void loadParams(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset, int* numberOfLabel) {
    if(node) {
    	Instruction load = constructInstruction(code_LOAD, NULL, NULL, generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel));
    	addInstruction(threeAddressCode, load);
    	loadParams(getRSide(node), threeAddressCode, offset, numberOfLabel);
    }
}

int params(Symbol* symbol) {
	if(symbol) {
		return 1 + params(symbol->params);
	}

	return 0;
}

void assignOffset(Symbol* symbol, int* offset) {
	setOffset(symbol, *offset);
	*offset += 8;
}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset, int* numberOfLabel) {
	if(node) {
		Flag flag = getFlag(*(node->symbol));
		Symbol* fstOperand;
		Symbol* sndOperand;
		Symbol* expression;
		Symbol* else_label;
		Symbol* while_label;
		Instruction jmp;
		Symbol* end_label;
		Instruction instruction;
		Instruction label;
		Instruction call;
		Symbol* start_of_function;
		Symbol* end_of_function;
		Symbol* zero;
        char name[16];
		switch (flag) {
			case flag_VALUE_INT:
			    return getSymbol(node);
                break;
			case flag_VALUE_BOOL:
                setName(getSymbol(node), (getValue(*getSymbol(node)) == 1? "true" : "false"));
			    return getSymbol(node);
                break;
			case flag_IDENTIFIER:
			    return getSymbol(node);
                break;
			case flag_PARAM:
			    return getSymbol(node);
                break;
			case flag_ADDITION:
			    fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_ADDITION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_SUBSTRACTION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
				instruction = constructInstruction(code_SUBSTRACTION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_MULTIPLICATION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_MULTIPLICATION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_DIVISION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_DIVISION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_MOD:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_MOD, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

            	sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_OR:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_OR, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_AND:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_AND, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_RETURN:
			    expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_RETURN, NULL, NULL, expression);
			    addInstruction(threeAddressCode, instruction);
            	break;
			case flag_ASSIGNMENT:
		        expression  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
            	instruction = constructInstruction(code_ASSIGNMENT, expression, NULL, getSymbol(getLSide(node)));
			    addInstruction(threeAddressCode, instruction);
				assignOffset(getSymbol(getLSide(node)), offset);
			    break;
			case flag_SEMICOLON:
				generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
				break;
			case flag_LT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_LT, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_GT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_GT, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_EQT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_EQT, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_MINUS:
			
			zero = constructPtrToEmptySymbol();
			setName(zero, "0");
			setValue(zero, 0);
			setFlag(zero, flag_VALUE_INT);
			
			expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			instruction = constructInstruction(code_MINUS, zero, expression, getSymbol(node));
			addInstruction(threeAddressCode, instruction);
			sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                	setName(getSymbol(node), name);
                	assignOffset(getSymbol(node), offset);
			return getSymbol(node);
                break;
			case flag_NEG:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
			    instruction = constructInstruction(code_NEG, expression, NULL, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

				sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

				assignOffset(getSymbol(node), offset);
			    return getSymbol(node);
                break;
			case flag_IF:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
				end_label  = constructPtrToEmptySymbol();
				setFlag(end_label, flag_LABEL);
				sprintf(name, "end_label%d", *numberOfLabel);
				setName(end_label, name);

				*numberOfLabel += 1;
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
			    break;
			case flag_IF_ELSE:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);

                else_label = constructPtrToEmptySymbol();
                setFlag(else_label, flag_LABEL);
				sprintf(name, "else_label%d", *numberOfLabel);
                setName(else_label, name);
				
                end_label = constructPtrToEmptySymbol();
                setFlag(end_label, flag_LABEL);
				sprintf(name, "end_label%d", *numberOfLabel);
                setName(end_label, name);

				*numberOfLabel += 1;
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, else_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getMSide(node), threeAddressCode, offset, numberOfLabel);

				jmp = constructInstruction(code_JMP, NULL, NULL, end_label);
				addInstruction(threeAddressCode, jmp);				
				label = constructInstruction(code_LABEL, NULL, NULL, else_label);
				addInstruction(threeAddressCode, label);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
		    	break;
			case flag_WHILE:
                while_label = constructPtrToEmptySymbol();
                setFlag(while_label, flag_LABEL);
				sprintf(name, "while_label%d", *numberOfLabel);
                setName(while_label, name);

                end_label = constructPtrToEmptySymbol();
                setFlag(end_label, flag_LABEL);
				sprintf(name, "end_label%d", *numberOfLabel);
                setName(end_label, name);

				*numberOfLabel += 1;

				label = constructInstruction(code_LABEL, NULL, NULL, while_label);
				addInstruction(threeAddressCode, label);
			
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset, numberOfLabel);
				
				jmp = constructInstruction(code_JMP, NULL, NULL, while_label);
				addInstruction(threeAddressCode, jmp);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
		    	break;
			case flag_METHOD_DECLARATION:
				*offset = 8;
				int isExtern = getLSide(node) == NULL;

				if(!isExtern) {
					Symbol* symbol = getParams(*getSymbol(node));
					while(symbol) {
						assignOffset(symbol, offset);
						symbol = getParams(*symbol);
					}

                	start_of_function = constructPtrToEmptySymbol();
                	setFlag(start_of_function, flag_LABEL);
                	setName(start_of_function, getName(*getSymbol(node)));

                	end_of_function   = constructPtrToEmptySymbol();
                	setFlag(end_of_function,   flag_LABEL);
                	setName(end_of_function,   getName(*getSymbol(node)));
			
					label = constructInstruction(code_LABEL_START_OF_FUNCTION, getSymbol(node), NULL, start_of_function);
                	addInstruction(threeAddressCode, label);
					generateIntermediateCode(getLSide(node), threeAddressCode, offset, numberOfLabel);
					label = constructInstruction(code_LABEL_END_OF_FUNCTION, getSymbol(node), NULL, end_of_function);
                	addInstruction(threeAddressCode, label);
					assignOffset(getSymbol(node), offset);
				}
		    	break;
			case flag_METHOD_CALL:
				loadParams(getLSide(node), threeAddressCode, offset, numberOfLabel);
				call = constructInstruction(code_CALL, NULL, NULL, getSymbol(node));
				addInstruction(threeAddressCode, call);
                return getSymbol(node);
                break;
            default:
                break;
		}
	}
	
	return NULL;
}

void printInstruction(void* i) {
	Instruction instruction = *(Instruction*) i;
	Code op = instruction.code;
	char* oprnd1 = (char*) malloc(2 * sizeof(char));
	char* oprnd2 = (char*) malloc(2 * sizeof(char));
	char* dest;

	strcpy(oprnd1, "-");
	strcpy(oprnd2, "-");

	if(instruction.fstOperand) { oprnd1 = getName(*(instruction.fstOperand)); }
	if(instruction.sndOperand) { oprnd2 = getName(*(instruction.sndOperand)); }
	dest = getName(*(instruction.dest));
	printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), oprnd1, oprnd2, dest);
}

void showThreeAddressCode(ThreeAddressCode threeAddressCode) {
	showQueue(threeAddressCode.queue, printInstruction);
}
