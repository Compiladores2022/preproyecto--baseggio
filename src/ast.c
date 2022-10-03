#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol.h"

ASTNode* node(Symbol* symbol) {
    ASTNode* leaf = (ASTNode*) malloc(sizeof(ASTNode));
    if(leaf == NULL) { exit(EXIT_FAILURE); }
    leaf->symbol = symbol;
    leaf->lSide  = NULL;
    leaf->mSide  = NULL;
    leaf->rSide  = NULL;
    return leaf;
}

ASTNode* composeTree(Flag flag, const char* name, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide) {
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->name = (char*) malloc(sizeof(char));
    strcpy(symbol->name, name);
    symbol->flag = flag;
    ASTNode* root = node(symbol);
    root->lSide = lSide;
    root->mSide = mSide;
    root->rSide = rSide;
    return root;
}

int isLeave(ASTNode* node) {
    return !node->lSide && !node->mSide && !node->rSide;
}

void reportErrorIfExists(Type typeOfTheFstOperand, Type typeOfTheSndOperand, Type expectedType, Flag operator) {
    if(!(typeOfTheFstOperand == typeOfTheSndOperand && typeOfTheSndOperand == expectedType)) {
	printf("%s arguments are of type: %s x %s but %s x %s was found\n"
		       	,flagToString(operator)
			,typeToString(expectedType)
			,typeToString(expectedType)
			,typeToString(typeOfTheFstOperand) 
			,typeToString(typeOfTheSndOperand));
	exit(EXIT_FAILURE);
    }
}

void reportAssignmentErrorIfExists(Type varType, Type exprType, char* varName) {
	if(!(varType == exprType)) {
	    printf("%s is of type %s but the expresion is of type %s\n"
			    ,varName
			    ,typeToString(varType)
			    ,typeToString(exprType));
	    exit(EXIT_FAILURE);
	}
}

Type typeCheck(ASTNode* node) {
    if(node) {
	    if(isLeave(node)) { return node->symbol->type; }
	    Flag flag = node->symbol->flag;
	    if(isAnArithmeticBinaryOperator(flag)) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_INT, flag);
		node->symbol->type = typeOfTheFstOperand;
		return node->symbol->type;
	    }

	    if(isABooleanBinaryOperator(flag)) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_BOOL, flag);
		node->symbol->type = typeOfTheFstOperand;
		return node->symbol->type;
	    }

	    if(flag == flag_RETURN) {
	        typeCheck(node->lSide);
	    }

	    if(flag == flag_ASSIGNMENT) {
	        Type varType  = typeCheck(node->lSide);
		Type exprType = typeCheck(node->rSide);
		reportAssignmentErrorIfExists(varType, exprType, node->lSide->symbol->name);
	    }

	    if(flag == flag_SEMICOLON) {
	        typeCheck(node->lSide);
		typeCheck(node->rSide);
	    }
    }

    return 0;
}

int evaluateOperation(int valueOfTheFstOperand, int valueOfTheSndOperand, Flag operator) {
    switch (operator) {
        case flag_ADDITION:
		return valueOfTheFstOperand + valueOfTheSndOperand;
	case flag_MULTIPLICATION:
		return valueOfTheFstOperand * valueOfTheSndOperand;
	case flag_OR:
		return valueOfTheFstOperand || valueOfTheSndOperand;
	case flag_AND:
		return valueOfTheFstOperand && valueOfTheSndOperand;
	default:
		return 0;
    }
}

int evaluate(ASTNode* node) {
    if(node) {
        if(isLeave(node)) { return node->symbol->value; }
	Flag flag = node->symbol->flag;

        if(isABinaryOperator(flag)) {
	    int valueOfTheFstOperand = evaluate(node->lSide);
	    int valueOfTheSndOperand = evaluate(node->rSide);
	    return node->symbol->value = evaluateOperation(valueOfTheFstOperand, valueOfTheSndOperand, flag);
	}

	if(flag == flag_RETURN) {
	    printf("%d\n", evaluate(node->lSide));
	}

	if(flag == flag_ASSIGNMENT) {
	    node->lSide->symbol->value = evaluate(node->rSide);
	}

	if(flag == flag_SEMICOLON) {
	    evaluate(node->lSide);
	    evaluate(node->rSide);
	}
    }

    return 0;
}

void printAST(ASTNode* root) {
    if(root != NULL) {        
        printAST(root->lSide);
	printAST(root->mSide);
	printAST(root->rSide);
	//
	//root->lSide;
	//root->mSide;
	//root->rSide;

	printf("FLAG: %s NAME: %s\n", flagToString(root->symbol->flag), root->symbol->name);
	if(root->symbol->flag == flag_METHOD) {
	    
	    Symbol* params = root->symbol->params;
	    while(params) {
	        printf("TYPE: %s, NAME: %s\n", typeToString(params->type), params->name);
		params = params->params;
	    }
	}
    }
}
