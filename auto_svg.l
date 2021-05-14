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
"node" {return(NODE);}
"edge" {return(EDGE);}
"from" {return(FROM);}
"to" {return(TO);}
"at" {return(AT);}
"label" {return(LABEL);}
"color" {return(COLOR);}
"bgcolor" {return(BGCOLOR);}
"size" {return(SIZE);}
"initial" {return(INIT);} /* can't use INITIAL because it is a flex macro */
"final" {return(FINAL);}
"north" {return(NORTH);}
"south" {return(SOUTH);}
"east" {return(EAST);}
"west" {return(WEST);}
"north-east" {return(NORTH_EAST);}
"north-west" {return(NORTH_WEST);}
"south-east" {return(SOUTH_EAST);}
"south-west" {return(SOUTH_WEST);}
"path" {return(PATH);}
"dump" {return(DUMP);}
"remove" {return(REMOVE);}
"move" {return(MOVE);}
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