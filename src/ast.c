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

Ast emptyTree() {
  Ast ast;
  ast.root = NULL;
  return ast;
}

Ast compose(ASTNode* root, Ast lSide, Ast mSide, Ast rSide) {
    Ast ast;
    root->lSide = lSide.root;
    root->mSide = mSide.root;
    root->rSide = rSide.root;
    ast.root = root;
    return ast;
}

Ast leaf(Symbol* symbol) {
    return compose(node(symbol), emptyTree(), emptyTree(), emptyTree());
}

void showASTNodes(ASTNode* node) {
    if(node) {
	printf("root: ");
        showSymbol(*node->symbol);
	if (node->lSide) printf("left side: ");
	showASTNodes(node->lSide);
	if (node->mSide) printf("mid side: ");
	showASTNodes(node->mSide);
	if (node->rSide) printf("right side: ");
	showASTNodes(node->rSide);
    }
}

void showAST(Ast ast)
{
    printf("Tree: \n");
    showASTNodes(ast.root);
}
