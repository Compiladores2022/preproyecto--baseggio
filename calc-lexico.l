%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "grammar.tab.h"

%}
%x IN_COMMENT

%option noyywrap
%option yylineno

digit     [0-9]
alpha     [a-zA-Z]
alpha_num {alpha}|{digit}|"_"
bool      "True"|"False"
keyword   "Program"|"if"|"then"|"else"|"extern"|"void"|"while"

%%

"Program" { return PROGRAM; }

"if"      { return IF; }

"then"    { return THEN; }

"else"    { return ELSE; }

"extern"  { return EXTERN; }

"void"    { return VOID; }

"while"   { return WHILE; }

"return"  { return RETURN; }

"Int"     { yylval.t = TYPE_INT;
            return tINT; }

"Bool"    { yylval.t = TYPE_BOOL;
            return tBOOL; }

{bool}    { yylval.i = strcmp(yytext, "True") == 0? 1 : 0;
            return vBOOL; }

{alpha}{alpha_num}* { yylval.s = (char*) malloc(sizeof(char));
                      strcpy(yylval.s, yytext);
                      return ID; 
                    }

"-"?{digit}+ { yylval.i = atoi(yytext);
               return vINT; }

"==" { return EQT; }

[+*/%=;(){}<>,]|"-" { return *yytext; }
                                  
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

" "|\n|\t

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
