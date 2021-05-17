%{
#include <iostream>
#include "node.h"
#include "edge.h"

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
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING Create_Attrs_2   { createEdge($4, $6, $8); }
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING AT FLOAT FLOAT Create_Attrs_2 { createEdgeWithPositions($4, $6, $8, $10, $11); }
  ;

Create_Attrs_1:
    EOL                                     { }
  | LABEL LABEL_STRING Create_Attrs_1 { setLabel($2); }
  | COLOR LABEL_STRING Create_Attrs_1 { setNodeColor($2); }
  | BGCOLOR LABEL_STRING Create_Attrs_1 { setBgColor($2); }
  | SIZE FLOAT Create_Attrs_1 { setSize($2); }
  | FINAL Directions Create_Attrs_1 { setType("final"); }
  | FINAL Create_Attrs_1 { setType("final"); }
  | INIT Directions Create_Attrs_1 { setType("initial"); }
  | INIT Create_Attrs_1 { setType("initial"); }
  ;

Create_Attrs_2:
    EOL                               { }
  | COLOR LABEL_STRING Create_Attrs_2 { setEdgeColor($2); }
  | PATH LABEL_STRING Create_Attrs_2  { setPath($2); }
  ;

Directions:
    NORTH  { setDirection("north"); }
  | SOUTH { setDirection("south"); }
  | WEST  { setDirection("west"); }
  | EAST  { setDirection("east"); }
  | NORTH_EAST  { setDirection("north-east"); }
  | NORTH_WEST  { setDirection("north-west"); }
  | SOUTH_EAST  { setDirection("south-east"); }
  | SOUTH_WEST  { setDirection("south-west"); }
  ;

%%

int main(void){
    yyparse();
}
