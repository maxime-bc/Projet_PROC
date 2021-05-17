%{
#include <iostream>
#include "node.h"

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

%token CREATE NODE EDGE FROM TO AT EOL LABEL COLOR BGCOLOR SIZE INIT FINAL PATH DUMP REMOVE MOVE WITH RENAME
%token OPENING_SQ_BRACKET ENDING_SQ_BRACKET COMMA
%token NORTH SOUTH EAST WEST NORTH_EAST NORTH_WEST SOUTH_EAST SOUTH_WEST
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
    CREATE NODE ID AT FLOAT FLOAT Create_Attrs_1 { createNode($3, $5, $6); } // demander au prof
  ;

Create_Attrs_1:
    EOL                                     { }
  | LABEL LABEL_STRING Create_Attrs_1 { setLabel($2); }
  | COLOR LABEL_STRING Create_Attrs_1 { setNodeColor($2); }
  | BGCOLOR LABEL_STRING Create_Attrs_1 { setBgColor($2); }
  | SIZE FLOAT Create_Attrs_1 { setSize($2); }
  ;

%%

int main(void){
    yyparse();
}
