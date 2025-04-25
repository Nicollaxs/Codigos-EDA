#include <stdio.h>
#include <stdlib.h>

//macros

#define hash(v,M) (v%M)
#define eq(A,B) ((A) == (B))
#define null(A) (key(A) == Key(NullItem))
#define key(A) ((int)A.letra)


typedef struct Item{
    char letra;
}Item;

Item *ht;
Item NullItem = {-1};
int M;

void HTinit(int max){
    M = max;
    ht = malloc(sizeof(Item)*M);

    for(int i = 0; i < M; i ++){
        ht[i] = NullItem;
    }
}

void HTinsert(Item item){
    int chave = (int) item.letra;
    int i =  hash(chave,M);

    while(!null(ht[i])){
        i = (i + 1) % M;
    }

    ht[i] =item;
}

Item HTsearch(char letra){
    int chave = (int)letra;
    int i = hash(chave,M);

    while(!null(ht[i])){

        if(eq(key(ht[i]),chave)){
            return ht[i];
        } 

        i = (i + 1) % M;
    }

    return NullItem;;
}