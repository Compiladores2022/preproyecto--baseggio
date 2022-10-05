%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "ast.h"
#include "queue.h"

#define TRUE 1
#define FALSE 0

SymbolTable symbolTable;

int yylex();
void yyerror(const char* s);
void addAll(SymbolTable* symbolTable, Symbol* symbol);
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

%left '+'
%left '-'
%left '*'
%left '/'
%left '%'
%right UMINUS

%right '='

%left OR
%left AND
%right '!'

%left '<'
%left '>'
%left EQT

%%

program:{ constructSymbolTable(&symbolTable); }  PROGRAM '{' lDeclarations MethodDeclarations '}' { 
        ASTNode* root = composeTree(flag_SEMICOLON, ";", $4, NULL, $5);
        typeCheck(root);
        //printAST(root);
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
                     addAll(&symbolTable, symbol->params);
                   }
                   Block  
                   { closeLevel(&symbolTable);
                     ASTNode* n = node($1);
                     n->lSide = $3;
                     $$ = n;
                   }
		 | Method EXTERN ';' { ASTNode* n = node($1);
		                       $$ = n;
		                     }
                 ;

Method: VOID ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, TYPE_VOID, $2, 0);
                                 if(addSymbol(&symbolTable, symbol)) {
                                     symbol->isFunction = TRUE;
                                     symbol->params = $4;
                                     $$ = symbol;
                                 } else {
                                     printf("Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 }
                               }
      | Type ID '(' Params ')' { Symbol* symbol = constructPtrToSymbol(flag_METHOD_DECLARATION, $1, $2, 0);
                                 if(addSymbol(&symbolTable, symbol)) {
                                     symbol->isFunction = TRUE;
                                     symbol->params = $4;
                                     $$ = symbol;
                                 } else {
                                     printf("Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 }
                               }
      ;

Params:                 { $$ = NULL; }
      | OneOrMoreParams { $$ = $1;   }
      ;

OneOrMoreParams : Param                     { $$ = $1; }
		| Param ',' OneOrMoreParams { Symbol* symbol = $1;
                                              symbol->params = $3;
                                              $$ = symbol;
                                            }
                ;

Param: Type ID { Symbol* symbol = constructPtrToSymbol(flag_PARAM, $1, $2, 0);
                 $$ = symbol;
               } ;

Block: { openLevel(&symbolTable); } '{' lDeclarations lStatements '}' 
       { closeLevel(&symbolTable); $$ = composeTree(flag_SEMICOLON, ";", $3, NULL, $4); } ;

lStatements: { $$ = NULL; }
	   | lStatements Statement { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
           ;

Statement: ID '=' E ';' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
	                  ASTNode* lSide = node(symbol);
                          $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $3);
	                }
	 | E ';'                               { $$ = $1; }
         | IF '(' E ')' THEN Block             { $$ = composeTree(flag_IF, "if-then", $3, NULL, $6); }
         | IF '(' E ')' THEN Block ELSE Block  { $$ = composeTree(flag_IF_ELSE, "if-then-else", $3, $6, $8); }
         | WHILE E Block                       { $$ = composeTree(flag_WHILE, "while", $2, NULL, $3); }
         | RETURN ';'                          { $$ = composeTree(flag_RETURN, "return", NULL, NULL, NULL); }
         | RETURN E ';'                        { $$ = composeTree(flag_RETURN, "return", $2, NULL, NULL); }
         | ';'                                 { $$ = composeTree(flag_SEMICOLON, ";", NULL, NULL, NULL); }
         | Block                               { $$ = $1; }
         ;

Declaration: Type ID '=' E ';' { Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, $1, $2, 0); 
	                         if(addSymbol(&symbolTable, symbol)) {
                                   ASTNode* lSide = node(symbol);
                                   $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $4);
				 } else {
                                   printf("Redeclared var\n");
                                   exit(EXIT_FAILURE);
				 }
                               }
           ;

E: ID         { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1); 
                ASTNode* n = node(symbol);
                $$ = n;
              }
 | MethodCall { $$ = $1; }
 | V          { $$ = $1; }
 | E '+' E    { $$ = composeTree(flag_ADDITION,       "+",  $1, NULL, $3);   }
 | E '-' E    { $$ = composeTree(flag_SUBSTRACTION,   "-",  $1, NULL, $3);   }
 | E '*' E    { $$ = composeTree(flag_MULTIPLICATION, "*",  $1, NULL, $3);   }
 | E '/' E    { $$ = composeTree(flag_DIVISION,       "/",  $1, NULL, $3);   }
 | E '%' E    { $$ = composeTree(flag_MOD,            "%",  $1, NULL, $3);   }
 | E '<' E    { $$ = composeTree(flag_LT,             "<",  $1, NULL, $3);   }
 | E '>' E    { $$ = composeTree(flag_GT,             ">",  $1, NULL, $3);   }
 | E EQT E    { $$ = composeTree(flag_EQT,            "==", $1, NULL, $3);   }
 | E OR  E    { $$ = composeTree(flag_OR,             "||", $1, NULL, $3);   }
 | E AND E    { $$ = composeTree(flag_AND,            "&&", $1, NULL, $3);   }
 | '-' E %prec UMINUS      { $$ = composeTree(flag_MINUS,          "-",  $2, NULL, NULL); }
 | '!' E      { $$ = composeTree(flag_NEG,            "!",  $2, NULL, NULL); }
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

Expressions: { $$ = NULL; }
	   | OneOrMoreExpressions { $$ = $1; }
           ;

OneOrMoreExpressions: E { $$ = $1; }
		    | E ',' OneOrMoreExpressions { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $3); }
                    ;

Type : tINT  { $$ = $1; }
     | tBOOL { $$ = $1; }
     ;

MethodCall: ID '(' Expressions ')' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
	                             if(isFunction(*symbol)) {
	                                 symbol->flag = flag_METHOD_CALL;
                                         ASTNode* n = node(symbol);
                                         n->lSide = $3;
                                         $$ = n;
                                     } else {
                                         printf("%s is not a function\n", symbol->name);
                                         exit(EXIT_FAILURE);
                                     }
                                   } ;

%%

void addAll(SymbolTable* symbolTable, Symbol* symbol) {
    if(symbol) {
        addSymbol(symbolTable, symbol);
        addAll(symbolTable, symbol->params);
    }
}
