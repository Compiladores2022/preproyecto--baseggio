#ifndef AST_H
#define AST_H
#include "symbol.h"

typedef struct astNode{
    Symbol* symbol;
    struct astNode* lSide;
    struct astNode* mSide;
    struct astNode* rSide;
} ASTNode;

typedef struct {
    ASTNode* root;
} Ast;

ASTNode* node(Symbol* symbol);
Ast emptyTree();
Ast compose(ASTNode* root, Ast lSide, Ast mSide, Ast rSide);
Ast leaf(Symbol* symbol);
void showAST(Ast ast);
#endif
