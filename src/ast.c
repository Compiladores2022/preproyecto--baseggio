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

int checkReturn(ASTNode* node, Type expected) {
    if(node) {
        Flag flag = node->symbol->flag;
        if(flag == flag_RETURN) {
            Type returnType = typeCheck(node->lSide);
            if(returnType == expected) {
                return TRUE;
            } else {
                printf("%s was expected in return statement\n", typeToString(expected));
		exit(EXIT_FAILURE);
            }
        } else {
            return checkReturn(node->lSide, expected) || checkReturn(node->mSide, expected) || checkReturn(node->rSide, expected);
        }
    }
    
    return FALSE;
}

void checkParams(Symbol* fParams, ASTNode* rParams) {
    if(fParams && rParams) {
        Type typeOfTheFParam = fParams->type;
        Type typeOfTheRParam = rParams->lSide->symbol->type;
        if(typeOfTheFParam != typeOfTheRParam) {
            printf("Formal param and real param does not match\n");
            exit(EXIT_FAILURE);
        }
        
        checkParams(fParams->params, rParams->rSide);
    } else if(fParams) {
        printf("few parameters");
        exit(EXIT_FAILURE);
    } else if(rParams) {
        printf("many parameters");
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
	    
	    if(flag == flag_LT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_INT, flag);
		return TYPE_BOOL;
	    }
	    
	    if(flag == flag_GT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		reportErrorIfExists(typeOfTheFstOperand, typeOfTheSndOperand, TYPE_INT, flag);
		return TYPE_BOOL;
	    }
	    
	    if(flag == flag_EQT) {
	        Type typeOfTheFstOperand = typeCheck(node->lSide);
		Type typeOfTheSndOperand = typeCheck(node->rSide);
		if(typeOfTheFstOperand == typeOfTheSndOperand) {
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
	    	    return typeOfTheFstOperand;
	    	} else {
	    	    printf("Bool expression was expected.\n");
		    exit(EXIT_FAILURE);
	    	}
	    	
	    	typeCheck(node->rSide);
	    }
	    
	    if(flag == flag_METHOD_DECLARATION) {
		int isExtern      = node->lSide == NULL;
		int hasReturnType = node->symbol->type != TYPE_VOID;
		ASTNode* block          = node->lSide;
		Type expectedReturnType = node->symbol->type;
		if(hasReturnType && !isExtern && !checkReturn(block, expectedReturnType)) {
		    printf("return statement is missing in %s function.\n", node->symbol->name);
		    exit(EXIT_FAILURE);
		}
		
		typeCheck(block);
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
