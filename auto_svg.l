%{
  #include "auto_svg.tab.h"
  #include <stdlib.h>
%}

LABEL \"[^\"\\<\>]*\"
ID  [a-zA-Z][a-zA-Z0-9_]{0,14}
FLOAT [+-]?([0-9]*[.])?[0-9]+

%%

(?i:create) {return(CREATE);}
(?i:node) {return(NODE);}
{ID} {
  yylval.string = strdup(yytext);
  return(ID); 
}
{FLOAT} { 
  yylval.number = strtod(yytext, NULL);
  return(FLOAT); 
}
{LABEL} { 
  yylval.string = strdup(yytext);
  return(LABEL); 
}
. { }

%%