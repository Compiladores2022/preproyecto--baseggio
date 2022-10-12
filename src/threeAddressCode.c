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

void loadParams(ASTNode* node, ThreeAddressCode* threeAddressCode, int* offset) {
    if(node) {
    	Instruction load = constructInstruction(code_LOAD, NULL, NULL, generateIntermediateCode(getLSide(node), threeAddressCode, offset));
    	addInstruction(threeAddressCode, load);
    	loadParams(getRSide(node), threeAddressCode, offset);
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
        char name[16];
		switch (flag) {
			case flag_VALUE_INT:
			    return getSymbol(node);
			case flag_VALUE_BOOL:
                setName(getSymbol(node), (getValue(*getSymbol(node)) == 1? "true" : "false"));
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

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_SUBSTRACTION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_SUBSTRACTION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_MULTIPLICATION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_MULTIPLICATION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_DIVISION:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_DIVISION, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_MOD:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_MOD, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);
                
                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_OR:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_OR, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_AND:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_AND, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

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

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_GT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_GT, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_EQT:
				fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_EQT, fstOperand, sndOperand, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_MINUS:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_MINUS, expression, NULL, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_NEG:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
			    instruction = constructInstruction(code_NEG, expression, NULL, getSymbol(node));
			    addInstruction(threeAddressCode, instruction);

                sprintf(name, "t%d", threeAddressCode->numberOfTemporaries++);
                setName(getSymbol(node), name);

			    return getSymbol(node);
			case flag_IF:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				
				end_label  = constructPtrToEmptySymbol();
				setFlag(end_label, flag_LABEL);
				setName(end_label, "end_label");
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
			    break;
			case flag_IF_ELSE:
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);

                else_label = constructPtrToEmptySymbol();
                setFlag(else_label, flag_LABEL);
                setName(else_label, "else_label");

                end_label = constructPtrToEmptySymbol();
                setFlag(end_label, flag_LABEL);
                setName(end_label, "end_label");
				
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
                while_label = constructPtrToEmptySymbol();
                setFlag(while_label, flag_LABEL);
                setName(while_label, "while_label");

                end_label = constructPtrToEmptySymbol();
                setFlag(end_label, flag_LABEL);
                setName(end_label, "end_label");

				label = constructInstruction(code_LABEL, NULL, NULL, while_label);
				addInstruction(threeAddressCode, label);
			
				expression = generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				
				instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
				addInstruction(threeAddressCode, instruction);
				
				generateIntermediateCode(getRSide(node), threeAddressCode, offset);
				
				jmp = constructInstruction(code_JMP, NULL, NULL, while_label);
				addInstruction(threeAddressCode, jmp);
				
				label = constructInstruction(code_LABEL, NULL, NULL, end_label);
				addInstruction(threeAddressCode, label);
				
		    	break;
			case flag_METHOD_DECLARATION:
                start_of_function = constructPtrToEmptySymbol();
                setFlag(start_of_function, flag_LABEL);
                setName(start_of_function, getName(*getSymbol(node)));

                end_of_function   = constructPtrToEmptySymbol();
                setFlag(end_of_function,   flag_LABEL);
                setName(end_of_function,   getName(*getSymbol(node)));

			
				label = constructInstruction(code_LABEL_START_OF_FUNCTION, getSymbol(node), NULL, start_of_function);
                addInstruction(threeAddressCode, label);
				generateIntermediateCode(getLSide(node), threeAddressCode, offset);
				label = constructInstruction(code_LABEL_END_OF_FUNCTION, getSymbol(node), NULL, end_of_function);
                addInstruction(threeAddressCode, label);
		    	break;
			case flag_METHOD_CALL:
				loadParams(getLSide(node), threeAddressCode, offset);
				call = constructInstruction(code_CALL, NULL, NULL, getSymbol(node));
				addInstruction(threeAddressCode, call);
                return getSymbol(node);
            default:
                break;
		}
	}
	
	return NULL;
}

void printInstruction(void* i) {
  Instruction instruction = *(Instruction*) i;
  Code op = instruction.code;

  if(iCodeIsABinaryOperator(op)) {
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), oprnd1, oprnd2, dest);
  }

  if(op == code_ASSIGNMENT) {
    char* expr = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    char* dest = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), expr, "-", dest);
  }

  if(op == code_RETURN) {
    char* dest = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_FALSE_CONDITIONAL) {
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), oprnd1, "-", dest);
  }

  if(op == code_JMP) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_LABEL) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_LABEL_START_OF_FUNCTION) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_LABEL_END_OF_FUNCTION) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_MINUS) {
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), oprnd1, "-", dest);
  }

  if(op == code_NEG) {
    char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), oprnd1, "-", dest);
  }

  if(op == code_CALL) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
  }

  if(op == code_LOAD) {
    //char* oprnd1 = getName(*(instruction.fstOperand)); //instruction.fstOperand->name;
    //char* oprnd2 = getName(*(instruction.sndOperand)); //instruction.sndOperand->name;
    char* dest   = getName(*(instruction.dest)); //instruction.dest->name;
    printf("%-18s %-10s %-10s %-18s\n", iCodeToString(op), "-", "-", dest);
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
    char* res = (char*) malloc(16 * sizeof(char));
    if(isValue(getFlag(*symbol))) {
        sprintf(res, "$%d",        getValue(*symbol));
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
