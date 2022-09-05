%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symbolTable.h"
#include "ast.h"

SymbolTable symbolTable;
int yylex();
void yyerror(const char *s);
void contextCheck(char* name);
ASTNode* tree(Flag, Type, int, const char*, ASTNode*, ASTNode*, ASTNode*);

%}

%union { int i; char* s; struct astNode* n }
 
%token <i> vINT
%token <i> vBOOL
%token tINT
%token tBOOL
%token <s> ID
%token TOKEN_OR
%token TOKEN_AND
%token TOKEN_RETURN 

%type <n> prog
%type <n> lDeclarations
%type <n> lSentences
%type <n> Declaration
%type <n> Sentence
%type <n> E
%type <n> V

%left '+'
%left '*'
%right '='
%left TOKEN_OR
%left TOKEN_AND
 
%%
 
prog: { constructSymbolTable(&symbolTable); } lSentences { $$ = $2; //showAST($$); 
    }
    | { constructSymbolTable(&symbolTable); } lDeclarations lSentences { $$ = tree(SEMICOLON, 0, 0, ";", $2, NULL, $3); showAST($$); 
}
    ;
    
lDeclarations: Declaration               { $$ = $1; }
             | Declaration lDeclarations { $$ = tree(SEMICOLON, 0, 0, ";", $1, NULL, $2); }
             ;

Declaration: Type ID '=' E ';' { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
	                         symbol->name = (char*) malloc(sizeof(char));
                                 strcpy(symbol->name, $2);
                                 if(lookUpSymbol(symbolTable, symbol->name)) {
                                     printf("ERROR: Redeclared identifier: %s\n", $2);
                                     exit(EXIT_FAILURE);
                                 } else {
                                     addSymbol(&symbolTable, symbol);
                                     ASTNode* lSide = node(symbol);
                                     $$ = tree(ASSIGNMENT, 0, 0, "=", lSide, NULL, $4);
                                 }
                               }
           ;
             
lSentences: Sentence            { $$ = $1; 
	  }
          | Sentence lSentences { $$ = tree(SEMICOLON, 0, 0, ";", $1, NULL, $2); 
}
          ;
          
Sentence: E ';'        { $$ = $1; 
	}
	| ID '=' E ';' { Symbol* symbol;
                         if((symbol = lookUpSymbol(symbolTable, $1)) == NULL) {
	                     printf("ERROR: Undeclared identifier: %s\n", $1);
	                     exit(EXIT_FAILURE);
	                 } else {
                             ASTNode* lSide = node(symbol);
                             $$ = tree(ASSIGNMENT, 0, 0, "=", lSide, NULL, $3);
                         }
	               }
        | TOKEN_RETURN E ';' { $$ = tree(RETURN, 0, 0, "return", $2, NULL, NULL); 
}
        ;
  
E: V         { $$ = $1;                                            
 }
 | E '+' E   { $$ = tree(ADDITION, 0, 0, "+", $1, NULL, $3);       
}
 | E '*' E   { $$ = tree(MULTIPLICATION, 0, 0, "*", $1, NULL, $3); 
}
 | E TOKEN_OR  E   { $$ = tree(OP_OR, 0, 0, "||", $1, NULL, $3);          
}
 | E TOKEN_AND E   { $$ = tree(OP_AND, 0, 0, "&&", $1, NULL, $3);         
}
 | '(' E ')' { $$ = $2;                                             
}
 ;

V : vINT  { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
            symbol->flag  = VALUE_INT;
            symbol->value = $1;
            ASTNode* n = node(symbol);
            $$ = n; }
            
  | vBOOL { Symbol* symbol = (Symbol*) malloc(sizeof(Symbol)) ;
            symbol->flag = VALUE_BOOL;
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

Type : tINT
     | tBOOL
     ;
%%

ASTNode* tree(Flag flag, Type type, int value, const char* name, ASTNode* lSide, ASTNode* mSide, ASTNode* rSide) {
    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->name = (char*) malloc(sizeof(char));
    strcpy(symbol->name, name);
    symbol->value = value;
    symbol->type  = type;
    symbol->flag  = flag;
    ASTNode* root = node(symbol);
    compose(root, lSide, mSide, rSide);
    return root;
}
