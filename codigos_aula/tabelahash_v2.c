#include <stdio.h>
#include <stdlib.h>

//HTinit HTinsert HTSearch 

#define hash(v,M) (v%M)
#define key(A) (A->chave)
#define null(A) (A == NULL)
#define eq(A,B) ((A) == (B))

typedef struct Item{
    int chave;
    struct Item *prox;
}Item;

Item **ht;
int M;

void HTinit(int max){

    M = max;
    ht = malloc(sizeof(Item*) * M);

    for(int i = 0; i < M; i++){
        ht[i] = NULL;
    }
}

void HTinsert(Item *item){
    int i = hash(key(item), M);

    item->prox = ht[i];
    ht[i] = item;

}

Item* HTsearch(int chave){
    int i = hash(chave,M);

    while(!null(ht[i])){
        if(ht[i]->chave == chave){
            return ht[i];
        }

        i = (i + 1) % M;
    }

    return NULL;
}


int main(){

    HTinit(50);

    Item *item1 = malloc(sizeof(Item));
    item1->chave = 10;
    item1->prox = NULL;


    Item *item2 = malloc(sizeof(Item));
    item2->chave = 30;
    item2->prox = NULL;


    Item *item3 = malloc(sizeof(Item));
    item3->chave = 44;
    item3->prox = NULL;

    Item *item4 = malloc(sizeof(Item));
    item4->chave = 1;
    item4->prox = NULL;

    HTinsert(item1);
    HTinsert(item2);
    HTinsert(item3);
    HTinsert(item4);


    printf("Buscando pelo item : 10\n");
    
    if(HTsearch(10)){
        printf("Encontrado!\n");
    } else {
        printf("Não encontrado !\n");
    }


    printf("Buscando pelo item : 50\n");
    
    if(HTsearch(50)){
        printf("Encontrado!\n");
    } else {
        printf("Não encontrado !\n");
    }

    return 0;
}