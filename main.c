/* PROJECTO IAED - 2013/2014 - 2o SEMESTRE
   JOAO LEITE - JOAO TOMAZIO - TIAGO FERNANDES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mensagens.h"
#include "queue.h"


#define COMANDO_LEN	11					/* tamanho maximo do comando */
#define MENSAGEM_LEN 501					/* tamanho maximo do texto da mensagem */


void enviar(Inbox *inbox, int emissor, int receptor, char *texto);
void processar(Inbox *inbox, int receptor);
void listar(Inbox *inbox, int receptor);
void listarsorted(Inbox *inbox, int receptor);
void apagarmsg(Inbox *inbox, int receptor);



/* MAIN */
int main()
{
	int N, emissor, receptor, i;
	char c, buffer[MENSAGEM_LEN], command[COMANDO_LEN];
	Inbox *vctinbox;
	
	scanf("%d", &N);	/* Scan do numero de utilizadores */

	vctinbox = (Inbox*) malloc(sizeof(Inbox) * N);	/* Alocar memoria para o vector de inbox's */
	
	initlists(vctinbox, N);		/* Inicializa vector de inbox's */

	while(1)
	{
		scanf("%s", command);	/* Scan do comando */

		if (strcmp(command, "send") == 0)
		{
			scanf("%d", &emissor);
			scanf("%d", &receptor);

			getchar();	/* Para ignorar um " " */					

			for (i = 0; i < MENSAGEM_LEN - 1 && (c = getchar()) != EOF && c != '\n'; i++)    /* le caracteres do texto e coloca dentro do buffer */
				buffer[i] = c;
				
			buffer[i] = '\0';    /* adicionar \0 no final da string */
			
			enviar(vctinbox, emissor, receptor, buffer);
		}
		else if (strcmp(command, "process") == 0)
		{
			scanf("%d", &receptor);
			
			if (vctinbox[receptor].primeira == NULL)    /* se inbox vazia */
				puts("NULL");
			else
				processar(vctinbox, receptor); 
		}
		else if (strcmp(command, "list") == 0)
		{
			scanf("%d", &receptor);
			
			if (vctinbox[receptor].primeira == NULL)    /* se inbox vazia */
				puts("NULL");
			else
				listar(vctinbox, receptor);
		}
		else if (strcmp(command, "listsorted") == 0)
		{
			scanf("%d", &receptor);
			
			if (vctinbox[receptor].primeira == NULL)    /* se inbox vazia */
				puts("NULL");
			else
				listarsorted(vctinbox, receptor);
		}
		else if (strcmp(command, "kill") == 0)
		{
			scanf("%d", &receptor);

			while (vctinbox[receptor].primeira != NULL)     /* apaga todos os nodes e suas mensagens da inbox */
            	apagarmsg(vctinbox, receptor);
		}	
		
		else if (strcmp(command, "quit") == 0)
		{	
			for (i = 0; i < N; i++)    /* apaga todos os nodes de todas as inbox's */
			{
				while (vctinbox[i].primeira != NULL)    /* percorrer todos os nodes da inbox */
					apagarmsg(vctinbox, i);
			}
			break;		/* sai do programa */
		}
	}
	
	return 0;
}


void enviar(Inbox *inbox, int emissor, int receptor, char *texto)    /* junta novo node, com a sua mensagem, a inbox */
{
    Node *nova;
    Mensagem *mensagem;
    char *textonovo;
    int tamanho;
    
    nova = (Node*) malloc(sizeof(Node));    /* aloca memoria para o novo node */
    nova -> seguinte = NULL;    /* node mais recente */
    
    mensagem = (Mensagem*) malloc(sizeof(Mensagem));    /* aloca memoria para a mensagem do novo node */

    tamanho = strlen(texto) + 1;
    textonovo = (char*) malloc(sizeof(char) * tamanho);    /* aloca memoria para o texto da mensagem do novo node */		
    strcpy(textonovo,texto);
    
    mensagem -> texto = textonovo;	    /* texto do item mensagem */
    mensagem -> emissor = emissor;	    /* regista emissor do item mensagem */

    nova->item = (void*) mensagem;
   	

    if (inbox[receptor].primeira == NULL)    /* caso seja o primeiro node a ser introduzido na inbox */
    {
        inbox[receptor].primeira = nova;
        inbox[receptor].ultima = nova;
    }
    else    /* se nao for o primeiro, junta novo node a cadeia da inbox ja existente */
    {
        inbox[receptor].ultima->seguinte = nova;
        inbox[receptor].ultima = inbox[receptor].ultima -> seguinte;
    }
    inbox[receptor].tamanho++;    /* incrementa tamanho da inbox */
}

void processar(Inbox *inbox, int receptor)    /* imprime a primeira mensagem e elimina o primeiro node da inbox */
{		
   	imprime(inbox[receptor].primeira->item, receptor);   /* imprime a mensagem */
    apagarmsg(inbox, receptor);    /* elimina o node */
}



void listar(Inbox *inbox, int receptor)    /* imprime todas as mensagens da inbox, por ordem de chegada a inbox */
{
    Node *node;
    
    for(node = inbox[receptor].primeira; node != NULL; node = node -> seguinte)
            imprime(node -> item, receptor);
}



void listarsorted(Inbox *inbox, int receptor) /* cria vetor auxiliar vec, mete mensagens da inbox no vec, organiza vec por qsort segundo cmpMessages e imprime vec ordenado */
{
	Node *t;
	Mensagem *vec;
	Mensagem *tmp;
	int i = 0;
	
	vec = (Mensagem*) malloc(sizeof(Mensagem) * inbox[receptor].tamanho);	/* aloca memoria para vector de mensagens auxiliar */
	
	for (t = inbox[receptor].primeira; t != NULL; t = t -> seguinte)		/* adiciona mensagens dos nodes da inbox ao vector */
	{
		tmp=(Mensagem*) (t -> item);
		vec[i] = *tmp;
		i++;
	}
	
	qsort(vec, inbox[receptor].tamanho, sizeof(Mensagem) ,cmpMessages);		/* organiza vec por quicksort segundo a funcao de comparacao cmpMessages */
	
	for (i = 0; i < inbox[receptor].tamanho; i++)			/* imprime as mensagens do vector ordenado */
		imprime(&vec[i], receptor);
	
	free(vec);				/* liberta memoria do vector auxiliar */
}

void apagarmsg(Inbox *inbox, int receptor)    /* elimina o primeiro node da cadeia da inbox, reorganiza a inbox e liberta memoria do node, da sua mensagem e do seu texto */
{
    Node *antiga;
    Mensagem *msg;
    
    antiga = inbox[receptor].primeira;    /* antiga e o node a eliminar */
    inbox[receptor].primeira = antiga -> seguinte;    /* a segunda vai passar a ser a primeira */

    msg=antiga->item;
    free(msg->texto);
    free(antiga -> item);        /* liberta memoria da mensagem do node */
    free(antiga);    /* liberta memoria do node */

    inbox[receptor].tamanho--;    /* decrementa tamanho da inbox */
}

