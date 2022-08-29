%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}
%x IN_COMMENT

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]
bool "True"|"False"

%%

{digito}+ { return vINT; }

{bool} { return vBOOL; }

"return" { return RETURN; }

"Int" { return tINT; }

"Bool" { return tBOOL; }

{letra}({letra}|{digito})* { return ID; }    

[+*=;()] { return *yytext; }
                                  
"&&" { return AND; }
       
"||" { return OR; }

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

. { yyerror(); }

%%

void yyerror(){
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
