//Essa é uma implementação de tabela Hash com Encadeamento Separado

#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
    int chave;
    long elemento;
    struct Item* prox;
}Item;

#define hash(v,M) ((v%M)) //Função hash simples

Item **ht; // Tabela Hash como vetor de ponteiros para ITEM.
int M; //Tamanho da tabela

//inicializa a tabela Hash
void HTinit(int max){

    M = max;
    ht = malloc(sizeof(Item*) * M);
    for (int i = 0; i < M; i++)
        ht[i] = NULL;
    
}

void HTinsert(int chave, long valor){
    int i = hash(chave,M); //calcula índice.
    Item *novo = malloc(sizeof(Item));
    novo->chave = chave;
    novo->elemento = valor;

    //encadeamento : insere no inicio da lista
    novo->prox = ht[i];
    ht[i] = novo;

    printf("Inserido chave=%d, valor=%ld na posicao %d\n", chave, valor, i);
}

Item* HTsearch(int chave){
    int i = hash(chave,M);
    Item *p = ht[i];

    while(p != NULL){
        if(p->chave == chave)
            return p;
        p = p->prox;
    }

    return NULL;
}

int main() {
    HTinit(5); // Tamanho pequeno de propósito para provocar colisões

    HTinsert(1, 100);
    HTinsert(6, 200); // Colide com 1 (mesmo índice 1)
    HTinsert(11, 300); // Colide com 1 e 6
    HTinsert(3, 400);

    int chaves[] = {1, 6, 11, 3, 9};
    for (int i = 0; i < 5; i++) {
        Item* resultado = HTsearch(chaves[i]);
        if (resultado)
            printf("Encontrado: chave=%d, valor=%ld\n", resultado->chave, resultado->elemento);
        else
            printf("Chave %d não encontrada.\n", chaves[i]);
    }

    return 0;
}


