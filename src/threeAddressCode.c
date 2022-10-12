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

void loadParams(Symbol* param, ThreeAddressCode* threeAddressCode) {
    if(param) {
    	Instruction load = constructInstruction(code_LOAD, NULL, NULL, param);
    	addInstruction(threeAddressCode, load);
    	loadParams(param->params, threeAddressCode);
    }
}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset) {
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
		switch (flag) {
			case flag_VALUE_INT:
			    	return getSymbol(node);
			case flag_VALUE_BOOL:
			    	return getSymbol(node);
			case flag_IDENTIFIER:
			    	return getSymbol(node);
			case flag_PARAM:
			    	return getSymbol(node);
			case flag_ADDITION:
			    	fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_ADDITION, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_SUBSTRACTION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_SUBSTRACTION, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_MULTIPLICATION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_MULTIPLICATION, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_DIVISION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_DIVISION, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_MOD:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_MOD, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_OR:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_OR, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_AND:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_AND, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_RETURN:
			        expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			        instruction = constructInstruction(code_RETURN, NULL, NULL, expression);
			        addInstruction(threeAddressCode, instruction);
            			break;
			case flag_ASSIGNMENT:
		            	expression  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
            			instruction = constructInstruction(code_ASSIGNMENT, expression, NULL, getSymbol(getLSide(node)));
			        addInstruction(threeAddressCode, instruction);
			        break;
			case flag_SEMICOLON:
				generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			        generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				break;
			case flag_LT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_LT, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_GT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_GT, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_EQT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_EQT, fstOperand, sndOperand, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_MINUS:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_MINUS, expression, NULL, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_NEG:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    	instruction = constructInstruction(code_NEG, expression, NULL, getSymbol(node));
			    	addInstruction(threeAddressCode, instruction);
			    	return getSymbol(node);
			case flag_IF:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				
				end_label  = constructPtrToEmptySymbol();
				setFlag(end_label, code_LABEL);
				setName(end_label, "end_label");
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
			    	break;
			case flag_IF_ELSE:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				
				//construct end_label
				//construct else_label
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, else_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getMSide(node), threeAddressCode, offset);

				jmp = constructInstruction(code_JMP, NULL, NULL, end_label);
				addInstruction(threeAddressCode, jmp);				
				label = constructInstruction(code_LABEL, NULL, NULL, else_label);
				addInstruction(threeAddressCode, label);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
		    		break;
			case flag_WHILE:
				label = constructInstruction(code_LABEL, NULL, NULL, while_label);
				addInstruction(threeAddressCode, label);
			
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				
				//construct while_label
				//construct end_label
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				
				jmp = constructInstruction(code_JMP, NULL, NULL, while_label);
				addInstruction(threeAddressCode, jmp);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
		    		break;
			case flag_METHOD_DECLARATION:
			
				//construct start_of_function
				//construct end_of_function
			
				label = constructInstruction(code_LABEL, getSymbol(node), NULL, start_of_function);
				generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				label = constructInstruction(code_LABEL, getSymbol(node), NULL, end_of_function);
		    		break;
			case flag_METHOD_CALL:
				loadParams(getParams(getSymbol(node)), threeAddressCode);
				call = constructInstruction(code_CALL, NULL, NULL, getSymbol(node));
				addInstruction(threeAddressCode, call);
			    	break;
		}
	}
	
	return NULL;
}

void printInstruction(void* i) {
/*  Instruction instruction = *(Instruction*) i;
  Code op = instruction.code;
  if(isABinaryOperator(op)) {
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s %s %s %s\n", flagToString(op), oprnd1, oprnd2, dest);
  }

  if(op == code_ASSIGNMENT) {
    char* expr = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* dest = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s %s - %s\n", flagToString(op), expr, dest);
  }

  if(op == code_RETURN) {
    char* expr = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%s - - %s\n", flagToString(op), expr);
  }
*/
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
    /*Flag op = i.op;
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
		    fprintf(fp, "\n\tmovq $%d, -%d(%%rbp)", getValue(*(i.fstOperand)), getOffset(*(i.dest)));
		}
		break;
	default:
		break;
    }*/
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
