%{
#include <string.h>
%}

COMMENT ("---"("\n"|.*)*"---")|#.*
SEPARADOR ","
NUM [0-9]+\.?[0-9]*
VARS [a-z]+[0-9]*
START "START_PROG"
END "END_PROG"
IF "if"
ELSE "else"
WHILE "while"
PRINT "Out"
PRINTT "Outt"
PRINTS "Outs"
SCAN "Imp"
SCANS "Imps"
DECL "var"	
EXPONENT "**"
STRING (\".+*\")
INGREMENTO "++"
DECREMENTO "--"
TYPEINT "Int"
TYPEFLW "Flw"
TYPESTR "Str"
	
%%
{START} {return START;}
{END} {return END;}
{IF} {return IF;}
{ELSE} {return ELSE;}
{WHILE} {return WHILE;}
{PRINTT} {return PRINTT;}
{PRINT} {return PRINT;}
{PRINTS} {return PRINTS;}
{SCAN} {return SCAN;}
{SCANS} {return SCANS;}
{DECL} {return DECL;}
{EXPONENT} {return EXPONENT;}
{INGREMENTO} {return INGREMENTO;}
{DECREMENTO} {return DECREMENTO;}
{TYPEINT} {return TYPEINT;}
{TYPEFLW} {return TYPEFLW;}
{TYPESTR} {return TYPESTR;}
{SEPARADOR} {return SEPARADOR;}

{VARS} {
	strcpy(yylval.str,yytext);
	return VARS;
	}

{STRING} {
	int i; 
	for(i = 0; i < strlen(yytext); i++){
		yytext[i] = yytext[i+1];
	}
	yytext[i-2] = '\0';
	strcpy(yylval.str, yytext);
	//printf("%s .l\n", yytext);
	return STRING;
	}

{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}



[-+()=/*^{};\[\]:] {return *yytext;
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