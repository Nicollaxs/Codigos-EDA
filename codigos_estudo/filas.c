#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *prox;
} No;


No *comeco = NULL;
No *fim = NULL;

void enqueue(int valor){

    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if(comeco == NULL){ //caso a lista esteja vazia
        comeco = novo;
        fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }
}

int dequeue(){
    if(comeco == NULL){
        printf("Fila vazia ! \n");
        return -1; 
    } 

    No *remover = comeco;
    int valor = comeco->valor;
    comeco = comeco->prox;

    if(comeco == NULL) // Caso a lista fique vazia
        fim = NULL;

    free(remover);
    return valor;
}

int peek(){

    if(comeco == NULL){
        printf("Lista vazia! \n");
        return -1;
    }

    return comeco->valor;
}

void imprimir(No *aux){
    if(aux == NULL){
        printf("Acabou \n");
        return;
    }
    printf("Valor : %d \n", aux->valor);
    imprimir(aux->prox);
}



int main(){

    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);

    imprimir(comeco);

    printf("---------- \n");
    printf("Valor removido : %d \n", dequeue());
    imprimir(comeco);

    return 0;
}