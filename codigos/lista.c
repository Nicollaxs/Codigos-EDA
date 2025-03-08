#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto {
    float x;
    float y;
    struct Ponto *prox;
} Ponto;

Ponto *comeco = NULL;
int length = 0;

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

void addIndex(float x, float y, int index){ //função que adiciona itens em posiçoes arbitrarias
    
    Ponto *novo = (Ponto*) malloc(sizeof(Ponto));
    novo->x = x;
    novo->y = y;

    if(index > length){
        printf("Posição Inválida !");
    } else {
        if(index == 0){ // verifica se é o primeiro item da lista
            novo->prox = comeco;
            comeco = novo;
        } else { // Caso não seja o primeiro item da lista, buscaremos o ponto referente ao index
            Ponto *aux = comeco; 
            int i = 0;
            while(i != index-1){
                aux = aux->prox;
                i++;
            }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    length ++;
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

void removeIndex(int index){
    if(index > length || length == 0){
        printf("Posicao Invalida ou Lista Vazia \n");
    } else {
        if(index == 0){
            comeco = comeco->prox;
        } else {
            Ponto *aux = comeco;
            int i = 0;
            while(i != index-1){
                aux = aux->prox;
                i++;
            }
            aux->prox = aux->prox->prox;
        }
    length--;
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
        printf("\n Acabou");
    
    printf("( %.1f, %.1f )\n", p->x,p->y);
    imprimirRecursivamente(p->prox);
}

int main(){


    addIndex(1,1,0);
    addIndex(2,4,1);
    addIndex(4,16,2);

    addIndex(3,9,2);
    addIndex(0,0,0);

    removeIndex(0);
    removeIndex(2);

    // addComeco(1,2);
    // addComeco(5,4);
    // addComeco(6,7); 

    // addFimRecursivamente(comeco,8,9);
    // addFimRecursivamente(comeco,10,11);

    imprimirRecursivamente(comeco);

    return 0;
}