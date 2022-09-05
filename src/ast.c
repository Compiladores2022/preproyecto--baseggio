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
