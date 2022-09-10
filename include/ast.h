#ifndef AST_H
#define AST_H
#include "symbol.h"

typedef struct astNode{
    Symbol* symbol;
    struct astNode* lSide;
    struct astNode* mSide;
    struct astNode* rSide;
} ASTNode;

/* The 'node' function constructs a node (leaf) from a reference to a symbol and returns the node. */
ASTNode* node(Symbol* symbol);

/* The 'composeTree' functions constructs a new tree from: 
 * Flag flag, const char* name: symbol information for the root. 
 * ASTNode* lSide: left side of the resulting tree.
 * ASTNode* mSide: mid side of the resulting tree.
 * ASTNode* rSide: right side of the resulting tree.
 *
 * It returns the root of the new tree. */
ASTNode* composeTree(Flag flag, const char* name, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide);

/* The 'typeCheck' function performs the type check of the AST. */
Type typeCheck(ASTNode* node);

int evaluate(ASTNode* node);

/* The 'printAST' function prints the elements of the AST to the stdout. */
void printAST(ASTNode* root);
#endif
