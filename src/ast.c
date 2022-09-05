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
