%{
  #include "auto_svg.tab.h"
  #include <stdlib.h>
%}

LABEL_STRING \"[^\"\\<\>]*\"
ID  [a-zA-Z][a-zA-Z0-9_]{0,14}
FLOAT [+-]?([0-9]*[.])?[0-9]+
%option caseless
%%

"create" {return(CREATE);}
(?i:node) {return(NODE);}
(?i:edge) {return(EDGE);}
(?i:from) {return(FROM);}
(?i:to) {return(TO);}
(?i:at) {return(AT);}
(?i:label) {return(LABEL);}
(?i:color) {return(COLOR);}
(?i:bgcolor) {return(BGCOLOR);}
(?i:size) {return(SIZE);}
(?i:initial) {return(INIT);} /* can't use INITIAL because it is a flex macro */
(?i:final) {return(FINAL);}
(?i:north) {return(NORTH);}
(?i:south) {return(SOUTH);}
(?i:east) {return(EAST);}
(?i:west) {return(WEST);}
(?i:north-east) {return(NORTH_EAST);}
(?i:north-west) {return(NORTH_WEST);}
(?i:south-east) {return(SOUTH_EAST);}
(?i:south-west) {return(SOUTH_WEST);}
(?i:path) {return(PATH);}
(?i:dump) {return(DUMP);}
{ID} {
  yylval.string = strdup(yytext);
  return(ID); 
}
{FLOAT} { 
  yylval.number = strtod(yytext, NULL);
  return(FLOAT); 
}
{LABEL_STRING} { 
  yylval.string = strdup(yytext);
  return(LABEL_STRING); 
}
"\n" {return EOL;}
. { }
%%