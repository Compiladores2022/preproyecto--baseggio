%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "threeAddressCode.h"
#include "assemblerGenerator.h"
#include "ast.h"
#include "list.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

SymbolTable symbolTable;
ThreeAddressCode threeAddressCode;

int yylex();
void yyerror(const char* s);
char* expressionToString(ASTNode* node);
void checkIsNotAFunction(Symbol symbol);
void freeOffsetsInCurentLevel(SymbolTable symbolTable, ThreeAddressCode* threeAddressCode);
void addParametersToSymbolTable(SymbolTable* symbolTable, Symbol* symbol, ThreeAddressCode* threeAddressCode);
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

program:{ SymbolTable_construct(&symbolTable);
       	  ThreeAddressCode_construct(&threeAddressCode);
        }  PROGRAM '{' lDeclarations MethodDeclarations '}' { 
        ASTNode* root = composeTree(flag_SEMICOLON, ";", $4, NULL, $5);
	semanticCheck(root, symbolTable);
        generateIntermediateCode(root, &threeAddressCode);
	//ThreeAddressCode_print(threeAddressCode);
        generateAssembler(threeAddressCode);
} ;

lDeclarations: { $$ = NULL; } 
	     | lDeclarations Declaration { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
             ;

MethodDeclarations: { $$ = NULL; }
		  | MethodDeclaration MethodDeclarations { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
                  ;

MethodDeclaration: Method 
                   { ThreeAddressCode_construct(&threeAddressCode);
		     SymbolTable_openLevel(&symbolTable);
                     Symbol* symbol = $1;
                     addParametersToSymbolTable(&symbolTable, getParams(*symbol), &threeAddressCode);
                   }
                   Block
                   { SymbolTable_closeLevel(&symbolTable);
		     setOffset($1, threeAddressCode.offset);
                     ASTNode* n = node($1);
                     setLSide(n, $3);
                     $$ = n; }
		 | Method EXTERN ';' { ASTNode* n = node($1);
		                       $$ = n; }
                 ;

Method: VOID ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, TYPE_VOID, $2, 0);
				 SymbolTable_add(&symbolTable, symbol);
				 symbol->isFunction = TRUE;
                                     
				if (strcmp(getName(*symbol), "main") != 0) {
					symbol->params = $4;
				}
				$$ = symbol;
                               }
      | Type ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, $1, $2, 0);
      				 SymbolTable_add(&symbolTable, symbol);
      				 symbol->isFunction = TRUE;
                                     
				 if (strcmp(getName(*symbol), "main") != 0) {
					 symbol->params = $4;
				 }
				 $$ = symbol;
      				}
      ;

Params:                 { $$ = NULL; }
      | OneOrMoreParams { $$ = $1;   }
      ;

OneOrMoreParams : Param                     { $$ = $1; }
		| Param ',' OneOrMoreParams { Symbol* symbol = $1;
                                              setParams(symbol, $3);
                                              $$ = symbol; }
                ;

Param: Type ID { Symbol* symbol = constructPtrToSymbol(flag_PARAM, $1, $2, 0);
                 $$ = symbol; } ;

Block: { SymbolTable_openLevel(&symbolTable); } '{' lDeclarations lStatements '}' 
       { freeOffsetsInCurentLevel(symbolTable, &threeAddressCode);
         SymbolTable_closeLevel(&symbolTable);
         $$ = composeTree(flag_SEMICOLON, ";", $3, NULL, $4); } ;

lStatements: { $$ = NULL; }
	   | lStatements Statement { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
           ;

Statement: ID '=' E ';' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
			  checkIsNotAFunction(*symbol);
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

Declaration: Type ID '=' E ';' { if(SymbolTable_levels(symbolTable) == 1 
				&& !expressionIsOnlyFormedByConstants($4)) {
					printf("error: initializer element is not constant\n");
					printf("%s %s = %s\n", typeToString($1), $2, expressionToString($4));
					exit(EXIT_FAILURE);
				} 
				
				Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, $1, $2, 0); 
				symbol->global = SymbolTable_levels(symbolTable) == 1;
				SymbolTable_add(&symbolTable, symbol);
				ASTNode* lSide = node(symbol);	
				if(isGlobal(*symbol)) {
					$$ = composeTree(flag_GLOBAL_VAR_DECL, "=", lSide, NULL, $4);                        	
				} else {
					assignOffset(symbol, &threeAddressCode);
					$$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $4);
				}
                               }
           ;

E: ID                 { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1); 
			checkIsNotAFunction(*symbol);
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
 | '-' E %prec UMINUS { Symbol* zero = constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, "0", 0);
 			ASTNode* lSide = node(zero);
 			$$ = propagationOfConstants(flag_SUBSTRACTION,   flag_VALUE_INT,  TYPE_INT,  "-",  lSide, $2); }
 | '!' E              { $$ = propagationOfConstants(flag_NEG,            flag_VALUE_BOOL, TYPE_BOOL, "!",  $2, NULL); }
 | '(' E ')'          { $$ = $2; }
 ;

V: vINT {  char* name = allocateChar(32);
           snprintf(name, sizeof(int), "%d", $1);
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, name, $1));
           $$ = n; }
 | vBOOL { char* name = allocateChar(32);
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

char* expressionToString(ASTNode* node) {
	if(node) {
		if(isLeave(node)) { return getName(*getSymbol(node)); }
		Flag flag = getFlag(*getSymbol(node));
		char* fstOperand = allocateChar(32);
		char* sndOperand = allocateChar(32);
		char* result = allocateChar(32);
		if(isABinaryOperator(flag)) {
			strcpy(fstOperand, expressionToString(getLSide(node)));
			strcpy(sndOperand, expressionToString(getRSide(node)));
			sprintf(result, "%s %s %s", fstOperand, flagToString(flag), sndOperand);
		} else { 
			strcpy(fstOperand, expressionToString(getLSide(node)));
			sprintf(result, "%s %s", flagToString(flag), fstOperand);		
		}
		return result;
	}
	
	return NULL;
}

void checkIsNotAFunction(Symbol symbol) {
	if(isFunction(symbol)) {
		printf("ERROR: %s is a function.\n", getName(symbol));
		exit(EXIT_FAILURE);
	}
}

void freeOffsetsInCurentLevel(SymbolTable symbolTable, ThreeAddressCode* threeAddressCode) {
	int i = 0;
	int length = currentLevelLength(symbolTable);
	int offset;
	while(i < length) {
		offset = getOffset(*SymbolTable_getByIndex(symbolTable, i));
		//Symbol* symbol = SymbolTable_getByIndex(symbolTable, i);
		//printf("%s OFFSET: %d\n", getName(*symbol), getOffset(*symbol));
		add(&threeAddressCode->freeOffsets, &offset, sizeof(int), FALSE);
		i++;
	}
}

void addParametersToSymbolTable(SymbolTable* symbolTable, Symbol* symbol, ThreeAddressCode* threeAddressCode) {
    if(symbol) {
    	assignOffset(symbol, threeAddressCode);
        SymbolTable_add(symbolTable, symbol);
        addParametersToSymbolTable(symbolTable, getParams(*symbol), threeAddressCode);
    }
}
