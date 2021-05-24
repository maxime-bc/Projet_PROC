%{
    extern "C"
    {
        int yylex(void);
    }
  #include "auto_svg.tab.h"

  void topntail(char *str) {
      size_t len = strlen(str);
      memmove(str, str+1, len-2);
      str[len-2] = 0;
  }
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
"with" {return(WITH);}
"rename" {return(RENAME);}
"[" { return(OPENING_SQ_BRACKET); }
"]" { return(ENDING_SQ_BRACKET); }
"," { return(COMMA); }
"edit" { return(EDIT); }
"is" { return(IS); }
"complete" { return(COMPLETE); }
"clear" { return(CLEAR); }
"show" { return(SHOW); }
"all" { return(ALL); }
"edges" { return(EDGES); }
{ID} {
  yylval.string = strdup(yytext);
  return(ID);
}
{FLOAT} {
  yylval.number = strtod(yytext, NULL);
  return(FLOAT);
}
{LABEL_STRING} {
  char *str_dup = strdup(yytext);
  topntail(str_dup);
  yylval.string = str_dup;
  return(LABEL_STRING);
}
"\n" {return EOL;}
. { }
%%