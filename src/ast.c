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

void showFlag(Flag flag){
    switch ( flag ) {
	    case IDENTIFIER :
		  printf("ID");
		  break;
	    case ADDITION :
		  printf("+");
		  break;
	    case MULTIPLICATION :
		  printf("*");
		  break;
	    case OP_OR :
		  printf("||");
		  break;
	    case OP_AND :
		  printf("&&");
		  break;
	    case ASSIGNMENT: 
		  printf("=");
		  break;
	    case SEMICOLON :
		  printf(";");
		  break;
	    case VALUE_INT :
		  printf("vInt");
		  break;
	    case VALUE_BOOL :
		  printf("vBool");
		  break;
	    case RETURN :
		  printf("return");
		  break;
	    default :
		  break;
    }
}

void showAST(ASTNode* root) {
    if(root) {
        showFlag(root->symbol->flag);
	printf("\n");
        printf("left side: ");
        showAST(root->lSide);
        printf("mid side: ");
        showAST(root->mSide);
        printf("right side: ");
        showAST(root->rSide);
    } else {
       printf("_");
    }
}

int isLeave(ASTNode* node) {
    return !node->lSide && !node->mSide && !node->rSide;
}

int isBinaryOperator(Symbol* symbol) {
    return symbol->flag = ADDITION || symbol->flag == MULTIPLICATION || symbol->flag == OP_OR || symbol->flag == OP_AND || symbol->flag == ASSIGNMENT;
}

Type typeCheck(ASTNode* node) {
    if(node) {
        if(isLeave(node)) { return node->symbol->type; }
        
        if(isBinaryOperator(node->symbol)) {
            Flag operator = node->symbol->flag;
            Type lSideType = typeCheck(node->lSide);
            Type rSideType = typeCheck(node->rSide);
            if(operator == ADDITION || operator == MULTIPLICATION) {
                if( (lSideType == rSideType) == TYPE_INT) {
                    node->symbol->type = TYPE_INT;
                    printf("Hi.\n");
                    return node->symbol->type;
                } else {
                    printf("ERROR\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            if(operator == OP_OR || operator == OP_AND) {
                if( (lSideType == rSideType) == TYPE_BOOL) {
                    node->symbol->type = TYPE_BOOL;
                    return node->symbol->type;
                } else {
                    printf("ERROR");
                    exit(EXIT_FAILURE);
                }
            }
            
            if(operator == ASSIGNMENT) {
                if(!(lSideType == rSideType)) {
                    printf("ERROR");
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        if(node->symbol->flag == RETURN) {
            return typeCheck(node->lSide);
        }
        
        if(node->symbol->flag == SEMICOLON) {
            typeCheck(node->lSide);
            typeCheck(node->rSide);
        }
    }
    
    return 0;
}
