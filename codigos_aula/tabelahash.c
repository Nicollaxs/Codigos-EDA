#include <stdio.h>
#include <stdlib.h>

#define hash(v, m) ((16161 * (unsigned)v) % m)

typedef struct Item {
    int chave;
    long e1, e2;
    long elemento;
} Item;

Item NULLitem = {0, 0, 0, 0};

#define key(x) (x.chave)
#define less(a,b) (key(a) < key(b))
#define null(A) (key(ht[A]) == key(NULLitem))
#define eq(a, b) ((a) == (b)) // simples comparação de inteiros

static int N, M;
static Item *ht;

void HTinit(int max) {
    int i;
    N = 0;
    M = 2 * max;
    ht = malloc(sizeof(Item) * M);
    for (i = 0; i < M; i++)
        ht[i] = NULLitem;
}

int HTcount() {
    return N;
}

void HTinsert(Item item) { 
    int v = key(item);
    int i = hash(v, M);

    while (!null(i)) {
        i = (i + 1) % M;
    }

    ht[i] = item;
    N++;
}

Item HTsearch(int v) {
    int i = hash(v, M);
    while (!null(i)) {
        if (eq(v, key(ht[i])))
            return ht[i];
        else
            i = (i + 1) % M;
    }

    return NULLitem;
}

int main(){

    HTinit(10);

    Item novo = {42, 1, 2, 1000};
    HTinsert(novo);

    Item resultado = HTsearch(42);
    printf("Elemento encontrado: %ld\n", resultado.elemento);


    return 0;
}
