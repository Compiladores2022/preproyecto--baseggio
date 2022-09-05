#ifndef AST_H
#define AST_H
#include "symbol.h"

typedef struct astNode{
    Symbol* symbol;
    struct astNode* lSide;
    struct astNode* mSide;
    struct astNode* rSide;
} ASTNode;

ASTNode* node(Symbol* symbol);
void compose(ASTNode* root, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide);
void showAST(ASTNode* root);
#endif
