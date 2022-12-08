%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>	

char var_work_string[50];
	
	typedef struct vars{//estrutura de uma variável
		char name[50];
		double valor;
		char string[200];
		struct vars * prox;
	}VARI;
	
	
	//insertVarere uma nova variável na lista de variáveis
	VARI *insertVar(VARI*l,char n[]){
		VARI*new =(VARI*)malloc(sizeof(VARI));
		strcpy(new->name,n);
		new->prox = l;
		return new;
	}
	
	//busca uma variável na lista de variáveis
	VARI *searchVar(VARI*l,char n[]){
		VARI*aux = l;
		while(aux != NULL){
			if(strcmp(n,aux->name)==0)
				return aux;
			aux = aux->prox;
		}
		return aux;
	}
	
		
/*O node type serve para indicar o tipo de nó que está na árvore. 
Isso serve para a função eval() entender o que realizar naquele nó*/
typedef struct ast { /*Estrutura de um nó*/
	int nodetype;
	struct ast *l; /*Esquerda*/
	struct ast *r; /*Direita*/
}Ast; 

typedef struct numval { /*Estrutura de um número*/
	int nodetype;
	double number;
}Numval;

typedef struct strval { /*Estrutura de a string*/
	int nodetype;
	char string[50];
}Strval;

/*Estrutura de um nome de variável, 
nesse exemplo uma variável é um número no vetor var[26]*/	
typedef struct VarName {
	int nodetype;
	char var[50];
}VarName;

typedef struct flow { /*Estrutura de um desvio (if/else/while)*/
	int nodetype;
	Ast *cond;		/*condição*/
	Ast *tl;		/*then, ou seja, verdade*/
	Ast *el;		/*else*/
}Flow;

/*Estrutura para um nó de atribuição.
	Para atrubior o valor de v em s*/
typedef struct symasgn {  
	int nodetype;
	char s[50];
	Ast *v;
}Symasgn;


VARI *l1; /*Variáveis*/
VARI *aux;

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
 
Ast * newvari(int nodetype, char nome[50]) { /*Função que cria uma nova variável*/
	VarName *a = (VarName*) malloc(sizeof(VarName));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = nodetype;;
	strcpy(a->var,nome);
	return (Ast*)a;
}

Ast * newnum(double d) { /*Função de que cria um novo número*/
	Numval *a = (Numval*) malloc(sizeof(Numval));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'K';
	a->number = d;
	return (Ast*)a;
}


Ast * newString(char str[]) { /*Função de que cria uma nova string*/
	Strval *a = (Strval*) malloc(sizeof(Strval));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'S';
	strcpy(a->string, str);
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
	a->nodetype = '0' + cmptype; /*Para pegar o tipo de teste, definido no arquivo.l e utilizar na função eval()*/
	a->l = l;
	a->r = r;
	return a;
}

Ast * newasgn(char s[50], Ast *v) { /*Função para um nó de atribuição*/
	Symasgn *a = (Symasgn*)malloc(sizeof(Symasgn));
	if(!a) {
		printf("out of space");
	exit(0);
	}
	a->nodetype = '=';
	strcpy(a->s,s);
	//a->s = s; /*Símbolo/variável*/
	a->v = v; /*Valor*/
	return (Ast *)a;
}


Ast * newValorVal(char s[50]) { /*Função que recupera o nome/referência de uma variável, neste caso o número*/
	
	VarName *a = (VarName*) malloc(sizeof(VarName));
	if(!a) {
		printf("out of space");
		exit(0);
	}
	a->nodetype = 'N';
	strcpy(a->var,s);
	return (Ast*)a;
	
}

char* eval2(Ast *a){
	char *v2;
	switch(a->nodetype) {
		
		case 'S':
			return ((Strval *)a)->string;
			break;

		default: printf("internal error: bad node %c\n", a->nodetype);
				break;
	}
	return v2;
}

double eval(Ast *a) { /*Função que executa operações a partir de um nó*/
	double v;
	char* stringVar;
	VARI * aux1;
	if(!a) {
		printf("internal error, null eval");
		return 0.0;
	}
	switch(a->nodetype) {
		case 'K': v = ((Numval *)a)->number; break; 	/*Recupera um número*/
		case 'S': strcpy(var_work_string, ((Strval *)a)->string);		/*Recupera um valor*/
				printf ("%s\n",var_work_string); 
				break;
		case 'N': 
			aux1 = searchVar(l1,((VarName *)a)->var);
			v = aux1->valor;
			break;
			//printf("%ld %ld\n", eval(a->l), eval(a->r));
		case '+': v = eval(a->l) + eval(a->r); break;	/*Operações "árv esq   +   árv dir"*/
		case '-': v = eval(a->l) - eval(a->r); break;	/*Operações*/
		case '*': v = eval(a->l) * eval(a->r); break;	/*Operações*/
		case '/': v = eval(a->l) / eval(a->r); break; /*Operações*/
		case 'M': v = -eval(a->l); break;				/*Operações, número negativo*/
	
		case '^': v = pow(eval(a->l), eval(a->r)); break; //carlos

		case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;	/*Operações lógicas. "árv esq   >   árv dir"  Se verdade 1, falso 0*/
		case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;
		case '3': v = (eval(a->l) != eval(a->r))? 1 : 0; break;
		case '4': v = (eval(a->l) == eval(a->r))? 1 : 0; break;
		case '5': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;
		case '6': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;
		
		case '=':
			// inicialmente verificar se a variável existe
			v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
			aux = searchVar(l1,((Symasgn *)a)->s);

			if (aux == NULL){
				l1 = insertVar(l1,((Symasgn*)a)->s);
				aux = searchVar(l1,((Symasgn *)a)->s);

				//printf ("Variável não declarada: %s\n",((Symasgn *)a)->s);
			}
			aux->valor = v;			
		
			break;
		
		case 'I':						/*CASO IF*/
			if (eval(((Flow *)a)->cond) != 0) {	/*executa a condição / teste*/
				if (((Flow *)a)->tl)		/*Se existir árvore*/
					v = eval(((Flow *)a)->tl); /*Verdade*/
				else
					v = 0.0;
			} else {
				if( ((Flow *)a)->el) {
					v = eval(((Flow *)a)->el); /*Falso*/
				} else
					v = 0.0;
				}
			break;
		case 'O':
			scanf("%lf", &v);
			aux1 = searchVar(l1, ((VarName *)a)->var);
			aux1->valor = v;

		case 'W':
			v = 0.0;
			if( ((Flow *)a)->tl) {
				while( eval(((Flow *)a)->cond) != 0){
					v = eval(((Flow *)a)->tl);
				}
			}
		break;
			
		case 'L': 	eval(a->l);
					v = eval(a->r);
					break; /*Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos*/
		
		case 'P': 	v = eval(a->l);		/*Recupera um valor*/
					printf ("%.2f\n",v); 
					break;  /*Função que imprime um valor*/
		
		case 'Q': 	
					printf("%s\n", ((Strval *)a->l)->string);
					break;  /*Função que imprime um valor*/
		
		case 'V': 	l1 = insertVar(l1,((VarName*)a)->var);
					break;
			
		default: printf("internal error: bad node %c\n", a->nodetype);
				
	}
	return v;
}

int yylex();
void yyerror (char *s){
	printf("%s\n", s);
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
%token START END IF ELSE WHILE PRINT PRINTS SCAN DECL INGREMENTO DECREMENTO
%token <str>STRING
%token <fn> CMP
%token EXPONENT

%right '='
%left '+' '-'
%left '*' '/'
%left CMP
%left EXPONENT


%type <a> exp list stmt prog exp2

%nonassoc IFX NEG

%%

val: START prog END
	;

prog: stmt 		{eval($1);}  /*Inicia e execução da árvore de derivação*/
	| prog stmt {eval($2);}	 /*Inicia e execução da árvore de derivação*/
	;
	
/*Funções para análise sintática e criação dos nós na AST*/	
/*Verifique q nenhuma operação é realizada na ação semântica, apenas são criados nós na árvore de derivação com suas respectivas operações*/
	
stmt: IF '(' exp ')' '{' list '}' %prec IFX
		{
			$$ = newflow('I', $3, $6, NULL);
		}
	
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}'
		{
			$$ = newflow('I', $3, $6, $10);
		}

	| WHILE '(' exp ')' '{' list '}'
		{
			$$ = newflow('W', $3, $6, NULL);
		}

	| VARS '=' exp
		{
			$$ = newasgn($1,$3);
		}
	| PRINT '(' exp ')'
		{
			$$ = newast('P',$3,NULL);
		}
	| PRINTS '(' exp2 ')'
		{
			$$ = newast('Q',$3,NULL);
		}
	| SCAN '(' VARS ')'
		{
			$$ = newvari('O', $3);
		}
	| DECL VARS
		{
			$$ = newvari('V',$2);
		}
	| VARS INGREMENTO
		{
			$$ = newasgn($1, newast('+', newValorVal($1), newnum(1.0))); 
		}
	| VARS DECREMENTO
		{
			$$ = newasgn($1, newast('-', newValorVal($1), newnum(1.0))); 
		}

;	

list:	  stmt{$$ = $1;}
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
	|exp EXPONENT exp {$$ = newast('^', $1, $3);}
	|NUM {$$ = newnum($1);}						/*token de um número*/
	|VARS {$$ = newValorVal($1);}				/*token de uma variável*/

	;

exp2: STRING {
		$$ = newString($1);
	}
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

