%{

#include <stdio.h>

int yylex();
void yyerror(const char* s);
%}

%token PROGRAM
%token IF
%token THEN
%token ELSE
%token RETURN
%token EXTERN
%token WHILE
%token ID
%token vINT
%token vBOOL
%token tINT
%token tBOOL
%token VOID
%token OR
%token AND

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

program: PROGRAM '{' lDeclarations MethodDeclarations '}' ;

lDeclarations: 
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

lStatements: 
	   | lStatements Statement
           ;

Statement: ID '=' E ';'
	 | MethodCall ';'
         | IF '(' E ')' THEN Block
         | IF '(' E ')' THEN Block ELSE Block
         | WHILE E Block
         | RETURN ';'
         | RETURN E ';'
         | Block
         ;

Declaration: Type ID '=' E ';' ;

E: ID
 | MethodCall 
 | V
 | E '+' E
 | E '-' E
 | E '*' E
 | E '/' E
 | E '%' E
 | E '<' E
 | E '>' E
 | E EQT E
 | E OR  E
 | E AND E
 | '-' E
 | '!' E
 | '(' E ')'
 ;

V: vINT
 | vBOOL
 ;

Expressions: 
	   | OneOrMoreExpressions
           ;

OneOrMoreExpressions: E
		    | E ',' OneOrMoreExpressions
                    ;

Type : tINT
     | tBOOL
     ;

MethodCall: ID '(' Expressions ')' ;

%%
