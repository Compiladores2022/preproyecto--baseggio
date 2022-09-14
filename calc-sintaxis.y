%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbolTable.h"
#include "ast.h"
#include "threeAddressCode.h"

SymbolTable symbolTable;
ThreeAddressCode threeAddressCode;
int yylex();
void yyerror(const char* s);
%}

%union { int i; char* s; struct astNode* n; enum type t }
 
%token <i> vINT
%token <i> vBOOL
%token <t> tINT
%token <t> tBOOL
%token <s> ID
%token OR
%token AND
%token RETURN 
%type <n> lDeclarations
%type <n> lSentences
%type <n> Declaration
%type <n> Sentence
%type <n> E
%type <n> V
%type <t> Type

%left '+'
%left '*'
%right '='
%left OR
%left AND

%%

setUp: { constructSymbolTable(&symbolTable); } prog

prog: lSentences { typeCheck($1);
                   generateIntermediateCode($1, &threeAddressCode);
                   showThreeAddressCode(threeAddressCode); }
    | lDeclarations lSentences { ASTNode* root = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); 
                                 typeCheck(root); 
                                 generateIntermediateCode(root, &threeAddressCode); 
                                 showThreeAddressCode(threeAddressCode); }
    ;
    
lDeclarations: Declaration               { $$ = $1; }
             | Declaration lDeclarations { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
             ;

Declaration: Type ID '=' E ';' { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
	                         symbol->name = (char*) malloc(sizeof(char));
                                 strcpy(symbol->name, $2);
                                 symbol->type = $1;
                                 if(lookUpSymbol(symbolTable, symbol->name)) {
                                     printf("ERROR: Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 } else {
                                     addSymbol(&symbolTable, symbol);
                                     ASTNode* lSide = node(symbol);
                                     $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $4);
                                 }
                               }
           ;
             
lSentences: Sentence            { $$ = $1; }
          | Sentence lSentences { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
          ;
          
Sentence: E ';'        { $$ = $1; }
	| ID '=' E ';' { Symbol* symbol;
                         if((symbol = lookUpSymbol(symbolTable, $1)) == NULL) {
	                     printf("ERROR: Undeclared identifier: %s\n", $1);
	                     exit(EXIT_FAILURE);
	                 } else {
                             ASTNode* lSide = node(symbol);
                             $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $3);
                         }
	               }
        | RETURN E ';' { $$ = composeTree(flag_RETURN, "return", $2, NULL, NULL); }
        ;
  
E: V         { $$ = $1; }
 | E '+' E   { $$ = composeTree(flag_ADDITION, "+", $1, NULL, $3); }
 | E '*' E   { $$ = composeTree(flag_MULTIPLICATION, "*", $1, NULL, $3); }
 | E OR  E   { $$ = composeTree(flag_OR, "||", $1, NULL, $3); }
 | E AND E   { $$ = composeTree(flag_AND, "&&", $1, NULL, $3); }
 | '(' E ')' { $$ = $2; }
 ;

V : vINT  { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
            symbol->type  = TYPE_INT;
            symbol->flag  = flag_VALUE_INT;
            symbol->value = $1;
            ASTNode* n = node(symbol);
            $$ = n; }
            
  | vBOOL { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol)) ;
            symbol->type = TYPE_BOOL;
            symbol->flag = flag_VALUE_BOOL;
            symbol->value = $1;
            ASTNode* n = node(symbol);
            $$ = n; 
          }
            
  | ID    { Symbol* symbol;
            if((symbol = lookUpSymbol(symbolTable, $1))) {
	        ASTNode* n = node(symbol);
                $$ = n;
	    } else {
	        printf("ERROR: Undeclared identifier: %s\n", $1);
                exit(EXIT_FAILURE);
	    }
	  }
  ;

Type : tINT  { $$ = $1; }
     | tBOOL { $$ = $1; }
     ;
%%
