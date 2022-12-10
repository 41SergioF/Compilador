/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "rules.y"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>	

//nodetype variáveis

//1 - Integer
//2 - Double
//3 - String
//4 - Arrey
	
	typedef struct vars{//estrutura de uma variável
		int nodetype;
		char name[50];	 // Nome da variável
		double valueDouble;	 // Valor quando double
		int valueInteger;	 // Valor quando int
		char valueString[50]; // Valor quando String
		double *vector;	 // Ponteiro para um vetor de double
		struct vars * prox;
	}VARIAVEL;

	typedef struct conteudo{
		int intergerValue;
		double doubleValue;
		char stringValue;
	}Conteudo;
	
	VARIAVEL *insert_vari_int(VARIAVEL*l,char n[]){
		VARIAVEL*new =(VARIAVEL*)malloc(sizeof(VARIAVEL));
		strcpy(new->name,n);
		new->prox = l;
		new->nodetype = 1;
		return new;
	}

	//insere uma nova variável na lista de variáveis
	VARIAVEL *insert_vari_float(VARIAVEL*l,char n[]){
		VARIAVEL*new =(VARIAVEL*)malloc(sizeof(VARIAVEL));
		strcpy(new->name,n);
		new->prox = l;
		new->nodetype = 2;
		return new;
	}
	
	VARIAVEL *insert_vari_str(VARIAVEL*l,char n[]){
		VARIAVEL*new =(VARIAVEL*)malloc(sizeof(VARIAVEL));
		strcpy(new->name,n);
		new->prox = l;
		new->nodetype = 3;
		return new;
	}
	
	VARIAVEL *insert_array(VARIAVEL*l,char n[], int tamanho){
		VARIAVEL*new =(VARIAVEL*)malloc(sizeof(VARIAVEL));
		strcpy(new->name,n);
		new->vector = (double*)malloc(tamanho * sizeof(double));
		new->prox = l;
		new->nodetype = 3;
		return new;
	}
	
	//busca uma variável na lista de variáveis
	VARIAVEL *srch(VARIAVEL*l,char n[]){
		VARIAVEL*aux = l;
		while(aux != NULL){
			if(strcmp(n,aux->name)==0)
				return aux;
			aux = aux->prox;
		}
		return aux;
	}
	
		
/*O node type serve para indicar o tipo de nó que está na árvore. Isso serve para a função eval() entender o que realizar naquele nó*/
typedef struct ast { /*Estrutura de um nó*/
	int nodetype;
	struct ast *l; /*Esquerda*/
	struct ast *r; /*Direita*/
}Ast; 

typedef struct flwVal { /*Estrutura de um número*/
	int nodetype;
	double value;
}FlwVal;

typedef struct intVal { /*Estrutura de um número*/
	int nodetype;
	double value;
}IntVal;

typedef struct nameVari { /*Estrutura de um nome de variável, nesse exemplo uma variável é um número no vetor name[26]*/
	int nodetype;
	char name[50];
	int size;
}NameVari;

typedef struct strVal { /*Estrutura de a string*/
	int nodetype;
	char value[50];
}StrVal;
	
typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
	int nodetype;
	Ast *cond;		/*condição*/
	Ast *tl;		/*then, ou seja, verdade*/
	Ast *el;		/*else*/
}Flow;

typedef struct symasgn { /*Estrutura para um nó de atribuição. Para atrubior o valueDouble de v em name*/
	int nodetype;
	char name[50];
	Ast *v;
	int pos;
}Symasgn;


VARIAVEL *listOfVariavel; /*Variáveis*/
VARIAVEL *aux;

Ast * newast(int nodetype, Ast *l, Ast *r){ /*Função para criar um nó*/

	Ast *a = (Ast*) malloc(sizeof(Ast));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	return a;
}
 
Ast * newVari(int nodetype, char nome[50]) {			/*Função de que cria uma nova variável*/
	NameVari *a = (NameVari*) malloc(sizeof(NameVari));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	strcpy(a->name,nome);
	return (Ast*)a;
}

Ast * newarray(int nodetype, char nome[50], int tam) {			/*Função de que cria uma nova variável*/
	NameVari *a = (NameVari*) malloc(sizeof(NameVari));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	strcpy(a->name,nome);
	a->size = tam;
	return (Ast*)a;
}	

	
Ast * newNum(double value) {			/*Função de que cria um novo número*/
	FlwVal *a = (FlwVal*) malloc(sizeof(FlwVal));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'K';
	a->value = value;
	return (Ast*)a;
}	

Ast * newString(char str[]) { /*Função de que cria uma nova string*/
	StrVal *a = (StrVal*) malloc(sizeof(StrVal));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'J';
	strcpy(a->value, str);
	return (Ast*)a;
}

Ast * newInterger(int value) { /*Função de que cria uma nova string*/
	IntVal *a = (IntVal*) malloc(sizeof(IntVal));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'R';
	a->value = value;
	return (Ast*)a;
}

Ast * newflow(int nodetype, Ast *cond, Ast *tl, Ast *el){ /*Função que cria um nó de if/else/while*/
	Flow *a = (Flow*)malloc(sizeof(Flow));
	if(!a) {
		printf("out of space");
	exit(0);
	}
	a->nodetype = nodetype;
	a->cond = cond;
	a->tl = tl;
	a->el = el;
	return (Ast *)a;
}

Ast * newcmp(int cmptype, Ast *l, Ast *r){ /*Função que cria um nó para testes*/
	Ast *a = (Ast*)malloc(sizeof(Ast));
	if(!a) {
		printf("out of space");
	exit(0);
	}
	a->nodetype = '0' + cmptype; /*Para pegar o tipe de teste, definido no arquivo.l e utilizar na função eval()*/
	a->l = l;
	a->r = r;
	return a;
}

Ast * newasgn(char name[50], Ast *v) { /*Função para um nó de atribuição*/
	Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
	if(!a) {
		printf("out of space");
	exit(0);
	}
	a->nodetype = '=';
	strcpy(a->name,name);
	a->v = v; /*Valor*/
	//printf ("aqui:%lf\n",((VARIAVEL*)a->v)->doubleValue);
	return (Ast *)a;
}

Ast * newasgn_a(char name[50], Ast *v, int indice) { /*Função para um nó de atribuição*/
	Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
	if(!a) {
		printf("out of space");
	exit(0);
	}
	a->nodetype = '=';
	strcpy(a->name,name);
	a->v = v; /*Valor*/
	a->pos = indice;
	return (Ast *)a;
}
	
	
Ast * newValorVal(char name[]) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/
	
	NameVari *a = (NameVari*) malloc(sizeof(NameVari));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'N';
	strcpy(a->name,name);
	return (Ast*)a;
}
	
Ast * newValorVal_a(char name[], int indice) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/
	NameVari *a = (NameVari*) malloc(sizeof(NameVari));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'n';
	strcpy(a->name,name);
	a->size = indice;
	
	return (Ast*)a;
}	

Ast * newValorValS(char name[50]) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/
	
	NameVari *a = (NameVari*) malloc(sizeof(NameVari));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'Q';
	strcpy(a->name,name);
	return (Ast*)a;
	
}

	
char * eval2(Ast *a) { /*Função que executa operações a partir de um nó*/
		VARIAVEL *aux1;
		char *v2;
		
			switch(a->nodetype) {
			
			case 'Q':
				aux1 = srch(listOfVariavel,((NameVari *)a)->name);
				return aux1->valueString;
				break;

			default: printf("internal error: bad node %c\n", a->nodetype);
					break;
		}
		
	return v2;
	}


Conteudo * eval(Ast *a) { /*Função que executa operações a partir de um nó*/
	Conteudo * cont; //= (Conteudo *)malloc(sizeof(Conteudo));
	Conteudo * cont_aux; // = (Conteudo *)malloc(sizeof(Conteudo));
	double valueDouble; 
	char v1[50];
	char *v2;
	VARIAVEL * aux1;
	if(!a) {
		printf("internal error, null eval");
		cont->doubleValue = 0.0;
		return cont;
	}
	switch(a->nodetype) {
		case 'K': cont->doubleValue = ((FlwVal *)a)->value; break; 	/*Recupera um número*/
		//case 'J': 
		case 'N': 
			aux1 = srch(listOfVariavel,((NameVari *)a)->name);
			cont->doubleValue = aux1->valueDouble;
			break;
		
		case 'n':
			
			aux1 = srch(listOfVariavel,((NameVari *)a)->name);
			valueDouble = aux1->vector[((NameVari *)a)->size];
			break;
		
		case '+': cont->doubleValue = eval(a->l)->doubleValue + eval(a->r)->doubleValue; break;	/*Operações "árv esq   +   árv dir"*/
		case '-': cont->doubleValue = eval(a->l)->doubleValue - eval(a->r)->doubleValue; break;	/*Operações "árv esq   +   árv dir"*/
		case '*': cont->doubleValue = eval(a->l)->doubleValue * eval(a->r)->doubleValue; break;	/*Operações "árv esq   +   árv dir"*/
		case '/': cont->doubleValue = eval(a->l)->doubleValue / eval(a->r)->doubleValue; break;	/*Operações "árv esq   +   árv dir"*/
		case 'M': cont->doubleValue = -eval(a->l)->doubleValue; break;				/*Operações, número negativo*/
	
		case '1': cont->doubleValue = (eval(a->l)->doubleValue >  eval(a->r)->doubleValue)? 1 : 0; break;	/*Operações lógicas. "árv esq   >   árv dir"  Se verdade 1, falso 0*/
		case '2': cont->doubleValue = (eval(a->l)->doubleValue <  eval(a->r)->doubleValue)? 1 : 0; break;
		case '3': cont->doubleValue = (eval(a->l)->doubleValue != eval(a->r)->doubleValue)? 1 : 0; break;
		case '4': cont->doubleValue = (eval(a->l)->doubleValue == eval(a->r)->doubleValue)? 1 : 0; break;
		case '5': cont->doubleValue = (eval(a->l)->doubleValue >= eval(a->r)->doubleValue)? 1 : 0; break;
		case '6': cont->doubleValue = (eval(a->l)->doubleValue <= eval(a->r)->doubleValue)? 1 : 0; break;
		
		case '=':
			cont_aux = eval(((Symasgn *)a)->v); /*Recupera o valueDouble*/
			aux = srch(listOfVariavel,((Symasgn *)a)->name);
			
			//printf ("AQUI %d\n",((NameVari *)aux)->nodetype);
			if (aux->nodetype == 1){
				aux->valueInteger = cont_aux->intergerValue;
			}
			if(aux->nodetype == 2){ //lembrar de verificar os demais tipos
				aux->valueDouble = cont_aux->doubleValue;
			}/*
			if(aux->nodetype == 3){
				strcpy(aux->valueString, "teste");
			}*/
			else
				aux->vector[((Symasgn *)a)->pos] = cont_aux->doubleValue; //inserção no vetor
			break;
		
		case 'I':						/*CASO IF*/
			if (eval(((Flow *)a)->cond)->doubleValue != 0) {	/*executa a condição / teste*/
				if (((Flow *)a)->tl)		/*Se existir árvore*/
					cont->doubleValue = eval(((Flow *)a)->tl)->doubleValue; /*Verdade*/
				else
					valueDouble = 0.0;
			} else {
				if( ((Flow *)a)->el) {
					cont->doubleValue = eval(((Flow *)a)->el)->doubleValue; /*Falso*/
				} else
					cont->doubleValue = 0.0;
				}
			break;
			
		case 'W':
			//printf ("WHILE\n");
			cont->doubleValue = 0.0;
			if( ((Flow *)a)->tl) {
				while( eval(((Flow *)a)->cond) != 0){
					cont->doubleValue = eval(((Flow *)a)->tl)->doubleValue;
					}
			}
		break;
		case '^':	cont->doubleValue = pow(eval(a->l)->doubleValue, eval(a->r)->doubleValue); 
					break; //carlos
		
		case 'L':	eval(a->l)->doubleValue;
					cont->doubleValue = eval(a->r)->doubleValue; break; /*Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos*/
		
		//Impreme uma double
		case 'P': 	cont->doubleValue = eval(a->l)->doubleValue;		/*Recupera um valueDouble*/
					printf ("%.2f\n", cont->doubleValue);
					break;  			/*Função que imprime um valueDouble*/
		
		case 'X': 	cont->intergerValue = eval(a->l)->doubleValue;		/*Recupera um valueDouble*/
					printf ("%i\n", cont->intergerValue);
					break;  
		// Impreme um a string
		case 'Y':	
					v2 = eval2(a->l);		/*Recupera um valueDouble STR*/
					printf ("%s\n",v2); break;  /*Função que imprime um valueDouble (string)*/
					break;

		case 'S': 	scanf("%lf", &valueDouble);
					aux1 = srch(listOfVariavel,((NameVari *)a)->name);
					aux1->valueDouble = valueDouble;
					break;
		
		case 'T': 	scanf("%s", v1);
					aux1 = srch(listOfVariavel,((NameVari *)a)->name);
					strcpy(aux1->valueString,v1);
					break;			
		
		case 'Q': 	
					printf("%s\n", ((StrVal *)a->l)->value);
					break;
					
		case 'V': 	listOfVariavel = insert_vari_float(listOfVariavel,((NameVari*)a)->name);
					break;
		case 'E': 
					listOfVariavel = insert_vari_int(listOfVariavel,((NameVari*)a)->name);
					break;
		case 'G': 
					listOfVariavel = insert_vari_str(listOfVariavel,((NameVari*)a)->name);
					break;
		case 'A':	
					listOfVariavel = insert_array(listOfVariavel,((NameVari*)a)->name,((NameVari*)a)->size);
					break;
			
		default: printf("internal error: bad node %c\n", a->nodetype);
				break;
				
	}
	return cont;
}


int yylex();
void yyerror (char *name){
	printf("%s\n", name);
}


#line 512 "rules.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    VARS = 259,
    STRING = 260,
    START = 261,
    END = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    PRINT = 266,
    PRINTS = 267,
    DECL = 268,
    SCAN = 269,
    PRINTT = 270,
    SCANS = 271,
    INGREMENTO = 272,
    DECREMENTO = 273,
    EXPONENT = 274,
    TYPEFLW = 275,
    TYPEINT = 276,
    TYPESTR = 277,
    SEPARADOR = 278,
    CMP = 279,
    IFX = 280,
    VARPREC = 281,
    DECLPREC = 282,
    NEG = 283,
    VET = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 443 "rules.y"

	float flo;
	int fn;
	int inter;
	char str[50];
	Ast *a;
	

#line 600 "rules.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  37
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

#define YYUNDEFTOK  2
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,    28,    26,     2,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   469,   469,   472,   473,   479,   480,   481,   483,   484,
     486,   487,   488,   490,   491,   492,   493,   495,   496,   497,
     498,   502,   508,   509,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   529,   530
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "VARS", "STRING", "START", "END",
  "IF", "ELSE", "WHILE", "PRINT", "PRINTS", "DECL", "SCAN", "PRINTT",
  "SCANS", "INGREMENTO", "DECREMENTO", "EXPONENT", "TYPEFLW", "TYPEINT",
  "TYPESTR", "SEPARADOR", "CMP", "'='", "'+'", "'-'", "'*'", "'/'", "IFX",
  "VARPREC", "DECLPREC", "NEG", "VET", "'('", "')'", "'{'", "'}'", "'['",
  "']'", "$accept", "val", "prog", "stmt", "list", "exp", "exp1", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    61,    43,    45,    42,    47,
     280,   281,   282,   283,   284,    40,    41,   123,   125,    91,
      93
};
# endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       4,   121,    31,    -9,     8,    23,    24,    27,    25,    35,
      36,    37,   108,   -61,   -61,   -61,   -61,     1,    71,     1,
       1,     1,     9,    -5,    69,    72,    73,    75,     9,    77,
     -61,   -61,   -61,    49,   -61,     1,     1,   125,    50,    56,
      70,   119,   -61,   -61,    57,    98,   -61,   -61,   -61,    66,
      67,    68,   110,    92,    81,     1,     1,     1,     1,     1,
       1,    89,    90,    91,    12,   -61,    86,   -61,   -61,   -61,
      99,   -61,   125,    92,   131,   131,   -12,   -12,     1,   121,
     121,    94,   104,   -61,   -61,   125,   -61,    11,    40,   -61,
     -61,   132,   -61,   -61,   120,   121,    53,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     1,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     4,    31,    34,    32,     0,     0,     8,     0,     0,
       0,     0,    36,    37,     0,     0,    11,    10,    12,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,    18,    17,    19,
       0,    29,    33,    28,    24,    25,    26,    27,     0,     0,
       0,     0,     0,    13,    35,     9,    22,     0,     0,    16,
      15,     5,    23,     7,     0,     0,     0,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,    -1,   -60,   -18,   128
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    12,    86,    87,    37,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      13,    39,    40,    41,    32,    33,    34,    55,    15,    16,
       1,    31,    56,    42,    43,     3,    17,    53,    54,     4,
      88,     5,     6,     7,     8,     9,    10,    11,    35,    23,
      18,    14,    81,    82,    45,    96,    36,    72,    73,    74,
      75,    76,    77,    19,     3,    24,    25,    26,     4,    91,
       5,     6,     7,     8,     9,    10,    11,     3,    20,    21,
      85,     4,    22,     5,     6,     7,     8,     9,    10,    11,
      27,    28,    29,    46,    38,    55,    47,    48,    93,    49,
      56,    51,    57,    58,    59,    60,    92,    92,    52,    55,
      61,    97,    62,    65,    56,    92,    57,    58,    59,    60,
      55,    66,    67,    68,    69,    56,    63,    57,    58,    59,
      60,    55,     3,    70,    78,    30,     4,    71,     5,     6,
       7,     8,     9,    10,    11,     3,    83,    79,    80,     4,
      89,     5,     6,     7,     8,     9,    10,    11,    55,    84,
      90,    94,    64,    56,    55,    57,    58,    59,    60,    56,
      55,    57,    58,    59,    60,    56,    50,    95,     0,    59,
      60
};

static const yytype_int8 yycheck[] =
{
       1,    19,    20,    21,     3,     4,     5,    19,    17,    18,
       6,    12,    24,     4,     5,     4,    25,    35,    36,     8,
      80,    10,    11,    12,    13,    14,    15,    16,    27,     4,
      39,     0,    20,    21,    39,    95,    35,    55,    56,    57,
      58,    59,    60,    35,     4,    20,    21,    22,     8,    38,
      10,    11,    12,    13,    14,    15,    16,     4,    35,    35,
      78,     8,    35,    10,    11,    12,    13,    14,    15,    16,
      35,    35,    35,     4,     3,    19,     4,     4,    38,     4,
      24,     4,    26,    27,    28,    29,    87,    88,    39,    19,
      40,    38,    36,    36,    24,    96,    26,    27,    28,    29,
      19,     3,    36,    36,    36,    24,    36,    26,    27,    28,
      29,    19,     4,     3,    25,     7,     8,    36,    10,    11,
      12,    13,    14,    15,    16,     4,    40,    37,    37,     8,
      36,    10,    11,    12,    13,    14,    15,    16,    19,    40,
      36,     9,    23,    24,    19,    26,    27,    28,    29,    24,
      19,    26,    27,    28,    29,    24,    28,    37,    -1,    28,
      29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    42,     4,     8,    10,    11,    12,    13,    14,
      15,    16,    43,    44,     0,    17,    18,    25,    39,    35,
      35,    35,    35,     4,    20,    21,    22,    35,    35,    35,
       7,    44,     3,     4,     5,    27,    35,    46,     3,    46,
      46,    46,     4,     5,    47,    39,     4,     4,     4,     4,
      47,     4,    39,    46,    46,    19,    24,    26,    27,    28,
      29,    40,    36,    36,    23,    36,     3,    36,    36,    36,
       3,    36,    46,    46,    46,    46,    46,    46,    25,    37,
      37,    20,    21,    40,    40,    46,    44,    45,    45,    36,
      36,    38,    44,    38,     9,    37,    45,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    47,    47
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     7,    11,     7,     3,     6,
       3,     3,     3,     5,     4,     6,     6,     4,     4,     4,
       2,     2,     1,     2,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     3,     1,     4,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 472 "rules.y"
                        {eval((yyvsp[0].a));}
#line 1841 "rules.tab.c"
    break;

  case 4:
#line 473 "rules.y"
                    {eval((yyvsp[0].a));}
#line 1847 "rules.tab.c"
    break;

  case 5:
#line 479 "rules.y"
                                            {(yyval.a) = newflow('I', (yyvsp[-4].a), (yyvsp[-1].a), NULL);}
#line 1853 "rules.tab.c"
    break;

  case 6:
#line 480 "rules.y"
                                                        {(yyval.a) = newflow('I', (yyvsp[-8].a), (yyvsp[-5].a), (yyvsp[-1].a));}
#line 1859 "rules.tab.c"
    break;

  case 7:
#line 481 "rules.y"
                                         {(yyval.a) = newflow('W', (yyvsp[-4].a), (yyvsp[-1].a), NULL);}
#line 1865 "rules.tab.c"
    break;

  case 8:
#line 483 "rules.y"
                                     { (yyval.a) = newasgn((yyvsp[-2].str),(yyvsp[0].a));}
#line 1871 "rules.tab.c"
    break;

  case 9:
#line 484 "rules.y"
                                 {(yyval.a) = newasgn_a((yyvsp[-5].str),(yyvsp[0].a),(yyvsp[-3].flo));}
#line 1877 "rules.tab.c"
    break;

  case 10:
#line 486 "rules.y"
                                                { (yyval.a) = newVari('E',(yyvsp[0].str));}
#line 1883 "rules.tab.c"
    break;

  case 11:
#line 487 "rules.y"
                                                { (yyval.a) = newVari('V',(yyvsp[0].str));}
#line 1889 "rules.tab.c"
    break;

  case 12:
#line 488 "rules.y"
                                                { (yyval.a) = newVari('G',(yyvsp[0].str));}
#line 1895 "rules.tab.c"
    break;

  case 13:
#line 490 "rules.y"
                                { (yyval.a) = newarray('A',(yyvsp[-3].str),(yyvsp[-1].flo));}
#line 1901 "rules.tab.c"
    break;

  case 14:
#line 491 "rules.y"
                              { (yyval.a) = newast('Q',(yyvsp[-1].a),NULL);}
#line 1907 "rules.tab.c"
    break;

  case 15:
#line 492 "rules.y"
                                                {(yyval.a) = newast('X',(yyvsp[-3].a),NULL);}
#line 1913 "rules.tab.c"
    break;

  case 16:
#line 493 "rules.y"
                                                {(yyval.a) = newast('P',(yyvsp[-3].a),NULL);}
#line 1919 "rules.tab.c"
    break;

  case 17:
#line 495 "rules.y"
                                {(yyval.a) = newast('Y',(yyvsp[-1].a),NULL);}
#line 1925 "rules.tab.c"
    break;

  case 18:
#line 496 "rules.y"
                                        {(yyval.a) = newVari('S',(yyvsp[-1].str));}
#line 1931 "rules.tab.c"
    break;

  case 19:
#line 497 "rules.y"
                                        {(yyval.a) = newVari('T',(yyvsp[-1].str));}
#line 1937 "rules.tab.c"
    break;

  case 20:
#line 499 "rules.y"
                {
			(yyval.a) = newasgn((yyvsp[-1].str), newast('+', newValorVal((yyvsp[-1].str)), newNum(1.0))); 
		}
#line 1945 "rules.tab.c"
    break;

  case 21:
#line 503 "rules.y"
                {
			(yyval.a) = newasgn((yyvsp[-1].str), newast('-', newValorVal((yyvsp[-1].str)), newNum(1.0))); 
		}
#line 1953 "rules.tab.c"
    break;

  case 22:
#line 508 "rules.y"
           {(yyval.a) = (yyvsp[0].a);}
#line 1959 "rules.tab.c"
    break;

  case 23:
#line 509 "rules.y"
                            { (yyval.a) = newast('L', (yyvsp[-1].a), (yyvsp[0].a));	}
#line 1965 "rules.tab.c"
    break;

  case 24:
#line 513 "rules.y"
                     {(yyval.a) = newast('+',(yyvsp[-2].a),(yyvsp[0].a));}
#line 1971 "rules.tab.c"
    break;

  case 25:
#line 514 "rules.y"
                     {(yyval.a) = newast('-',(yyvsp[-2].a),(yyvsp[0].a));}
#line 1977 "rules.tab.c"
    break;

  case 26:
#line 515 "rules.y"
                     {(yyval.a) = newast('*',(yyvsp[-2].a),(yyvsp[0].a));}
#line 1983 "rules.tab.c"
    break;

  case 27:
#line 516 "rules.y"
                     {(yyval.a) = newast('/',(yyvsp[-2].a),(yyvsp[0].a));}
#line 1989 "rules.tab.c"
    break;

  case 28:
#line 517 "rules.y"
                     {(yyval.a) = newcmp((yyvsp[-1].fn),(yyvsp[-2].a),(yyvsp[0].a));}
#line 1995 "rules.tab.c"
    break;

  case 29:
#line 518 "rules.y"
                     {(yyval.a) = (yyvsp[-1].a);}
#line 2001 "rules.tab.c"
    break;

  case 30:
#line 519 "rules.y"
                           {(yyval.a) = newast('M',(yyvsp[0].a),NULL);}
#line 2007 "rules.tab.c"
    break;

  case 31:
#line 520 "rules.y"
             {(yyval.a) = newNum((yyvsp[0].flo));}
#line 2013 "rules.tab.c"
    break;

  case 32:
#line 521 "rules.y"
                {(yyval.a) = newString((yyvsp[0].str));}
#line 2019 "rules.tab.c"
    break;

  case 33:
#line 522 "rules.y"
                          {(yyval.a) = newast('^', (yyvsp[-2].a), (yyvsp[0].a));}
#line 2025 "rules.tab.c"
    break;

  case 34:
#line 523 "rules.y"
                          {(yyval.a) = newValorVal((yyvsp[0].str));}
#line 2031 "rules.tab.c"
    break;

  case 35:
#line 524 "rules.y"
                        {(yyval.a) = newValorVal_a((yyvsp[-3].str),(yyvsp[-1].flo));}
#line 2037 "rules.tab.c"
    break;

  case 36:
#line 529 "rules.y"
              {(yyval.a) = newValorValS((yyvsp[0].str));}
#line 2043 "rules.tab.c"
    break;

  case 37:
#line 530 "rules.y"
                 {(yyval.a) = newString((yyvsp[0].str));}
#line 2049 "rules.tab.c"
    break;


#line 2053 "rules.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 532 "rules.y"


#include "lex.yy.c"

int main(){
	
	yyin=fopen("example.cs","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}
