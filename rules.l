%{
#include <string.h>
%}

COMMENT ("---"("\n"|.*)*"---")|#.*
NUM [0-9]+\.?[0-9]*
VARS [a-z]+[0-9]*
START "START"
END "END"
IF "IF"
ELSE "ELSE"
WHILE "WHILE"
PRINT "PRINT"
DECL "var"	
EXPONENT "**"

%%
{START} {return START;}
{END} {return END;}
{IF} {return IF;}
{ELSE} {return ELSE;}
{WHILE} {return WHILE;}
{PRINT} {return PRINT;}
{DECL} {return DECL;}
{EXPONENT} {return EXPONENT;}

{VARS} {
	strcpy(yylval.str,yytext);
	return VARS;
	}

{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}

[-+()=/*^{};] {return *yytext;
			}
			

">" {yylval.fn = 1; return CMP; }
"<" {yylval.fn = 2; return CMP; }
"<>" {yylval.fn = 3; return CMP; }
"==" {yylval.fn = 4; return CMP; }
">=" {yylval.fn = 5; return CMP; }
"<=" {yylval.fn = 6; return CMP; }

{COMMENT} {;}

[\ \n\t]*	{;}
. {printf("(%s) Ingonrado\n",yytext);}
%%