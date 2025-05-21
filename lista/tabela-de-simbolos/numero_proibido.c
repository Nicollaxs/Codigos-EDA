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
}STnode;

link h,z;

link new(int chave){

    link x = malloc(sizeof(STnode));
    x->chave = chave;
    x->l = x->r = z;
    x->cor = RED;
    x->n = 1;

    return x;
}

int busca(link h, int chave){

    if(h == z)
        return 0;

    if(h->chave == chave)
        return 1;
        
    if(h->chave > chave)
       return busca(h->l,chave);
    
    if(h->chave < chave)
        return busca(h->r,chave);

    return -1;
}

link rotacionaEsq(link h){
    link x = h->r;
    h->r = x->l;
    x->l = h;

    x->cor = h->cor;
    h->cor = RED;

    x->n = h->n;
    h->n = h->l->n + h->r->n + 1;
    
    return x;
}


link rotacionaDir(link h){
    link x = h->l;
    h->l = x->r;
    x->r = h;

    x->cor = h->cor;
    h->cor = RED;

    x->n = h->n;
    h->n = h->l->n + h->r->n + 1;

    return x;
}

int isRed(link h){
    if(h == z)
        return 0;
    
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
        return;
    
    imprime(h->l);
    printf("%d\n", h->chave);
    imprime(h->r);
}

void printArvore(link h, int nivel) {
    if (h == z) return;

    for (int i = 0; i < nivel; i++)
        printf("  ");

    printf("%d (%s)\n", h->chave, h->cor == RED ? "R" : "B");

    printArvore(h->l, nivel + 1);
    printArvore(h->r, nivel + 1);
}

int main(){

    z = malloc(sizeof(STnode));
    z->l = z->r = z;
    z->cor = BLACK;
    z->n = 0;

    h = z;

    int n;
    scanf("%d",&n);

    for(int i = 0; i < n; i++){
        int numero;
        scanf("%d", &numero);
        h = insert(h,numero);
    }

    int entrada;
    while(scanf("%d", &entrada) == 1){
        if(busca(h,entrada))
            printf("sim\n");
        else 
            printf("nao\n");
    }

    return 0;
}


