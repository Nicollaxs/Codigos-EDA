#include <stdio.h>
#include <stdlib.h>

// HTinsert , hash , HTinit , HTcount, HTSearch

#define hash(v,M) (16161 * (unsigned)v % M) //v = chave M = max

typedef struct Item{
    int chave;
    int frequencia;
}Item;

Item NULLItem = {0};

#define  key(A) ((A.chave))
#define  freq(A) ((A.frequencia))
#define less(A,B) ((A.chave < B.chave))
#define null(A) (key(A) == key(NULLItem))
#define eq(A,B) ((A) == (B))

static int N,M;
static Item* ht;

void HTinit(int max){
    int i;
    N = 0;
    M = 2 * max;
    ht = malloc(sizeof(Item)*M);

    for( i = 0; i < M; i++){
        ht[i] = NULLItem;
    }
}

void HTinsert(int v){

    int i = hash(v, M);

    while(!null(ht[i]) && key(ht[i]) != v){
        i = (i + 1) % M; 
    }

    if(null(ht[i])){
        ht[i].chave = v;
        ht[i].frequencia = 1;
        N++;
    } else {
        ht[i].frequencia ++;
    }
}


int main(){

    int entradas;
    int vet[10];
    int resIndex = 0;

    for (int i = 0; i < 10; i++) vet[i] = 0;

    while (scanf("%d", &entradas) && entradas != 0){
        HTinit(entradas);

        int chave, maxFreq = 0, corMaisFreq = 0;

        for(int i = 0; i < entradas; i++){
            scanf("%d", &chave);
            HTinsert(chave);    
        }


        for(int i = 0; i<M; i++){

            if(!null(ht[i]) && ht[i].frequencia > maxFreq){
                maxFreq = freq(ht[i]);
                corMaisFreq = key(ht[i]);
            }
        }

        if (resIndex < 10) {
            vet[resIndex++] = corMaisFreq;
        }

    }

    for(int i = 0; i < 10; i++){
        if(vet[i] != 0)
          printf("%d\n", vet[i]);
    }

    return 0;
}  