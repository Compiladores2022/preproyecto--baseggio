%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <ast.h>

SymbolTable symbolTable;

int yylex();
void yyerror(const char* s);
%}

%union { int i; char* s; struct astNode* n; enum type t }

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
%type <n> Declaration
%type <n> Statement
%type <n> E
%type <n> V
%type <t> Type

%left '+'
%left '-'
%left '*'
%left '/'
%left '%'

%right '='

%left OR
%left AND
%right '!'

%left '<'
%left '>'
%left EQT

%%

program:{ constructSymbolTable(&symbolTable); }  PROGRAM '{' lDeclarations MethodDeclarations '}' ;

lDeclarations: { $$ = NULL; } 
	     | lDeclarations Declaration
             ;

MethodDeclarations: 
		  | MethodDeclaration MethodDeclarations
                  ;

MethodDeclaration: Method Block
		 | Method EXTERN ';'
                 ;

Method: VOID ID '(' Params ')'
      | Type ID '(' Params ')'
      ;

Params: 
      | OneOrMoreParams
      ;

OneOrMoreParams : Param
		| Param ',' OneOrMoreParams
                ;

Param: Type ID ;

Block: '{' lDeclarations lStatements '}' ;

lStatements: { $$ = NULL; }
	   | lStatements Statement
           ;

Statement: ID '=' E ';' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
	                  ASTNode* lSide = node(symbol);
                          $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $3);
	                }
	 | E ';'                               { $$ = $1; }
         | IF '(' E ')' THEN Block             { $$ = NULL; }
         | IF '(' E ')' THEN Block ELSE Block  { $$ = NULL; }
         | WHILE E Block                       { $$ = NULL; }
         | RETURN ';'                          { $$ = NULL; }
         | RETURN E ';'                        { $$ = NULL; }
         | ';'                                 { $$ = NULL; }
         | Block                               { $$ = NULL; }
         ;

Declaration: Type ID '=' E ';' { Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, $1, $2, 0); 
	                         if(addSymbol(&symbolTable, symbol)) {
                                   printf("var added\n");
				 } else {
                                   printf("Redeclared var\n");
                                   exit(EXIT_FAILURE);
				 }
                               }

E: ID         { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1); 
                ASTNode* n = node(symbol);
                $$ = n;
              }
 | MethodCall { $$ = NULL; }
 | V          { $$ = $1; }
 | E '+' E    { $$ = NULL; }
 | E '-' E    { $$ = NULL; }
 | E '*' E    { $$ = NULL; }
 | E '/' E    { $$ = NULL; }
 | E '%' E    { $$ = NULL; }
 | E '<' E    { $$ = NULL; }
 | E '>' E    { $$ = NULL; }
 | E EQT E    { $$ = NULL; }
 | E OR  E    { $$ = NULL; }
 | E AND E    { $$ = NULL; }
 | '-' E      { $$ = NULL; }
 | '!' E      { $$ = NULL; }
 | '(' E ')'  { $$ = $2; }
 ;

V: vINT {  char* name = (char*) malloc(sizeof(char));
           sprintf(name, "%d", $1);
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, name, $1));
           $$ = n;
        }
 | vBOOL { char* name = (char*) malloc(sizeof(char));
           sprintf(name, "%d", $1);
           ASTNode* n = node(constructPtrToSymbol(flag_VALUE_BOOL, TYPE_BOOL, name, $1));
           $$ = n;
         }
 ;

Expressions:
	   | OneOrMoreExpressions
           ;

OneOrMoreExpressions: E
		    | E ',' OneOrMoreExpressions
                    ;

Type : tINT  { $$ = $1; }
     | tBOOL { $$ = $1; }
     ;

MethodCall: ID '(' Expressions ')' { checkIdentifierIsDeclared(symbolTable, $1); }

%%
