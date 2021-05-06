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

%token CREATE NODE
%token <string> ID
%token <string> LABEL
%token <number> FLOAT

%start S
%%

S:
    CREATE              { printf("CREATE"); return 0; } 
  | NODE                { printf("NODE"); return 0; }   
  | LABEL               { printf("LABEL = %s", $1); return 0; }
  | ID                  { printf("ID = %s", $1); return 0; }
  | FLOAT               { printf("FLOAT = %f", $1); return 0; }
  ;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}

