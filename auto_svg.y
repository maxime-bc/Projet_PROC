%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"

int yylex();
int yyerror(char *s);
%}

%union{
   float number;
   char* string;
}

%token CREATE NODE EDGE FROM TO AT EOL LABEL COLOR BGCOLOR SIZE INIT FINAL PATH
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
  | CREATE NODE ID AT FLOAT FLOAT Create_Attrs_1    { create_node($3, $5, $6); } /*demander au prof*/
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING Create_Attrs_2   { }
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING AT FLOAT FLOAT Create_Attrs_2   { }
  ;

Create_Attrs_1:
    EOL                                     { }
  | LABEL LABEL_STRING Create_Attrs_1 { set_label($2); }
  | COLOR LABEL_STRING Create_Attrs_1 { printf("COLOR %s\n", $2); }
  | BGCOLOR LABEL_STRING Create_Attrs_1 { printf("BGCOLOR %s\n", $2); }
  | SIZE FLOAT Create_Attrs_1 { printf("SIZE %f\n", $2); }
  | FINAL Directions Create_Attrs_1 {}
  | FINAL Create_Attrs_1 {}
  | INIT Directions Create_Attrs_1 {}
  | INIT Create_Attrs_1 {}
  ;

Create_Attrs_2:
    EOL
  | COLOR LABEL_STRING Create_Attrs_2 { printf("COLOR %s\n", $2); }
  | PATH LABEL_STRING Create_Attrs_2  { printf("PATH %s\n", $2); }
  ;

Directions:
    NORTH  { printf("NORTH\n");}
  | SOUTH {}
  | WEST  {}
  | EAST  {}
  | NORTH_EAST  {}
  | NORTH_WEST  {}
  | SOUTH_EAST  {}
  | SOUTH_WEST  {}
  ;

%%

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}

