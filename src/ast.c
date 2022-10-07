#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol.h"

#define TRUE 1
#define FALSE 0

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

	setName(symbol, name);
	setFlag(symbol, flag);

    ASTNode* root = node(symbol);
    root->lSide = lSide;
    root->mSide = mSide;
    root->rSide = rSide;
    return root;
}

int isLeave(ASTNode* node) {
    return !node->lSide && !node->mSide && !node->rSide;
}

void checkReturn(ASTNode* node, Type expected) {
    if(node) {
        Flag flag =  getFlag(*(node->symbol)); //node->symbol->flag;
        if(flag == flag_RETURN) {
            Type returnType = typeCheck(node->lSide);
            if(returnType != expected) {
                printf("%s was expected in return statement\n", typeToString(expected));
		        exit(EXIT_FAILURE);
            }
        }
        
	    checkReturn(node->lSide, expected);
        checkReturn(node->mSide, expected);
        checkReturn(node->rSide, expected);
    }
}

int thereIsAtLeastOneReturn(ASTNode* node) {
    if(node) {
        return (getFlag(*(node->symbol)) == flag_RETURN)
		|| thereIsAtLeastOneReturn(node->lSide)
		|| thereIsAtLeastOneReturn(node->mSide)
		|| thereIsAtLeastOneReturn(node->rSide);
    }

    return FALSE;
}

void checkParams(Symbol* fParams, ASTNode* rParams, char* functionName) {
    if(fParams && rParams) {
        Type fParamType = getType(*fParams);
	    Type rParamType = getType(*(rParams->lSide->symbol));//rParams->lSide->symbol->type;
	if(fParamType == rParamType) {
	    checkParams(fParams->params, rParams->rSide, functionName);
	} else {
	    printf("%s function expected %s but argument is of type %s\n", functionName, typeToString(fParamType), typeToString(rParamType));
	    exit(EXIT_FAILURE);
	}
    } else if(fParams) {
        printf("too few params to function %s\n", functionName);
	    exit(EXIT_FAILURE);
    } else if(rParams) {
        printf("too many params to function %s\n", functionName);
	    exit(EXIT_FAILURE);
    }
}

void typeCheckBinaryOperation(Flag op, Type typeOfTheFstOperand, Type typeOfTheSndOperand, Type expected) {
    if(typeOfTheFstOperand != expected || typeOfTheSndOperand != expected) {
        printf("%s arguments are of type %s x %s but %s x %s were found\n"
			,flagToString(op)
			,typeToString(expected)
			,typeToString(expected)
			,typeToString(typeOfTheFstOperand)
			,typeToString(typeOfTheSndOperand));
	exit(EXIT_FAILURE);
    }
}

void typeCheckEqual(Type typeOfTheFstOperand, Type typeOfTheSndOperand) {
    if(typeOfTheFstOperand != typeOfTheSndOperand) {
        printf("== arguments do not math\n");
	exit(EXIT_FAILURE);
    }
}

void typeCheckUnaryOperation(Flag op, Type typeOfTheOperand, Type expected) {
    if(typeOfTheOperand != expected) {
        printf("%s argument is of type %s but %s was found\n"
			,flagToString(op)
			,typeToString(expected)
			,typeToString(typeOfTheOperand));
	exit(EXIT_FAILURE);
    }
}

void checkIfIsABoolExpression(Type type) {
    if(type != TYPE_BOOL) {
        printf("Expected Bool expression\n");
	exit(EXIT_FAILURE);
    }
}

void checkMethodDeclaration(ASTNode* block, Type returnType, char* name) {
    int hasReturnType = returnType != TYPE_VOID;
    int isExtern      = block == NULL;
    if(!isExtern) {
        if(hasReturnType && thereIsAtLeastOneReturn(block)) {
            checkReturn(block, returnType);
        } else if(hasReturnType) {
            printf("return statement is missing in %s function\n", name);
	    exit(EXIT_FAILURE);
        }
    }
}

void typeCheckAssignment(Type varType, Type expressionType, char* name) {
    if(varType != expressionType) {
        printf("%s is of type %s but the expression is of type %s\n"
			,name
			,typeToString(varType)
			,typeToString(expressionType));
	exit(EXIT_FAILURE);
    }
}

Type typeCheck(ASTNode* node) {
    if(node) {
    	Flag flag = getFlag(*(node->symbol));
		ASTNode* block;
		ASTNode* thenBlock;
		ASTNode* elseBlock;
		ASTNode* rParams;
		Symbol*  fParams;
		Type  returnType;
		switch (flag) {
			case flag_VALUE_INT:
		    	return getType(*(node->symbol));
			case flag_VALUE_BOOL:
		    	return getType(*(node->symbol));
			case flag_IDENTIFIER:
		    	return getType(*(node->symbol));
			case flag_PARAM:
		    	return getType(*(node->symbol));
			case flag_ADDITION:
		    	typeCheckBinaryOperation(flag_ADDITION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
				setType(node->symbol, TYPE_INT);
		    	return TYPE_INT;
			case flag_SUBSTRACTION:
		    	typeCheckBinaryOperation(flag_SUBSTRACTION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    	setType(node->symbol, TYPE_INT);
		    	return TYPE_INT;
			case flag_MULTIPLICATION:
			    typeCheckBinaryOperation(flag_MULTIPLICATION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
			    setType(node->symbol, TYPE_INT);
			    return TYPE_INT;
			case flag_DIVISION:
			    typeCheckBinaryOperation(flag_DIVISION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
			    setType(node->symbol, TYPE_INT);
				return TYPE_INT;
			case flag_MOD:
		    	typeCheckBinaryOperation(flag_MOD, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    	setType(node->symbol, TYPE_INT);
			    return TYPE_INT;
			case flag_OR:
			    typeCheckBinaryOperation(flag_OR, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_BOOL);
		    	setType(node->symbol, TYPE_BOOL);
		    	return TYPE_BOOL;
			case flag_AND:
			    typeCheckBinaryOperation(flag_AND, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_BOOL);
			    setType(node->symbol, TYPE_BOOL);
			    return TYPE_BOOL;
			case flag_RETURN:
		    	typeCheck(node->lSide); // typeCheck(leftSide(node));
		    	break;
			case flag_ASSIGNMENT:
			    typeCheckAssignment(typeCheck(node->lSide), typeCheck(node->rSide), getName(*(node->lSide->symbol)));
			    break;
			case flag_SEMICOLON:
		    	typeCheck(node->lSide);
			    typeCheck(node->rSide);
			    break;
			case flag_LT:
			    typeCheckBinaryOperation(flag_LT, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
			    setType(node->symbol, TYPE_BOOL);
			    return TYPE_BOOL;
			case flag_GT:
			    typeCheckBinaryOperation(flag_GT, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    	setType(node->symbol, TYPE_BOOL);
		    	return TYPE_BOOL;
			case flag_EQT:
			    typeCheckEqual(typeCheck(node->lSide), typeCheck(node->rSide));
		    	setType(node->symbol, TYPE_BOOL);
		    	return TYPE_BOOL;
			case flag_MINUS:
			    typeCheckUnaryOperation(flag_MINUS, typeCheck(node->lSide), TYPE_INT);
		    	setType(node->symbol, TYPE_INT);
		    	return TYPE_INT;
			case flag_NEG:
			    typeCheckUnaryOperation(flag_NEG, typeCheck(node->lSide), TYPE_BOOL);
			    setType(node->symbol, TYPE_BOOL);
                return TYPE_BOOL;
			case flag_IF:
		    	thenBlock = node->rSide;
		    	checkIfIsABoolExpression(typeCheck(node->lSide));
		    	typeCheck(thenBlock);
		    	break;
			case flag_IF_ELSE:
			    thenBlock = node->mSide;
		    	elseBlock = node->rSide;
		    	checkIfIsABoolExpression(typeCheck(node->lSide));
		    	typeCheck(thenBlock);
		    	typeCheck(elseBlock);
		    	break;
			case flag_WHILE:
			    block = node->rSide;
			    checkIfIsABoolExpression(typeCheck(node->lSide));
			    typeCheck(block);
		    	break;
			case flag_METHOD_DECLARATION:
			    block      = node->lSide;
			    returnType = getType(*(node->symbol));
		    	checkMethodDeclaration(block, returnType, getName(*(node->symbol)));
		    	typeCheck(block);
		    	break;
			case flag_METHOD_CALL:
			    fParams = node->symbol->params;
		    	rParams = node->lSide;
			    checkParams(fParams, rParams, node->symbol->name);
			    return node->symbol->type;
			default:
		    	break;
		}
    }

    return 0;
}

void printAST(ASTNode* root) {
	if(root) {
	  printf("-- FATHER --\n");
	  printf("FLAG: %s, NAME: %s\n", flagToString(root->symbol->flag), root->symbol->name);
	  if(isFunction(*(root->symbol))) {
	      Symbol* params = root->symbol->params;
	      while(params) {
	          printf("PARAM: %s, ", params->name);
		  params = params->params;
	      }
	  }
	  if(root->lSide) {
	      printf("Left side: \n");
	      printAST(root->lSide);
	  }

	  if(root->mSide) {
	      printf("Mid side: \n");
	      printAST(root->mSide);
	  }

	  if(root->rSide) {
	      printf("Right side: \n");
	      printAST(root->rSide);
	  }

	  printf(" -- BACKTRACK  -- \n");
	}
}
