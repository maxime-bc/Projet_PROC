%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex();
int yyerror(char *s);

%}

%union{
   float number;
   char* string;
}

%token CREATE NODE EDGE FROM TO
%token <string> ID
%token <string> LABEL
%token <number> FLOAT

%start S
%%

S:
    Command                 { }
  | S Command               { }
  ;

Command:
    CREATE NODE ID               { printf("CREATE NODE %s", $3); } 
  | CREATE EDGE FROM ID TO ID    { printf("CREATE EDGE FROM %s TO %s", $4, $6); }
  | FLOAT               { printf("FLOAT = %f", $1); }
  ;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}

