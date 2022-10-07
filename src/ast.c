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

void checkReturn(ASTNode* node, Type expected) {
    if(node) {
        Flag flag = node->symbol->flag;
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
        return (node->symbol->flag == flag_RETURN)
		|| thereIsAtLeastOneReturn(node->lSide)
		|| thereIsAtLeastOneReturn(node->mSide)
		|| thereIsAtLeastOneReturn(node->rSide);
    }

    return FALSE;
}

void checkParams(Symbol* fParams, ASTNode* rParams, char* functionName) {
    if(fParams && rParams) {
        Type fParamType = fParams->type;
	Type rParamType = rParams->lSide->symbol->type;
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

Type typeCheck(ASTNode* node) {
    if(node) {
	    Flag flag = node->symbol->flag;
	    if(flag == flag_VALUE_INT || flag == flag_VALUE_BOOL || flag == flag_IDENTIFIER || flag == flag_PARAM) { return node->symbol->type; }
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
	    
	    if(flag == flag_LT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_INT, flag);
		node->symbol->type = TYPE_BOOL;
		return TYPE_BOOL;
	    }
	    
	    if(flag == flag_GT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_INT, flag);
		node->symbol->type = TYPE_BOOL;
		return TYPE_BOOL;
	    }
	    
	    if(flag == flag_EQT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		if(typeOfTheFstOperand == typeOfTheSndOperand) {
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		} else {
		    printf("%s arguments %s x %s does not match.\n"
		       	,flagToString(flag_EQT)
			,typeToString(typeOfTheFstOperand) 
			,typeToString(typeOfTheSndOperand));
		    exit(EXIT_FAILURE);
		}
	    }
	    
	    if(flag == flag_MINUS) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
	        if(typeOfTheFstOperand == TYPE_INT) {
			node->symbol->type = TYPE_INT;
	        	return typeOfTheFstOperand;
	        } else {
	        	printf("%s is of type %s but the expression is of type %s.\n"
		       	,flagToString(flag_MINUS)
			,typeToString(TYPE_INT) 
			,typeToString(typeOfTheFstOperand));
		    exit(EXIT_FAILURE);
	        }
	    }
	    
	    if(flag == flag_NEG) {
	    	Type typeOfTheFstOperand = typeCheck(node->lSide);
	        if(typeOfTheFstOperand == TYPE_BOOL) {
			node->symbol->type = TYPE_BOOL;
	        	return typeOfTheFstOperand;
	        } else {
	        	printf("%s is of type %s but the expression is of type %s.\n"
		       	,flagToString(flag_NEG)
			,typeToString(TYPE_BOOL) 
			,typeToString(typeOfTheFstOperand));
		    exit(EXIT_FAILURE);
	        }
	    }
	    
	    if(flag == flag_IF) {
	    	Type typeOfTheFstOperand = typeCheck(node->lSide);
	    	if(typeOfTheFstOperand == TYPE_BOOL) {
	    	    typeCheck(node->rSide);
	    	} else {
	    	    printf("Bool expression was expected.\n");
		    exit(EXIT_FAILURE);
	    	}
	    }
	    
	    if(flag == flag_IF_ELSE) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
	    	if(typeOfTheFstOperand == TYPE_BOOL) {
	    	    typeCheck(node->mSide);
	    	    typeCheck(node->rSide);
	    	} else {
	    	    printf("Bool expression was expected.\n");
		    exit(EXIT_FAILURE);
	    	}
	    }
	    
	    if(flag == flag_WHILE) {
		Type typeOfTheFstOperand = typeCheck(node->lSide);
	    	if(typeOfTheFstOperand == TYPE_BOOL) {
		    typeCheck(node->rSide);
	    	} else {
	    	    printf("Bool expression was expected.\n");
		    exit(EXIT_FAILURE);
	    	}
	    }
	    
	    if(flag == flag_METHOD_DECLARATION) {
		int isExtern      = node->lSide == NULL;
		int hasReturnType = node->symbol->type != TYPE_VOID;
		ASTNode* block          = node->lSide;
		Type expectedReturnType = node->symbol->type;
		if(!isExtern) {
		    if(hasReturnType) {
		        if(thereIsAtLeastOneReturn(block)) {
			    checkReturn(block, expectedReturnType);
			} else {
			    printf("return is missing in function %s\n", node->symbol->name);
			    exit(EXIT_FAILURE);
			}
		    }
		    typeCheck(block);
		}
	    }

            if(flag == flag_METHOD_CALL) { 
		  Symbol*  fParams = node->symbol->params;
                  ASTNode* rParams = node->lSide;
		  checkParams(fParams, rParams, node->symbol->name);
	    }
    }

    return 0;
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
    if(hasReturnType && thereIsAtLeastOneReturn(block)) {
        checkReturn(block, returnType);
    } else if(hasReturnType) {
        printf("return statement is missing in %s function\n", name);
	exit(EXIT_FAILURE);
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

Type typeCheck_(ASTNode* node) {
    if(node) {
    	Flag flag = node->symbol->flag; // getFlag(getSymbol(node));
	ASTNode* block;
	ASTNode* thenBlock;
	ASTNode* elseBlock;
	ASTNode* rParams;
	Symbol*  fParams;
	Type  returnType;
	switch (flag) {
		case flag_VALUE_INT:
		    return node->symbol->type; // getType(getSymbol(node));
		case flag_VALUE_BOOL:
		    return node->symbol->type; // getType(getSymbol(node));
		case flag_IDENTIFIER:
		    return node->symbol->type; // getType(getSymbol(node));
		case flag_PARAM:
		    return node->symbol->type; // getType(getSymbol(node));
		case flag_ADDITION:
		    typeCheckBinaryOperation(flag_ADDITION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_INT; // setType(getSymbol(node), TYPE_INT);
		    return TYPE_INT;
		case flag_SUBSTRACTION:
		    typeCheckBinaryOperation(flag_SUBSTRACTION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_INT;
		    return TYPE_INT;
		case flag_MULTIPLICATION:
		    typeCheckBinaryOperation(flag_MULTIPLICATION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_INT;
		    return TYPE_INT;
		case flag_DIVISION:
		    typeCheckBinaryOperation(flag_DIVISION, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_INT;
		    return TYPE_INT;
		case flag_MOD:
		    typeCheckBinaryOperation(flag_MOD, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_INT;
		    return TYPE_INT;
		case flag_OR:
		    typeCheckBinaryOperation(flag_OR, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_BOOL);
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		case flag_AND:
		    typeCheckBinaryOperation(flag_AND, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_BOOL);
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		case flag_RETURN:
		    typeCheck(node->lSide); // typeCheck(leftSide(node));
		    break;
		case flag_ASSIGNMENT:
		    typeCheckAssignment(typeCheck(node->lSide), typeCheck(node->rSide), node->symbol->name);
		    break;
		case flag_SEMICOLON:
		    typeCheck(node->lSide);
		    typeCheck(node->rSide);
		    break;
		case flag_LT:
		    typeCheckBinaryOperation(flag_LT, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		case flag_GT:
		    typeCheckBinaryOperation(flag_GT, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_INT);
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		case flag_EQT:
		    typeCheckBinaryOperation(flag_EQT, typeCheck(node->lSide), typeCheck(node->rSide), TYPE_IDC);
		    node->symbol->type = TYPE_BOOL;
		    return TYPE_BOOL;
		case flag_MINUS:
		    typeCheckUnaryOperation(flag_MINUS, typeCheck(node->lSide), TYPE_INT);
		    node->symbol->type = TYPE_INT;
		    return TYPE_INT;
		case flag_NEG:
		    typeCheckUnaryOperation(flag_NEG, typeCheck(node->lSide), TYPE_BOOL);
		    node->symbol->type = TYPE_BOOL;
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
		    block  = node->lSide;
		    returnType = node->symbol->type;
		    checkMethodDeclaration(block, returnType, node->symbol->name);
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
