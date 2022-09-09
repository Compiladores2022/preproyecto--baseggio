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
ASTNode* composeTree(Flag flag, const char* name, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide);
Type typeCheck(ASTNode* node);
void showAST(ASTNode* root);
#endif
