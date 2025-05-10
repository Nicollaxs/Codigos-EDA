#include <stdio.h>
#include <stdlib.h>

// rotesq, rotdir, flipcolor, insert, isred

#define RED 1 //não é nescessario o "="
#define BLACK 0 //Não tem ponto e virgula

typedef struct STnode* link;

typedef struct STnode{
    int chave;
    link l;
    link r;
    int cor;
    int n;
}STnode; //Esqueci de colocar "STnode"

link h,z;

link new(int chave){
    link x = malloc(sizeof(STnode));
    x->chave = chave;
    x->l = x->r = z; //Errei na sintaxe
    x->cor = RED; //Novos links sempre devem ter a cor RED.
    x->n = 1; //lembre-se  de atualizar o n

    return x;
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

link flipColors(link h){
    h->cor = RED;
    h->r->cor = BLACK;
    h->l->cor = BLACK;

    return h;
}

int isRed(link x){
    if(x == z)
      return 0;

    return x->cor == RED;
}

link insert(link h, int chave){
    if(h == z)
        return new(chave);
    
    if(h->chave > chave)
        h->l = insert(h->l,chave);
    if(h->chave < chave)
        h->r = insert(h->r, chave);
    
    if(isRed(h->r) && !isRed(h->l))
        h = rotacionaEsq(h);
    if(isRed(h->l) && isRed(h->l->l))
        h = rotacionaDir(h);
    if(isRed(h->l) && isRed(h->r))
        h = flipColors(h);

    h->n = h->l->n + h->r->n + 1; //Calcula quantos nós tem na arvore
    return h;
}

void printArvore(link h, int nivel) {
    if (h == z) return;

    for (int i = 0; i < nivel; i++)
        printf("  ");

    printf("%d (%s)\n", h->chave, h->cor == RED ? "R" : "B");

    printArvore(h->l, nivel + 1);
    printArvore(h->r, nivel + 1);
}

link STsearch(link ht, int chave){

    if(ht == z){
        return NULL;
    }

    if(ht->chave == chave){
        return ht;
    }

    if(ht->chave > chave)
        return STsearch(ht->l, chave);
    if(ht->chave < chave)
        return STsearch(ht->r, chave);

}


int main(){

    z = malloc(sizeof(STnode));
    z->l = z->r = z;
    z->cor = BLACK;
    z->n = 0;

    h = z;

    h = insert(h,10);
    h = insert(h,7);
    h = insert(h,15);
    h = insert(h,11);

    link busca = STsearch(h,7);

    if(busca != NULL){
        printf("Item achado : %d\n", busca->chave);
    } else {
        printf("Item não achado.\n");
    }

    printf("Árvore Red-Black:\n");
    printArvore(h, 0);

    return 0;
}



