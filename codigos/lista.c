#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto {
    float x;
    float y;
    struct Ponto *prox;
} Ponto;

Ponto *comeco = NULL;

void add(float x, float y){
    Ponto *p = (Ponto*) malloc(sizeof(Ponto)); // Alocação dinamica
    p->x = x;
    p->y = y;
    p->prox = comeco; // o proximo será null nesse ponto 
    comeco = p; // Agora "p" é o primeiro item da lista
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
        printf("\n Acabou");
    
    printf("( %.1f, %.1f )\n", p->x,p->y);
    imprimirRecursivamente(p->prox);
}

int main(){

    add(1,2);
    add(5,4);
    add(6,7);

    imprimirRecursivamente(comeco);

    return 0;
}