#include <stdio.h>
#include <stdlib.h>

#define hash(v,M) ((v%M))
#define key(A) (A->chave)
#define eq(A,B) ((A) == (B))
#define null(A) (A == NULL)

typedef struct Item{
    int chave;
    struct Item *prox;
}Item;

Item **ht;
Item NULLItem = {-1,NULL};
int M;

void HTinit(int max){
    M = max;

    ht = malloc(sizeof(Item*) * M);

    for(int i = 0; i < M; i ++){
        ht[i] = NULL;
    }
}

void HTinsert(int chave){
    int i = hash(chave, M);

    Item *novo = malloc(sizeof(Item));
    novo->chave = chave;

    Item *p = ht[i];

    novo->prox = ht[i];
    ht[i] = novo;
}

Item* HTsearch(int chave){
    int i = hash(chave, M);

    while(!null(ht[i])){
        if(eq(key(ht[i]),chave)){
            return ht[i];
        }
        i = (i + 1) % M;
    }

    return NULL;
}

void grau(Item **ht){
    
    for(int i = 0; i < M; i ++){

        int col = 0;
        Item *p = ht[i];

        while(!null(p)){
            col++;
            p = p->prox;
        }

        printf("O total de colisões no indice %d : %d\n", i, col - 1); //O primeiro item não é colisão, então tem que ter o col - 1.

    }
}
