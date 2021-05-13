%{
  #include "auto_svg.tab.h"
  #include <stdlib.h>
%}

LABEL_STRING \"[^\"\\<\>]*\"
ID  [a-zA-Z][a-zA-Z0-9_]{0,14}
FLOAT [+-]?([0-9]*[.])?[0-9]+

%%

(?i:create) {return(CREATE);}
(?i:node) {return(NODE);}
(?i:edge) {return(EDGE);}
(?i:from) {return(FROM);}
(?i:to) {return(TO);}
(?i:at) {return(AT);}
(?i:label) {return(LABEL);}
(?i:color) {return(COLOR);}
(?i:bgcolor) {return(BGCOLOR);}
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