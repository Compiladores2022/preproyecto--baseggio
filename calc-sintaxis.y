%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbolTable.h"
#include "ast.h"
#include "threeAddressCode.h"

int offset = 8;
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
                   generateIntermediateCode($1, &threeAddressCode, &offset);
                   //showThreeAddressCode(threeAddressCode); 
                   generateAssembler(threeAddressCode, symbolTable);
                   
                 }
    | lDeclarations lSentences { ASTNode* root = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); 
                                 typeCheck(root); 
                                 generateIntermediateCode(root, &threeAddressCode, &offset); 
                                 //showThreeAddressCode(threeAddressCode);
                                 generateAssembler(threeAddressCode, symbolTable);
                               }
    ;
    
lDeclarations: Declaration               { $$ = $1; }
             | Declaration lDeclarations { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
             ;

Declaration: Type ID '=' E ';' { Symbol* symbol = constructPtrToSymbol(flag_IDENTIFIER, $1, $2, 0);
                                 symbol->offset = offset;
                                 printf("%s offset: %d\n", $2, offset);
                                 offset += 8;
                                 if(addSymbol(&symbolTable, symbol)) {
                                     ASTNode* lSide = node(symbol);
                                     $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $4);
                                 } else {
                                     printf("Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 }
                               }
           ;
             
lSentences: Sentence            { $$ = $1; }
          | Sentence lSentences { $$ = composeTree(flag_SEMICOLON, ";", $1, NULL, $2); }
          ;
          
Sentence: E ';'        { $$ = $1; }
	| ID '=' E ';' { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
                         ASTNode* lSide = node(symbol);
                         $$ = composeTree(flag_ASSIGNMENT, "=", lSide, NULL, $3);
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

V : vINT  { char* name = (char*) malloc(sizeof(char));
            sprintf(name, "%d", $1);
            ASTNode* n = node(constructPtrToSymbol(flag_VALUE_INT, TYPE_INT, name, $1));
            $$ = n; }
            
  | vBOOL { char* name = (char*) malloc(sizeof(char));
            sprintf(name, "%d", $1);
            ASTNode* n = node(constructPtrToSymbol(flag_VALUE_BOOL, TYPE_BOOL, name, $1));
            $$ = n; 
          }
            
  | ID    { Symbol* symbol = checkIdentifierIsDeclared(symbolTable, $1);
            ASTNode* n     = node(symbol);
            $$ = n;
	  }
  ;

Type : tINT  { $$ = $1; }
     | tBOOL { $$ = $1; }
     ;
%%
