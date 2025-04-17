#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0
//New Insert RotEsq RotDir FlipColors isRed Imprime Busca 
typedef struct STnode* link;

typedef struct STnode{
    int chave;
    int item;
    link r;
    link l;
    int cor;
    int n;
}Stnode;

link h,z;

link new(int chave){

    link x = malloc(sizeof(STnode));
    x->chave = chave;
    x->l = x->r = z;
    x->cor = RED
    x->n = 1;

    return x;
}

int busca(link h, int chave){

    if(h->chave == chave)
        return chave;
        
    if(h->chave > chave)
        busca(h->l,chave)
    
    if(h->chave < chave)
        busca(h->r,chave)

    return -1;
}

link rotacionaEsq(link h){
    link x = h->r;
    h->l = x->l;
    x->l = h;

    x->cor = h->cor;
    h->cor = RED;

    x->n = h->n;
    h->n = h->l->n + h->r->n + 1;
    
    return x;
}


link rotacionaDir(link h){
    link x = h->l;
    h->l = x->l;
    x->r = h;

    x->cor = h->cor;
    h->cor = RED;

    x->n = h->n;
    h->n = h->l->n + h->r->n;

    return x;
}

int isRed(link h){
    if(h == z)
        return;
    
    return h->cor == RED;
}

link flipColors(link h){

    h->l->cor = BLACK;
    h->r->cor = BLACK;
    h->cor = RED;

    return h;
}


link insert(link h, int chave){
    if(h == z)
        return new(chave);
    
    if(h->chave > chave)
        h->l = insert(h->l,chave);
    
    if(h->chave < chave)
        h->r = insert(h->r,chave);

    
    if(isRed(h->r) && !isRed(h->l))
        h = rotacionaEsq(h);
    if(isRed(h->l) && isRed(h->l->l))
        h = rotacionaDir(h);
    if(isRed(h->l) && isRed(h->r))
        h = flipColors(h);

    h->n = h->l->n + h->r->n + 1;

    return h;
}


void imprime(link h){
    if(h == z)
        return
    
    imprime(h->l);
    printf("%d", h->chave);
    imprime(h->r);
}

int main(){

    

    return 0;
}


