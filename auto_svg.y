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

%token CREATE NODE EDGE FROM TO AT EOL LABEL COLOR BGCOLOR SIZE INIT FINAL
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
    EOL                                    { }
  | CREATE NODE ID Create_Attrs_1          { } 
  | CREATE EDGE FROM ID TO ID   { printf("CREATE EDGE FROM %s TO %s", $4, $6); }
  ;

Create_Attrs_1:
    EOL                                     { }
  | AT FLOAT FLOAT Create_Attrs_1 { printf("AT %f %f\n", $2, $3); }
  | LABEL LABEL_STRING Create_Attrs_1 { printf("LABEL %s\n", $2); }
  | COLOR LABEL_STRING Create_Attrs_1 { printf("COLOR %s\n", $2); }
  | BGCOLOR LABEL_STRING Create_Attrs_1 { printf("BGCOLOR %s\n", $2); }
  | SIZE FLOAT Create_Attrs_1 { printf("SIZE %f\n", $2); }
  | FINAL Directions Create_Attrs_1 {}
  | FINAL Create_Attrs_1 {}
  | INIT Directions Create_Attrs_1 {}
  | INIT Create_Attrs_1 {}
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

