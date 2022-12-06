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
PRINTS "PRINTS"
DECL "var"	
EXPONENT "**"
STRING (\".+*\")

%%
{START} {return START;}
{END} {return END;}
{IF} {return IF;}
{ELSE} {return ELSE;}
{WHILE} {return WHILE;}
{PRINT} {return PRINT;}
{PRINTS} {return PRINTS;}
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

{STRING} {
	int i; 
	for(i = 0; i < strlen(yytext); i++){
		yytext[i] = yytext[i+1];
	}
	yytext[i-2] = '\0';
	strcpy(yylval.str, yytext);
	printf("%s .l\n", yytext);
	return STRING;
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