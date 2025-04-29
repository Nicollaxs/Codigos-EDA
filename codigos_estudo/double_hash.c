#include <stdio.h>
#include <stdlib.h>


#define hash(v,M) ((v%M));
#define hashtwo(v,M) ((v % 97) + 1)
#define key(A) ((A.chave))
#define eq(A,B) (A == B)
#define null(A) (key(A)== key(NULLITEM))
#define MAXCOL 10


typedef struct Item{
    int chave;
}Item;

Item *ht;
Item NULLITEM = {-1};
int M;
int N = 0;

//HTinsert HTinit HTsearch HTgrow 

void HTinit(int max){
    M = max;

    ht = malloc(sizeof(Item) * M);

    for(int i = 0; i < M; i++){
        ht[i] = NULLITEM;
    }
}

int HTinsert(Item item){
    int chave = key(item);
    int i = hash(chave,M);
    int h = hashtwo(chave,M);

    int c = MAXCOL;
    while(c && !null(ht[i])){
        i = (i + h)%M;
        c--;
    }

    if(!c){
        HTgrow();
        return HTinsert(item);
    }

    ht[i] = item;
    N++;

    if(N > (M/2)){
        HTgrow();
    }

    return 1;
}


void HTgrow(){
    int oldM = M;
    M = 2 * M;

    Item *novo = ht;
    HTinit(M);

    for(int i = 0; i < oldM; i++){
        if(!null(novo[i])){
            HTinsert(novo[i]);
        }
    }

    free(novo);
}

Item HTSearch(int chave){
    int i = hash(chave,M);
    int h = hashtwo(chave,M);

    int c = MAXCOL;

    while(c && !eq(chave,key(ht[i]))){
        i = (i + h) % M;
        c--;
    }

    if(!c){
        return NULLITEM;
    }

    return ht[i];
}

int grau(Item *ht, int chave){
    int i = hash(chave,M);
    int h = hashtwo(chave,M);

    int qtd = 0;
    int c = MAXCOL;

    if(!eq(key(ht[i]),chave)){
        qtd++;
        c --;
        i = (i + h) % M;
    } else {
        return 0;
    }

    while(c && !eq(key(ht[i]),chave)){
        i = (i + h) % M;
        qtd++;
    }

    if(!c){
        return MAXCOL;
    }

    return qtd;
}


int main(){

    return 0;
}