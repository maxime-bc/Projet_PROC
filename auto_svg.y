%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "node.h"
#include "edge.h"
#include "svg.h"

int yylex();
int yyerror(char *s);
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
    MOVE FLOAT FLOAT { moveAllNodes($2, $3); }
  | MOVE ID FLOAT FLOAT { moveNode($2, $3, $4); }
  | MOVE OPENING_SQ_BRACKET Id_List ENDING_SQ_BRACKET FLOAT FLOAT { moveMultipleNodesById($5, $6); }
  | RENAME ID WITH ID { renameNode($2, $4); }
  | DUMP { printNodesList(); printEdgesList(); }
  | DUMP LABEL_STRING { dumpSVG($2); }
  | REMOVE NODE ID { removeNode($3); }
  | REMOVE EDGE FROM ID TO ID { removeEdge($4, $6); }
  | CREATE NODE ID AT FLOAT FLOAT Create_Attrs_1    { createNode($3, $5, $6); } // demander au prof
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING Create_Attrs_2   { createEdge($4, $6, $8); }
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING AT FLOAT FLOAT Create_Attrs_2 { createEdgePos($4, $6, $8, $10, $11); }
  ;

Id_List:
    ID COMMA Id_List { addId($1); }
  | ID { addId($1); }

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

int yyerror(char *s) {
    printf("%s\n",s);
    return 0;
}

int main(void) {
    yyparse();
}

