#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "threeAddressCode.h"

#define TRUE  1
#define FALSE 0

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
    add(&threeAddressCode->list, data, sizeof(instruction), FALSE);
}

List generateIntermediateCodeForParameters(ASTNode* node
					  ,ThreeAddressCode* threeAddressCode) {
    	List list;
    	
    	constructList(&list);
    	
    	ASTNode* ptr = node;
    	while(ptr) {
    		Symbol* param = generateIntermediateCode(getLSide(ptr), threeAddressCode);
    		add(&list, (void *) param, sizeof(Symbol*), TRUE);
    		ptr = getRSide(ptr);
    	}
    	
    	return list;
}

void loadParameters(List list, ThreeAddressCode* threeAddressCode) {    
    while(!isEmpty(list)) {
    	Instruction load = constructInstruction(code_LOAD, NULL, NULL, (Symbol *) head(list));
    	addInstruction(threeAddressCode, load);
    	removeFirst(&list);
    }
}

int params(Symbol* symbol) {
	if(symbol) {
		return 1 + params(symbol->params);
	}

	return 0;
}

void assignOffset(Symbol* symbol, ThreeAddressCode* threeAddressCode) {
	setOffset(symbol, threeAddressCode->offset);
	threeAddressCode->offset += 8;
}

Symbol* generateIntermediateCodeForBinaryOperation(Code iCode
						  ,ASTNode* node
						  ,ThreeAddressCode* threeAddressCode) {
	Symbol* fstOperand;
	Symbol* sndOperand;
	Instruction instruction;
	fstOperand  = generateIntermediateCode(getLSide(node), threeAddressCode);
	sndOperand  = generateIntermediateCode(getRSide(node), threeAddressCode);
	instruction = constructInstruction(iCode, fstOperand, sndOperand, getSymbol(node));
	addInstruction(threeAddressCode, instruction);
	assignOffset(getSymbol(node), threeAddressCode);
	
	return getSymbol(node);
}

Symbol* generateIntermediateCodeForNeg(ASTNode* node
				      ,ThreeAddressCode* threeAddressCode) {
				      
	Symbol* expression;
	Instruction instruction;
	expression  = generateIntermediateCode(getLSide(node), threeAddressCode);
	instruction = constructInstruction(code_NEG, expression, NULL, getSymbol(node));
	addInstruction(threeAddressCode, instruction);
	assignOffset(getSymbol(node), threeAddressCode);
	return getSymbol(node);	      
}

void generateIntermediateCodeForIF(ASTNode* node
				  ,ThreeAddressCode* threeAddressCode) {
				  
	Symbol* expression;
	Symbol* end_label;
	char name[16];
	Instruction instruction;
	Instruction label;
				  
	expression = generateIntermediateCode(getLSide(node), threeAddressCode);
	end_label  = constructPtrToEmptySymbol();
	setFlag(end_label, flag_LABEL);
	sprintf(name, "end_label%d", threeAddressCode->numberOfLabel);
	setName(end_label, name);
	threeAddressCode->numberOfLabel += 1;
	instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
	addInstruction(threeAddressCode, instruction);
	generateIntermediateCode(getRSide(node), threeAddressCode);
	label = constructInstruction(code_LABEL, NULL, NULL, end_label);
	addInstruction(threeAddressCode, label);  
}

void generateIntermediateCodeForIF_ELSE(ASTNode* node
				  ,ThreeAddressCode* threeAddressCode) {
	Symbol* expression;
	Symbol* else_label;
	Symbol* end_label;
	char name[16];
	Instruction jmp;
	Instruction label;
	Instruction instruction;
	expression = generateIntermediateCode(getLSide(node), threeAddressCode);
	else_label = constructPtrToEmptySymbol();
	setFlag(else_label, flag_LABEL);
	sprintf(name, "else_label%d", threeAddressCode->numberOfLabel);
	setName(else_label, name);

	end_label = constructPtrToEmptySymbol();
	setFlag(end_label, flag_LABEL);
	sprintf(name, "end_label%d", threeAddressCode->numberOfLabel);
	setName(end_label, name);

	threeAddressCode->numberOfLabel += 1;

	instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, else_label);
	addInstruction(threeAddressCode, instruction);

	generateIntermediateCode(getMSide(node), threeAddressCode);

	jmp = constructInstruction(code_JMP, NULL, NULL, end_label);
	addInstruction(threeAddressCode, jmp);				
	label = constructInstruction(code_LABEL, NULL, NULL, else_label);
	addInstruction(threeAddressCode, label);

	generateIntermediateCode(getRSide(node), threeAddressCode);

	label = constructInstruction(code_LABEL, NULL, NULL, end_label);
	addInstruction(threeAddressCode, label);		  
}

void generateIntermediateCodeForWHILE(ASTNode* node
				  ,ThreeAddressCode* threeAddressCode) {
				  
	Symbol* expression;
	Symbol* while_label;
	Symbol* end_label;
	Instruction label;
	Instruction instruction;
	Instruction jmp;
	char name[16];
				  
	while_label = constructPtrToEmptySymbol();
	setFlag(while_label, flag_LABEL);
	sprintf(name, "while_label%d", threeAddressCode->numberOfLabel);
	setName(while_label, name);

	end_label = constructPtrToEmptySymbol();
	setFlag(end_label, flag_LABEL);
	sprintf(name, "end_label%d", threeAddressCode->numberOfLabel);
	setName(end_label, name);

	threeAddressCode->numberOfLabel += 1;

	label = constructInstruction(code_LABEL, NULL, NULL, while_label);
	addInstruction(threeAddressCode, label);

	expression = generateIntermediateCode(getLSide(node), threeAddressCode);

	instruction = constructInstruction(code_FALSE_CONDITIONAL, expression, NULL, end_label);
	addInstruction(threeAddressCode, instruction);

	generateIntermediateCode(getRSide(node), threeAddressCode);

	jmp = constructInstruction(code_JMP, NULL, NULL, while_label);
	addInstruction(threeAddressCode, jmp);

	label = constructInstruction(code_LABEL, NULL, NULL, end_label);
	addInstruction(threeAddressCode, label);			  
}

void generateIntermediateCodeForMethodDeclaration(ASTNode* node
				  ,ThreeAddressCode* threeAddressCode) {
	threeAddressCode->offset = 8;
	int isExtern = getLSide(node) == NULL;
	if(!isExtern) {
		Symbol* start_of_function;
		Symbol* end_of_function;
		Instruction label;
		Symbol* symbol = getParams(*getSymbol(node));
		while(symbol) {
			assignOffset(symbol, threeAddressCode);
			symbol = getParams(*symbol);
		}

		start_of_function = constructPtrToEmptySymbol();
		setFlag(start_of_function, flag_LABEL);
		setName(start_of_function, getName(*getSymbol(node)));

		end_of_function = constructPtrToEmptySymbol();
		setFlag(end_of_function, flag_LABEL);
		setName(end_of_function, getName(*getSymbol(node)));

		label = constructInstruction(code_LABEL_START_OF_FUNCTION, getSymbol(node), NULL, start_of_function);
		addInstruction(threeAddressCode, label);
		generateIntermediateCode(getLSide(node), threeAddressCode);
		label = constructInstruction(code_LABEL_END_OF_FUNCTION, getSymbol(node), NULL, end_of_function);
		addInstruction(threeAddressCode, label);
		assignOffset(getSymbol(node), threeAddressCode);
	}
}

Symbol* generateIntermediateCodeForMethodCall(ASTNode* node
				  ,ThreeAddressCode* threeAddressCode) {
	Instruction call;
				  
	List params = generateIntermediateCodeForParameters(getLSide(node), threeAddressCode);
	loadParameters(params, threeAddressCode);
	Symbol* temp = constructPtrToEmptySymbol();
	assignOffset(temp, threeAddressCode);
	call = constructInstruction(code_CALL, temp, NULL, getSymbol(node));
	addInstruction(threeAddressCode, call);
	return temp;
}

Symbol* generateIntermediateCode(ASTNode* node, ThreeAddressCode* threeAddressCode) {
	if(node) {
		Flag flag = getFlag(*(node->symbol));
		Symbol* expression;
		Instruction instruction;
		switch (flag) {
			case flag_VALUE_INT:
				return getSymbol(node);
				break;
			case flag_VALUE_BOOL:
				//setName(getSymbol(node), (getValue(*getSymbol(node)) == 1? "true" : "false"));
				return getSymbol(node);
				break;
			case flag_IDENTIFIER:
				return getSymbol(node);
				break;
			case flag_PARAM:
				return getSymbol(node);
				break;
			case flag_ADDITION:
				return generateIntermediateCodeForBinaryOperation(code_ADDITION
										 ,node
										 ,threeAddressCode);
				break;
			case flag_SUBSTRACTION:
				return generateIntermediateCodeForBinaryOperation(code_SUBSTRACTION
										 ,node
										 ,threeAddressCode);
				break;
			case flag_MULTIPLICATION:
				return generateIntermediateCodeForBinaryOperation(code_MULTIPLICATION
										 ,node
										 ,threeAddressCode);
				break;
			case flag_DIVISION:
				return generateIntermediateCodeForBinaryOperation(code_DIVISION
										 ,node
										 ,threeAddressCode);
				break;
			case flag_MOD:
				return generateIntermediateCodeForBinaryOperation(code_MOD
										 ,node
										 ,threeAddressCode);
				break;
			case flag_OR:
				return generateIntermediateCodeForBinaryOperation(code_OR
										 ,node
										 ,threeAddressCode);
				break;
			case flag_AND:
				return generateIntermediateCodeForBinaryOperation(code_AND
										 ,node
										 ,threeAddressCode);
				break;
			case flag_RETURN:
				expression  = generateIntermediateCode(getLSide(node), threeAddressCode);
				instruction = constructInstruction(code_RETURN, NULL, NULL, expression);
				addInstruction(threeAddressCode, instruction);
				break;
			case flag_ASSIGNMENT:
				expression  = generateIntermediateCode(getRSide(node), threeAddressCode);
				instruction = constructInstruction(code_ASSIGNMENT, expression, NULL, getSymbol(getLSide(node)));
				addInstruction(threeAddressCode, instruction);
				assignOffset(getSymbol(getLSide(node)), threeAddressCode);
				break;
			case flag_GLOBAL_VAR_DECL:
				expression = constructPtrToEmptySymbol();
				setValue(expression, evaluate(getRSide(node)));
				instruction = constructInstruction(code_GLOBAL_VAR_DECL
							,expression
							,NULL
							,getSymbol(getLSide(node)));
				addInstruction(threeAddressCode, instruction);
				break;
			case flag_SEMICOLON:
				generateIntermediateCode(getLSide(node), threeAddressCode);
				generateIntermediateCode(getRSide(node), threeAddressCode);
				break;
			case flag_LT:
				return generateIntermediateCodeForBinaryOperation(code_LT
										 ,node
										 ,threeAddressCode);
				break;
			case flag_GT:
				return generateIntermediateCodeForBinaryOperation(code_GT
										 ,node
										 ,threeAddressCode);
				break;
			case flag_EQT:
				return generateIntermediateCodeForBinaryOperation(code_EQT
										 ,node
										 ,threeAddressCode);
				break;
			case flag_NEG:
				return generateIntermediateCodeForNeg(node, threeAddressCode);
				break;
			case flag_IF:
				generateIntermediateCodeForIF(node, threeAddressCode);
				break;
			case flag_IF_ELSE:
				generateIntermediateCodeForIF_ELSE(node, threeAddressCode);
				break;
			case flag_WHILE:
				generateIntermediateCodeForWHILE(node, threeAddressCode);
				break;
			case flag_METHOD_DECLARATION:
				generateIntermediateCodeForMethodDeclaration(node, threeAddressCode);
				break;
			case flag_METHOD_CALL:
				return generateIntermediateCodeForMethodCall(node, threeAddressCode);
				break;
			default:
				break;
		}
	}
	
	return NULL;
}

void ThreeAddressCode_construct(ThreeAddressCode* threeAddressCode) {
	constructList(&threeAddressCode->list);
	threeAddressCode->offset = 8;
	threeAddressCode->numberOfLabel = 0;
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
	print(threeAddressCode.list, printInstruction);
}
