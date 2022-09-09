%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "calc-sintaxis.tab.h"

%}
%x IN_COMMENT

%option noyywrap
%option yylineno

letra  [a-zA-Z]      
digito [0-9]
bool   "True"|"False"

%%

{digito}+ { return vINT; }

{bool}    { yylval.i = strcmp(yytext, "True") == 0? 1 : 0;
            return vBOOL; }

"return"  { return RETURN; }

"Int"     { yylval.t = TYPE_INT;
            return tINT; }

"Bool"    { yylval.t = TYPE_BOOL;
            return tBOOL; }

{letra}({letra}|{digito})* { yylval.s = (char*) malloc(sizeof(char));
                             strcpy(yylval.s, yytext);
                             return ID; 
                           }    

[+*=;()] { return *yytext; }
                                  
"&&"     { return AND; }
       
"||"     { return OR; }

"//".*"\n"

<INITIAL>{
  "/*"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
  "*/"      BEGIN(INITIAL);
  [^*\n]+   // eat comment in chunks
  "*"       // eat the lone star
  \n        yylineno++;
}

" "|\n 

. { printf("%s%d\n", "-> Lexical ERROR on line: ", yylineno);
    printf("%s%s\n", "unexpected character: ", yytext);
    exit(0);
  }

%%

void yyerror(char* s){
	printf("%s%d\n","-> Syntactic ERROR on line: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}
