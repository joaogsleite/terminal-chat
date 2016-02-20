#include <stdio.h>
#include <string.h>
#include "mensagens.h"


int cmpMessages(const void *va, const void *vb)			/* compara 2 mensagens e retorna um inteiro correspondente a ordem alfabetica ou de emissor da mensagem*/
{	
	
	Mensagem *a = (Mensagem*) va;			/*	transforma parametros em ponteiros para mensagem */
	Mensagem *b = (Mensagem*) vb;
	
	int strcompare = strcmp(a -> texto, b -> texto);
	
	if (strcompare != 0)						/* se texto diferente, retorna negativo se primeiro menor e positivo se vice versa */
		return strcompare;
		
	return (a -> emissor) - (b -> emissor);		/* se texto igual, retorna negativo se primeiro tiver emissor menor e positivo se vice versa */
}


void imprime(const void *mensagem, int receptor)    /* imprime a mensagem no formato: receptor, emissor, texto */
{
	Mensagem *msg= (Mensagem*) mensagem;
	printf("%d %d %s\n", receptor, msg -> emissor, msg -> texto);
}
