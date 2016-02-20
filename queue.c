#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void initlists(Inbox *vec, int N)	/* inicializa todas as inbox's, pondo os seus ponteiros primeira e ultima a apontar para NULL */
{
    int i;
    

    for(i = 0; i < N; i++)
    {
        vec[i].primeira = NULL;
        vec[i].ultima = NULL;
    }
}


