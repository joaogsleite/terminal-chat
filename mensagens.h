#ifndef MENSAGENS_H
#define MENSAGENS_H

typedef struct mensagem
{
    char *texto;
    int emissor;
} Mensagem;

void imprime(const void *mensagem, int receptor);
int cmpMessages(const void *va, const void *vb);

#endif
