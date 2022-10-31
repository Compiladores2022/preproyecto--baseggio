#ifndef AST_H
#define AST_H
#include "symbol.h"
#include "symbolTable.h"

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

/* The 'semanticCheck' function performs the semantic analysis of the AST. */
void semanticCheck(ASTNode* node, SymbolTable symbolTable);

/* The 'evaluate' functions evaluates the AST. */
int evaluate(ASTNode* node);

/* The 'getSymbol' function returns the Symbol associated with this node. */
Symbol* getSymbol(ASTNode* node);

/* The 'getLSide' function returns the Left Side associated with this node. */
ASTNode* getLSide(ASTNode* node);

/* The 'getLSide' function returns the Middle Side associated with this node. */
ASTNode* getMSide(ASTNode* node);

/* The 'getLSide' function returns the Right Side associated with this node. */
ASTNode* getRSide(ASTNode* node);

/* The 'setLSide' function associates an AST to the node as the Left Side */
void setLSide(ASTNode* node, ASTNode* lSide);

/* The 'setLSide' function associates an AST to the node as the Middle Side */
void setMSide(ASTNode* node, ASTNode* mSide);

/* The 'setLSide' function associates an AST to the node as the Right Side */
void setRSide(ASTNode* node, ASTNode* rSide);

/* The 'printAST' function prints the elements of the AST to the stdout. */
void printAST(ASTNode* root);

/* The 'isLeave' function return TRUE iff the node has no children. */
int isLeave(ASTNode* node);

/* The 'expressionIsOnlyFormedByConstants' returns TRUE iff the AST is only formed by constants in its base nodes. */
int expressionIsOnlyFormedByConstants(ASTNode* node);
#endif
