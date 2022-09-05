%{

#include <stdlib.h>
#include <stdio.h>
#include "symbolTable.h"
#include "ast.h"

SymbolTable symbolTable;
int yylex();
void yyerror(const char *s);
void contextCheck(char* name);

%}

%union { int i; char* s; struct astNode* n }
 
%token <i> vINT
%token <i> vBOOL
%token tINT
%token tBOOL
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

%left '+'
%left '*'
%right '='
%left OR
%left AND
 
%%
 
prog: lSentences     
    | { constructSymbolTable(&symbolTable); } lDeclarations lSentences
    ;
    
lDeclarations: Declaration
             | lDeclarations Declaration
             ;

Declaration: Type ID '=' E ';' { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
                               symbol->name = $2;
                               if(lookUpSymbol(symbolTable, symbol->name)) {
                                   printf("Identifier redeclared.\n");
                                   exit(EXIT_FAILURE);
                               } else {
                                   addSymbol(&symbolTable, symbol);
                               }
                             }
           ;
             
lSentences: Sentence
          | lSentences Sentence
          ;
          
Sentence: E ';'
	| ID '=' E ';' { if(lookUpSymbol(symbolTable, $1) == NULL) {
	                     printf("Identifier undeclared.\n");
	                     exit(EXIT_FAILURE);
	                 }  
	               }
        | RETURN E ';' { $$ = NULL; }
        ;
  
E: V         { $$ = $1; }
 | E '+' E   { $$ = NULL; }
 | E '*' E   { $$ = NULL; }
 | E OR  E   { $$ = NULL; }
 | E AND E   { $$ = NULL; }
 | '(' E ')' { $$ = $2; }
 ;

V : vINT  { Symbol symbol;
            symbol.flag  = VALUE_INT;
            symbol.value = $1;
            ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
            node->symbol = &symbol;
            $$ = node; }
            
  | vBOOL { Symbol symbol;
            symbol.flag = VALUE_BOOL;
            symbol.value = $1;
            ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
            node->symbol = &symbol;
            $$ = node; }
            
  | ID    { Symbol* symbol;
            if((symbol = lookUpSymbol(symbolTable, $1))) {
	        printf("Identifier undeclared.\n");
	        exit(EXIT_FAILURE);
	    } else {
	        ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
                node->symbol = &symbol;
                $$ = node;
	    }
	  }
  ;

Type : tINT
     | tBOOL
     ;
%%


