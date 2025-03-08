#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No *prox;
}No;

No *topo = NULL;

void push(int valor){
    
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    
    novo->prox = topo;
    topo = novo;
}

int pop(){

    if(topo == NULL){
        printf("Pilha vazia ! \n");
        return -1;
    }
    
    No *remover = topo;
    int valor = remover->valor;
    topo = topo->prox;
    free(remover);
    return valor;
}

int peek(){
    if(topo == NULL){
        printf("A lista está vazia !");
        return -1;
    }

    return topo->valor;
}

void imprimir(No *aux){
    if(topo == NULL){
        printf("A lista está vazia !");
        return;
    }

    if(aux == NULL){
        printf("Acabou \n");
        return;
    }

    printf("Valor : %d \n", aux->valor);
    imprimir(aux->prox);
}


int main(){
    push(10);
    push(20);
    push(30);
    imprimir(topo);  // Pilha: 30 20 10

    printf("Topo: %d\n", peek()); // Topo: 30

    printf("Removido: %d\n", pop());  // Removido: 30
    imprimir(topo);;  // Pilha: 20 10

    return 0;
}