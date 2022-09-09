#include "ast.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

ASTNode* node(Symbol* symbol) {
    ASTNode* leaf = (ASTNode*) malloc(sizeof(ASTNode));
    if(leaf == NULL) { exit(EXIT_FAILURE); }
    leaf->symbol = symbol;
    leaf->lSide  = NULL;
    leaf->mSide  = NULL;
    leaf->rSide  = NULL;
    return leaf;
}

void compose(ASTNode* root, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide) {
    root->lSide = lSide;
    root->mSide = mSide;
    root->rSide = rSide;
}

int isLeave(ASTNode* node) {
    return !node->lSide && !node->mSide && !node->rSide;
}

void reportErrorIfExists(Type typeOfTheFstOperand, Type typeOfTheSndOperand, Type expectedType, Flag operator) {
    if(!(typeOfTheFstOperand == typeOfTheSndOperand && typeOfTheSndOperand == expectedType)) {
	printf("%s arguments are of type: %sx%s but %sx%s was found\n", flagToString(operator), typeToString(expectedType), typeToString(expectedType), typeToString(typeOfTheFstOperand), typeToString(typeOfTheSndOperand));
	exit(EXIT_FAILURE);
    }
}

void reportAssignmentErrorIfExists(Type varType, Type exprType, char* varName) {
	if(!(varType == exprType)) {
	    printf("%s is of type %s but the expresion is of type %s\n", varName, typeToString(varType), typeToString(exprType));
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

	    if(isAnBooleanBinaryOperator(flag)) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_BOOL, flag);
		node->symbol->type = typeOfTheFstOperand;
		return node->symbol->type;
	    }

	    if(flag == RETURN) {
	        typeCheck(node->lSide);
	    }

	    if(flag == ASSIGNMENT) {
	        Type varType  = typeCheck(node->lSide);
		Type exprType = typeCheck(node->rSide);
		reportAssignmentErrorIfExists(varType, exprType, node->lSide->symbol->name);
	    }

	    if(flag == SEMICOLON) {
	        typeCheck(node->lSide);
		typeCheck(node->rSide);
	    }
    }

    return 0;
}
