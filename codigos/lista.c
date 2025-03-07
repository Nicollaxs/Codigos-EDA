#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto {
    float x;
    float y;
    struct Ponto *prox;
} Ponto;

Ponto *comeco = NULL;

void addComeco(float x, float y){
    Ponto *p = (Ponto*) malloc(sizeof(Ponto)); // Alocação dinamica
    p->x = x;
    p->y = y;
    p->prox = comeco; // o proximo será null nesse ponto ou caso tenha algum item na lista irá apontar para este item
    comeco = p; // Agora "p" é o primeiro item da lista
}

void addFim(float x, float y){

    Ponto *novo = (Ponto*) malloc(sizeof(Ponto));
    novo->x = x;
    novo->y = y;
    novo->prox = NULL;

    if(comeco == NULL){
        comeco = novo;
    } else {
        Ponto *aux = comeco;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void addFimRecursivamente(Ponto *aux, float x, float y){

    if(aux->prox == NULL){
        Ponto *novo = (Ponto*) malloc(sizeof(Ponto));
        novo->x = x;
        novo->y = y;
        novo->prox = NULL;
        aux->prox = novo;
    } else {
        addFimRecursivamente(aux->prox,x,y);
    }

}

void imprimir(){
    Ponto *var = comeco;
    while(var != NULL){
        printf("( %.1f, %.1f )\n", var->x,var->y);
        var = var->prox;
    }
}

void imprimirRecursivamente(Ponto *p){
    if(p == NULL)
        printf("\n Deu certo");
    
    printf("( %.1f, %.1f )\n", p->x,p->y);
    imprimirRecursivamente(p->prox);
}

int main(){

    addComeco(1,2);
    addComeco(5,4);
    addComeco(6,7);

    addFimRecursivamente(comeco,8,9);
    addFimRecursivamente(comeco,10,11);

    imprimirRecursivamente(comeco);

    return 0;
}