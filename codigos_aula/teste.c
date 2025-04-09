#include <stdio.h>
#include <stdlib.h>

typedef struct STnode* link;
#define nullItem -1

struct STnode{
    link l;
    link r;
    int item;
    int n;
};

link h,z;

link new(link l, link r, int valor, int n){
    link x = malloc(sizeof(*link));
    x->l = l;
    x->r = r;
    x->item = valor;
    x->n = n; 
    return n;
}

void STinit(){
    h = new(z,z,nullItem,0);
    z = h;
}

link insert(link h, int valor){
    if(h == z)
        return new(z,z,valor,1); 
    
    if(h->item < valor)
        h->r = insert(h->r,valor);
    else
        h->l = insert(h->l,valor);

    h->n = h->l->n + h->r->n + 1;
    return h;
}




int main(){

    return 0;
}