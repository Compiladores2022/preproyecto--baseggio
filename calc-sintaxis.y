%{

#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"

int yylex();
void yyerror(const char *s);

%}
 
%token vINT
%token vBOOL
%token tINT
%token tBOOL
%token ID
%token OR
%token AND
%token RETURN 
     
%left '+'
%left '*'
%right '='
%left OR
%left AND
 
%%
 
prog: lSentences     
    | lDeclarations lSentences
    ;
    
lDeclarations: Declaration
             | lDeclarations Declaration
             ;

Declaration: Type ID '=' expr ';' { Symbol symbol;
	                            symbol.name = "x";
                                    printf("%s\n", symbol.name); 
	                          }
           ;
             
lSentences: Sentence
          | lSentences Sentence
          ;
          
Sentence: expr ';'
	| ID '=' expr ';' { //printf("%s","assignment sentence "); 
                          }
        | RETURN expr ';' { //printf("%s","return sentence "); 
                          }
        ;
  
expr: Value
    | expr '+' expr
    | expr '*' expr
    | expr OR  expr
    | expr AND expr
    | '(' expr ')'
    ;

Value : vINT { //printf("%s", "vInt "); 
             }
      | vBOOL { //printf("%s", "vBool "); 
              }
      | ID { //printf("%s", "ID "); 
           }
      ;

Type : tINT { //printf("%s", "tInt ");
            }
     | tBOOL { //printf("%s", "tBool ");
             }
     ;
%%



