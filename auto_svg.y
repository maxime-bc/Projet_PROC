%{
#include <iostream>
#include "test.h"

void yyerror(const char *s){
    fprintf(stderr, "error: %s\n", s);
}

extern "C"{
  int yyparse(void);
  int yylex(void);
  int yywrap(){
    return 1;
  }
}
%}

%union{
   float number;
   char* string;
}

%token CREATE NODE AT EOL
%token <string> ID
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
    CREATE NODE ID AT FLOAT FLOAT    { testPrint(); } // demander au prof
  ;

%%

int main(void){
    yyparse();
}
