%{
#include "node.h"
#include "edge.h"
#include "svg.h"
#include "automaton.h"
#include <iostream>

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
   const char* c_string;
}

%type <c_string> Directions

%token CREATE NODE EDGE FROM TO AT EOL LABEL COLOR BGCOLOR SIZE INIT FINAL PATH DUMP REMOVE MOVE WITH RENAME EDIT
%token OPENING_SQ_BRACKET ENDING_SQ_BRACKET COMMA IS COMPLETE CLEAR SHOW ALL EDGES DETERMINISTIC ACCEPTED
%token NORTH SOUTH EAST WEST NORTH_EAST NORTH_WEST SOUTH_EAST SOUTH_WEST
%token <string> ID
%token <string> LABEL_STRING
%token <number> FLOAT

%start S
%%

S:
    Command                 { }
  | S Command               { }
  ;

Command:
    EOL { }
  | MOVE FLOAT FLOAT { moveAllNodes($2, $3); }
  | MOVE ID FLOAT FLOAT { moveNode($2, $3, $4); }
  | MOVE OPENING_SQ_BRACKET Id_List ENDING_SQ_BRACKET FLOAT FLOAT { moveMultipleNodesById($5, $6); }
  | RENAME ID WITH ID { renameNode($2, $4); }
  | DUMP LABEL_STRING { dumpSVG($2); }
  | DUMP { printNodes(); printEdges(); }
  | EDIT ID WITH Create_Attrs_1 { editNode($2); }
  | EDIT EDGE FROM ID TO ID WITH Create_Attrs_2 { editEdge($4, $6); }
  | REMOVE NODE ID { removeNode($3); }
  | REMOVE EDGE FROM ID TO ID { removeEdge($4, $6); }
  | CREATE NODE ID AT FLOAT FLOAT { createNode($3, $5, $6); }
  | CREATE NODE ID AT FLOAT FLOAT Create_Attrs_1 { createNode($3, $5, $6); }
  | CREATE NODE ID Create_Attrs_1 AT FLOAT FLOAT { createNode($3, $6, $7); }
  | CREATE NODE ID Create_Attrs_1 AT FLOAT FLOAT Create_Attrs_1 { createNode($3, $6, $7); }
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING Create_Attrs_2   { createEdge($4, $6, $8); }
  | CREATE EDGE FROM ID TO ID LABEL LABEL_STRING AT FLOAT FLOAT Create_Attrs_2 { createEdge($4, $6, $8, $10, $11); }
  | IS COMPLETE { if(isComplete()) { std::cout << "true" << std::endl; } else { std::cout << "false" << std::endl; } }
  | SHOW COMPLETE LABEL_STRING { isComplete($3); }
  | COMPLETE WITH ID AT FLOAT FLOAT { complete($3, $5, $6); }
  | IS DETERMINISTIC {  if(isDeterministic()) { std::cout << "true" << std::endl; } else { std::cout << "false" << std::endl; } }
  | SHOW DETERMINISTIC LABEL_STRING { isDeterministic($3); }
  | IS ACCEPTED LABEL_STRING { if(isAccepted($3)) { std::cout << "true" << std::endl; } else { std::cout << "false" << std::endl; } }
  | SHOW LABEL_STRING { isAccepted($2, true); }
  | CLEAR ALL { EDGES_LIST.clear(); NODES_LIST.clear(); }
  | CLEAR EDGES { EDGES_LIST.clear(); }
  ;

Id_List:
    ID COMMA Id_List { addId($1); }
  | ID { addId($1); }

Create_Attrs_1:
    LABEL LABEL_STRING { setNodeLabel($2); }
  | COLOR LABEL_STRING { setNodeColor($2); }
  | BGCOLOR LABEL_STRING { setBackgroundColor($2); }
  | SIZE FLOAT { setSize($2); }
  | FINAL Directions  { setType("final", $2); }
  | FINAL { setType("final", ""); }
  | INIT Directions { setType("initial", $2); }
  | INIT { setType("initial", ""); }
  | Create_Attrs_1 LABEL LABEL_STRING { setNodeLabel($3); }
  | Create_Attrs_1 COLOR LABEL_STRING { setNodeColor($3); }
  | Create_Attrs_1 BGCOLOR LABEL_STRING { setBackgroundColor($3); }
  | Create_Attrs_1 SIZE FLOAT { setSize($3); }
  | Create_Attrs_1 FINAL Directions { setType("final", $3); }
  | Create_Attrs_1 FINAL { setType("final", ""); }
  | Create_Attrs_1 INIT Directions { setType("initial", $3); }
  | Create_Attrs_1 INIT { setType("initial", ""); }
  ;

Create_Attrs_2:
    EOL                               { }
  | LABEL LABEL_STRING Create_Attrs_2 { setEdgeLabel($2); }
  | LABEL LABEL_STRING AT FLOAT FLOAT Create_Attrs_2 { setEdgeLabelWithPos($2, $4, $5); }
  | COLOR LABEL_STRING Create_Attrs_2 { setEdgeColor($2); }
  | PATH LABEL_STRING Create_Attrs_2  { setPath($2); }
  ;

Directions:
    NORTH  { $$ = "north"; }
  | SOUTH { $$ = "south"; }
  | WEST  { $$ = "west"; }
  | EAST  { $$ = "east"; }
  | NORTH_EAST  { $$ = "north-east"; }
  | NORTH_WEST  { $$ = "north-west"; }
  | SOUTH_EAST  { $$ = "south-east"; }
  | SOUTH_WEST  { $$ = "south-west"; }
  ;

%%

int main(void){
    yyparse();
}