#include <stdio.h>
#include <stdlib.h>

typedef struct STnode* link;
#define NULLITEM -1

struct STnode{
    link l;
    link r;
    int item;
    int n;
};

link h,z;

link new(link l, link r, int item, int n){
    link x = malloc(sizeof(*x));;
    x->l = NULL;
    x->r = NULL;
    x->item = item;
    x->n = n;

    return x;
}

void STinit(){ 
    z = new(NULL,NULL,NULLITEM,0); //não entendi esse item NULL
    h = z;
}

int stcount(){
    return h->n;
}

void sortR(link n){
    if(n == NULL)
        return ;   
    sortR(n->l);
    printf("%d ", n->item); 
    sortR(n->r);
}

link insertT(link h, int item){
    if(h == z)
        return new(z,z,item,1);
    
    if(item < h->item)
       h->l = insertT(h->l, item);
        //rotação
    else    
       h->r = insertT(h->r,item);
        //rotação
    h->n = h->l->n + h->r->n + 1; //não entendi

    return h;
}

int search(link h, int item){
    if(h->item == item)
        return item;

    if(item < h->item)
        return search(h->l, item);
    else    
        return search(h->r, item); 
}








int main(){

    return 0;
}