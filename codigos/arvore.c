#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int valor;
    struct Nodo *esq;
    struct Nodo *dir;
}Nodo;

Nodo* create(int valor){
    Nodo *no = (Nodo*) malloc(sizeof(Nodo));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

void add(Nodo *n, int valor){
    if(valor < n->valor){
        if(n->esq == NULL)
            n->esq = create(valor);
        else
            add(n->esq,valor);
    } else {
        if(n->dir == NULL)
            n->dir = create(valor);
        else
            add(n->dir,valor);
    }
}

void imprimir(Nodo *n){
    if(n == NULL)
        return;
    imprimir(n->esq);
    printf("\n %d",n->valor);
    imprimir(n->dir);
}

int main(){

    Nodo *nodo5 = create(5);

    add(nodo5,2);
    add(nodo5,1);
    add(nodo5,8);
    add(nodo5,4);

    imprimir(nodo5);
    
    return 0;
}