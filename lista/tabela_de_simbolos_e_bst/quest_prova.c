#include <stdio.h>
#include <stdlib.h>


#define hash(v,M) (v%M)

typedef struct Item{
    int chave;
    int pos;
    struct Item *prox;
}Item;

Item **ht;
int M, indice;

void HTinit(int max){
    M = max;
    ht = malloc(sizeof(Item*) * M);

    for(int i=0; i < M; i ++){
        ht[i] = NULL;
    }
}

void HTinsert(int chave, int pos){
    int i = hash(chave,M);

    Item *novo = malloc(sizeof(Item));
    novo->chave = chave;
    novo->prox = NULL;
    novo->pos = pos;
    

    if(ht[i] == NULL){
        ht[i] = novo;
    } else {
        Item *p = ht[i];

        while(p->prox != NULL){
            p = p->prox;
        }
        p->prox = novo;
    }
}

int HTsearch_kth(int chave, int k){
    int h = hash(chave,M);
    Item *p = ht[h];

    int cont = 0;

    while(p != NULL){
        if(p->chave == chave){
            cont ++;
            if(k == cont){
                return p->pos;
            }
        }
    
        p = p->prox;
    }

    return 0;
}

void HTfree(){
    for(int i = 0; i < M; i++){
        Item *p = ht[i];
        while(p != NULL){
            Item *tmp = p;
            p = p->prox;
            free(tmp);
        }
    }
    free(ht);
}



int main(){

    int tamVet, qtdEntradas;

    while(scanf("%d %d", &tamVet, &qtdEntradas) == 2){
        if (ht != NULL) HTfree();
        HTinit(tamVet);
        int resultado[qtdEntradas];

        for(int i = 0; i < tamVet; i++){
            int chave;
            scanf("%d", &chave);
            HTinsert(chave,i + 1);
        }

        for(int i = 0; i < qtdEntradas; i++){
            int k,chave;
            scanf("%d %d", &k, &chave);

            int res = HTsearch_kth(chave,k);
            resultado[i] = res;
        }

        for(int i = 0; i < qtdEntradas; i ++){
            printf("%d\n", resultado[i]);
        }
    }

}