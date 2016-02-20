#ifndef NODE_H
#define NODE_H

typedef struct node
{
	struct node *seguinte;
	void *item;
} Node;

typedef struct inbox
{
    Node *primeira, *ultima;
    int tamanho;
} Inbox;

void initlists(Inbox *vec, int N);

#endif
