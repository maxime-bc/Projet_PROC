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

%token CREATE NODE EDGE FROM TO AT EOL LABEL
%token <string> ID
%token <string> LABEL_STRING
%token <number> FLOAT

%start S
%%

S:
    Line                 { }
  | S Line               { }
  ;

Line:
    EOL                   { }
  | Command               { }
  ;

Command:
    EOL                                    { }
  | CREATE NODE ID Attributes              { } 
  | CREATE EDGE FROM ID TO ID   { printf("CREATE EDGE FROM %s TO %s", $4, $6); }
  ;

Attributes:
    EOL                                     { }
  | AT FLOAT FLOAT { printf("AT %f %f\n", $2, $3); }
  | LABEL LABEL_STRING { printf("LABEL %s\n", $2); }
  ;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}

