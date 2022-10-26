%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "threeAddressCode.h"
#include "assemblerGenerator.h"
#include "ast.h"
#include "queue.h"

#define TRUE 1
#define FALSE 0

int offset = 8;
int numberOfLabel = 0;
SymbolTable symbolTable;
ThreeAddressCode threeAddressCode;

int yylex();
void yyerror(const char* s);
void addAll(SymbolTable* symbolTable, Symbol* symbol);
ASTNode* propagationOfConstants(Flag operation, Flag constantFlag, Type type, const char* name, ASTNode* lSide, ASTNode* rSide);
%}

%union { int i; char* s; struct astNode* n; enum type t; struct symbol* sb; }

%token PROGRAM
%token IF
%token THEN
%token ELSE
%token RETURN
%token EXTERN
%token WHILE
%token <s> ID
%token <i> vINT
%token <i> vBOOL
%token <t> tINT
%token <t> tBOOL
%token VOID
%token OR
%token AND

%type <n> lDeclarations
%type <n> lStatements
%type <n> MethodDeclarations
%type <n> Expressions
%type <n> OneOrMoreExpressions
%type <n> Declaration
%type <n> Statement
%type <n> MethodDeclaration
%type <sb> Method
%type <n> MethodCall
%type <sb> Params
%type <sb> OneOrMoreParams
%type <sb> Param
%type <n> Block
%type <n> E
%type <n> V
%type <t> Type

%left OR
%left AND
%right '!'
%nonassoc '<'
%nonassoc '>'
%nonassoc EQT
%left '+'
%left '-'
%left '*'
%left '/'
%left '%'
%right UMINUS
%%

program:{ constructSymbolTable(&symbolTable); }  PROGRAM '{' lDeclarations MethodDeclarations '}' { 
        ASTNode* root = composeTree(flag_SEMICOLON, ";", $4, NULL, $5);

        Symbol* symbol = lookUpSymbol(symbolTable, "main");
        if(!(symbol && isFunction(*symbol))) {
            printf("main function not defined\n");
            exit(EXIT_FAILURE);
        }
        
        typeCheck(root);
        generateIntermediateCode(root, &threeAddressCode, &offset, &numberOfLabel);
        //showThreeAddressCode(threeAddressCode);
        generateAssembler(threeAddressCode);
} ;

lDeclarations: { $$ = NULL; } 
	           | lDeclarations Declaration { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
             ;

MethodDeclarations: { $$ = NULL; }
		              | MethodDeclaration MethodDeclarations { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
                  ;

MethodDeclaration: Method 
                   { openLevel(&symbolTable); 
                     Symbol* symbol = $1;
                     addAll(&symbolTable, symbol->params); }
                   Block  
                   { closeLevel(&symbolTable);
                     ASTNode* n = node($1);
                     setLSide(n, $3);
                     $$ = n; }
		 | Method EXTERN ';' { ASTNode* n = node($1);
		                       $$ = n; }
                 ;

Method: VOID ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, TYPE_VOID, $2, 0);
                                 if (addSymbol(&symbolTable, symbol)) {
                                     symbol->isFunction = TRUE;
                                     
                                     if (strcmp(getName(*symbol), "main") != 0) {
                                     	symbol->params = $4;
                                     }
                                     $$ = symbol;
                                 } else {
                                     printf("Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 } }
      | Type ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, $1, $2, 0);
                                 if(addSymbol(&symbolTable, symbol)) {
                                     symbol->isFunction = TRUE;
                                     
                                     if (strcmp(getName(*symbol), "main") != 0) {
                                     	symbol->params = $4;
                                     }
                                     $$ = symbol;
                                 } else {
                                     printf("Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 } }
      ;

Params:                 { $$ = NULL; }
      | OneOrMoreParams { $$ = $1;   }
      ;

OneOrMoreParams : Param                     { $$ = $1; }
		            | Param ',' OneOrMoreParams { Symbol* symbol = $1;
                                              symbol->params = $3;
                                              $$ = symbol; }
                ;

Param: Type ID { Symbol* symbol = constructPtrToSymbol(flag_PARAM, $1, $2, 0);
                 $$ = symbol; } ;

Block: { openLevel(&symbolTable); } '{' lDeclarations lStatements '}' 
       { closeLevel(&symbolTable); $$ = composeTree(flag_SEMICOLON, ";", $3, NULL, $4); } ;

lStatements: { $$ = NULL; }
	         | lStatements Statement { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
           ;

Statement: ID '=' E ';' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
			  if (isFunction(*symbol)) {
			  	printf("ERROR: %s is a function.\n", getName(*symbol));
			  	exit(EXIT_FAILURE);
			  }
	                  ASTNode* lSide = node(symbol);
                          $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $3); }
	 | E ';'                               { $$ = $1; }
         | IF '(' E ')' THEN Block             { $$ = composeTree(flag_IF, "if-then", $3, NULL, $6); }
         | IF '(' E ')' THEN Block ELSE Block  { $$ = composeTree(flag_IF_ELSE, "if-then-else", $3, $6, $8); }
         | WHILE E Block                       { $$ = composeTree(flag_WHILE, "while", $2, NULL, $3); }
         | RETURN ';'                          { 
         					Symbol* symbol = constructPtrToEmptySymbol();
         					setType(symbol, TYPE_VOID);
         					ASTNode* lSide = node(symbol);
         					$$ = composeTree(flag_RETURN, "return", lSide, NULL, NULL); }
         | RETURN E ';'                        { $$ = composeTree(flag_RETURN, "return", $2, NULL, NULL); }
         | ';'                                 { $$ = composeTree(flag_SEMICOLON, ";", NULL, NULL, NULL); }
         | Block                               { $$ = $1; }
         ;

Declaration: Type ID '=' E ';' {
				if(numberOfLevel(symbolTable) == 1 
				&& !expressionIsOnlyFormedByConstants($4)) {
					printf("error: initializer element is not constant\n");
					printf("%s %s = %s\n", typeToString($1), $2, getName(*getSymbol($4)));
					exit(EXIT_FAILURE);
				} 
				
				Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, $1, $2, 0); 
				symbol->global = numberOfLevel(symbolTable) == 1;
				
	                        if(addSymbol(&symbolTable, symbol)) {
                                	ASTNode* lSide = node(symbol);
                                	
                                	if(isGlobal(*symbol)) {
        					$$ = composeTree(flag_GLOBAL_VAR_DECL, "=", lSide, NULL, $4);                        	
                                	} else {
	                               		$$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $4);
                                	}
                                	
				} else {
                                	printf("Redeclared var\n");
                                	exit(EXIT_FAILURE);
				}
                               }
           ;

E: ID                 { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1); 
			if(isFunction(*symbol)) {
				printf("ERROR: %s is a function.\n", getName(*symbol));
				exit(EXIT_FAILURE);
			}
                        ASTNode* n = node(symbol);
                        $$ = n;  }
 | MethodCall         { $$ = $1; }
 | V                  { $$ = $1; }
 | E '+' E            { $$ = propagationOfConstants(flag_ADDITION,       flag_VALUE_INT,  TYPE_INT,  "+",  $1, $3); }
 | E '-' E            { $$ = propagationOfConstants(flag_SUBSTRACTION,   flag_VALUE_INT,  TYPE_INT,  "-",  $1, $3); }
 | E '*' E            { $$ = propagationOfConstants(flag_MULTIPLICATION, flag_VALUE_INT,  TYPE_INT,  "*",  $1, $3); }
 | E '/' E            { $$ = propagationOfConstants(flag_DIVISION,       flag_VALUE_INT,  TYPE_INT,  "/",  $1, $3); }
 | E '%' E            { $$ = propagationOfConstants(flag_MOD,            flag_VALUE_INT,  TYPE_INT,  "%",  $1, $3); }
 | E '<' E            { $$ = propagationOfConstants(flag_LT,             flag_VALUE_BOOL, TYPE_BOOL, "<",  $1, $3); }
 | E '>' E            { $$ = propagationOfConstants(flag_GT,             flag_VALUE_BOOL, TYPE_BOOL, ">",  $1, $3); }
 | E EQT E            { $$ = propagationOfConstants(flag_EQT,            flag_VALUE_BOOL, TYPE_BOOL, "==", $1, $3); }
 | E OR  E            { $$ = propagationOfConstants(flag_OR,             flag_VALUE_BOOL, TYPE_BOOL, "||", $1, $3); }
 | E AND E            { $$ = propagationOfConstants(flag_AND,            flag_VALUE_BOOL, TYPE_BOOL, "&&", $1, $3); }
 | '-' E %prec UMINUS { $$ = propagationOfConstants(flag_MINUS,          flag_VALUE_INT,  TYPE_INT,  "-",  $2, NULL); }
 | '!' E              { $$ = propagationOfConstants(flag_NEG,            flag_VALUE_BOOL, TYPE_BOOL, "!",  $2, NULL); }
 | '(' E ')'          { $$ = $2; }
 ;

V: vINT {  char* name = (char*) malloc(sizeof(char));
           snprintf(name, sizeof(int), "%d", $1);
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, name, $1));
           $$ = n; }
 | vBOOL { char* name = (char*) malloc(sizeof(char));
           snprintf(name, sizeof(int), "%d", $1);
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_BOOL, TYPE_BOOL, name, $1));
           $$ = n; }
 ;

Expressions: { $$ = NULL; }
	         | OneOrMoreExpressions { $$ = $1; }
           ;

OneOrMoreExpressions: E { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, NULL); }
		                | E ',' OneOrMoreExpressions { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $3); }
                    ;

Type : tINT  { $$ = $1; }
     | tBOOL { $$ = $1; }
     ;

MethodCall: ID '(' Expressions ')' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
	                             int isAFunction = isFunction(*symbol);
	                             if(isAFunction) {
                                     	symbol = copy(symbol);
                                     	setFlag(symbol, flag_METHOD_CALL);
                                     	ASTNode* n = node(symbol);
                                     	setLSide(n, $3);
                                     	$$ = n;
                                     } else {
                                       	printf("%s is not a function\n", symbol->name);
                                     	exit(EXIT_FAILURE);
                                     } } ;

%%

void addAll(SymbolTable* symbolTable, Symbol* symbol) {
    if(symbol) {
        addSymbol(symbolTable, symbol);
        addAll(symbolTable, symbol->params);
    }
}

ASTNode* propagationOfConstants(Flag operation, Flag constantFlag, Type type, const char* name, ASTNode* lSide, ASTNode* rSide) {
	int lSideIsOnlyFormedByConstants = expressionIsOnlyFormedByConstants(lSide);
	int rSideIsOnlyFormedByConstants = expressionIsOnlyFormedByConstants(rSide);
	if (lSide && lSideIsOnlyFormedByConstants) {
		setFlag(getSymbol(lSide), constantFlag);
		setValue(getSymbol(lSide), evaluate(lSide));
	}
	
	if (rSide && rSideIsOnlyFormedByConstants) {
		setFlag(getSymbol(rSide), constantFlag);
		setValue(getSymbol(rSide), evaluate(rSide));
	}
	
	ASTNode* result = composeTree(operation, name, lSide, NULL, rSide);
	
	if(lSideIsOnlyFormedByConstants && rSideIsOnlyFormedByConstants) {
		Symbol* expression = constructPtrToEmptySymbol();
		setFlag(expression, constantFlag);
		setType(expression, type);
		setValue(expression, evaluate(result));
		result = node(expression);
	}
	
	return result;
}
