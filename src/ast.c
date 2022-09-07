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

char* flagRepresentation(Flag flag){
    switch ( flag ) {
	    case IDENTIFIER :
		  return "ID";
		  break;
	    case ADDITION :
		  return "+";
		  break;
	    case MULTIPLICATION :
		  return "*";
		  break;
	    case OP_OR :
		  return "||";
		  break;
	    case OP_AND :
		  return "&&";
		  break;
	    case ASSIGNMENT: 
		  return "=";
		  break;
	    case SEMICOLON :
		  return ";";
		  break;
	    case VALUE_INT :
		  return "vInt";
		  break;
	    case VALUE_BOOL :
		  return "vBool";
		  break;
	    case RETURN :
		  return "return";
		  break;
	    default :
		  return "no representation found";
		  break;
    }
}

int isLeave(ASTNode* node) {
    return !node->lSide && !node->mSide && !node->rSide;
}

int isAnArithmeticBinaryOperator(Flag flag) {return flag == ADDITION || flag == MULTIPLICATION; }

int isAnBooleanBinaryOperator(Flag flag) { return flag == OP_OR || flag == OP_AND; }

char* typeRepresentation(Type type) {
    switch (type) {
        case TYPE_INT:
		return "Int" ;
		break;
	case TYPE_BOOL:
		return "Bool";
		break;
	default:
		return "no representation found";
		break;
    }
}

void reportErrorIfExists(Type typeOfTheFstOperand, Type typeOfTheSndOperand, Type expectedType, Flag operator) {
    if(!(typeOfTheFstOperand == typeOfTheSndOperand && typeOfTheSndOperand == expectedType)) {
	printf("%s arguments are of type: %sx%s but %sx%s was found\n", flagRepresentation(operator), typeRepresentation(expectedType), typeRepresentation(expectedType), typeRepresentation(typeOfTheFstOperand), typeRepresentation(typeOfTheSndOperand));
	exit(EXIT_FAILURE);
    }
}

void reportAssignmentErrorIfExists(Type varType, Type exprType, char* varName) {
	if(!(varType == exprType)) {
	    printf("%s is of type %s but the expresion is of type %s\n", varName, typeRepresentation(varType), typeRepresentation(exprType));
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
