%{
    extern "C"
    {
        int yylex(void);
    }
  #include "auto_svg.tab.h"
%}

LABEL_STRING \"[^\"\\<\>]*\"
ID  [a-zA-Z][a-zA-Z0-9_]{0,14}
FLOAT [+-]?([0-9]*[.])?[0-9]+
%option caseless
%%

"create" {return(CREATE);}
"node" {return(NODE);}
"at" {return(AT);}
{ID} {
  yylval.string = strdup(yytext);
  return(ID);
}
{FLOAT} {
  yylval.number = strtod(yytext, NULL);
  return(FLOAT);
}
"\n" {return EOL;}
. { }
%%