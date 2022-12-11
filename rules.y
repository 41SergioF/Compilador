%{
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
		
		case 'X': 	cont->intergerValue = eval(a->l)->intergerValue;		/*Recupera um valueDouble*/
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

%}

%union{
	float flo;
	int fn;
	int inter;
	char str[50];
	Ast *a;
	}

%token <flo>NUM
%token <str>VARS
%token <str>STRING
%token START END IF ELSE WHILE PRINT PRINTS DECL SCAN PRINTT SCANS INGREMENTO DECREMENTO
%token EXPONENT TYPEFLW TYPEINT TYPESTR SEPARADOR
%token <fn> CMP

%right '='
%left '+' '-'
%left '*' '/'
%left CMP

%type <a> exp list stmt prog exp1

%nonassoc IFX VARPREC DECLPREC NEG VET 

%%

val: START prog END
	;

prog: stmt 		{eval($1);}  /*Inicia e execução da árvore de derivação*/
	| prog stmt {eval($2);}	 /*Inicia e execução da árvore de derivação*/
	;
	
/*Funções para análise sintática e criação dos nós na AST*/	
/*Verifique q nenhuma operação é realizada na ação semântica, apenas são criados nós na árvore de derivação com suas respectivas operações*/
	
stmt: IF '(' exp ')' '{' list '}' %prec IFX {$$ = newflow('I', $3, $6, NULL);}
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}' {$$ = newflow('I', $3, $6, $10);}
	| WHILE '(' exp ')' '{' list '}' {$$ = newflow('W', $3, $6, NULL);}

	| VARS '=' exp %prec VARPREC { $$ = newasgn($1,$3);}
	| VARS '['NUM']' '=' exp {$$ = newasgn_a($1,$6,$3);}

	| DECL TYPEINT VARS	 %prec DECLPREC { $$ = newVari('E',$3);} //Variáreis unicas
	| DECL TYPEFLW VARS	 %prec DECLPREC { $$ = newVari('V',$3);}
	| DECL TYPESTR VARS	 %prec DECLPREC { $$ = newVari('G',$3);}

	| DECL VARS '['NUM']'	{ $$ = newarray('A',$2,$4);}
	| PRINTS '(' exp1 ')' { $$ = newast('Q',$3,NULL);}
	| PRINT '(' exp SEPARADOR TYPEINT ')' 	{$$ = newast('X',$3,NULL);}
	| PRINT '(' exp SEPARADOR TYPEFLW ')' 	{$$ = newast('P',$3,NULL);}
	//| PRINT '(' exp SEPARADOR TYPEFLW ')' 	{$$ = newast('P',$3,NULL);}
	| PRINTT '(' exp1 ')' 	{$$ = newast('Y',$3,NULL);}
	| SCAN '('VARS')'		{$$ = newVari('S',$3);}
	| SCANS '('VARS')'		{$$ = newVari('T',$3);}
	| VARS INGREMENTO
		{
			$$ = newasgn($1, newast('+', newValorVal($1), newNum(1.0))); 
		}
	| VARS DECREMENTO
		{
			$$ = newasgn($1, newast('-', newValorVal($1), newNum(1.0))); 
		}
	;

list: stmt {$$ = $1;}
		| list stmt { $$ = newast('L', $1, $2);	}
		;
	
exp: 
	 exp '+' exp {$$ = newast('+',$1,$3);}		/*Expressões matemáticas*/
	|exp '-' exp {$$ = newast('-',$1,$3);}
	|exp '*' exp {$$ = newast('*',$1,$3);}
	|exp '/' exp {$$ = newast('/',$1,$3);}
	|exp CMP exp {$$ = newcmp($2,$1,$3);}		/*Testes condicionais*/
	|'(' exp ')' {$$ = $2;}
	|'-' exp %prec NEG {$$ = newast('M',$2,NULL);}
	|NUM {$$ = newNum($1);}						/*token de um número*/
	|STRING {$$ = newString($1);}						/*token de um número*/
	|exp EXPONENT exp {$$ = newast('^', $1, $3);}
	|VARS 	%prec VET {$$ = newValorVal($1);}		/*token de uma variável*/
	|VARS '['NUM']' {$$ = newValorVal_a($1,$3);}				/*token de uma variável*/
		
	;

exp1: 
	 VARS {$$ = newValorValS($1);}
	| STRING {$$ = newString($1);}		
	;
%%

#include "lex.yy.c"

int main(){
	
	yyin=fopen("example.cs","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}