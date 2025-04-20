#include <stdio.h>
#include <stdlib.h>

#define hash(v,M) (16161 * (unsigned)v % M)

typedef struct Item {
    int chave;
    int frequencia;
} Item;

Item NULLItem = {0};

#define key(A) ((A.chave))
#define freq(A) ((A.frequencia))
#define null(A) (key(A) == key(NULLItem))

static int N, M;
static Item* ht;

void HTinit(int max) {
    N = 0;
    M = 2 * max;
    ht = malloc(sizeof(Item) * M);
    for (int i = 0; i < M; i++) ht[i] = NULLItem;
}

void HTinsert(int v) {
    int i = hash(v, M);
    while (!null(ht[i]) && key(ht[i]) != v) {
        i = (i + 1) % M;
    }
    if (null(ht[i])) {
        ht[i].chave = v;
        ht[i].frequencia = 1;
        N++;
    } else {
        ht[i].frequencia++;
    }
}

int main() {
    int entradas;
    int* resultados = NULL;
    int resIndex = 0, resCap = 0;

    while (scanf("%d", &entradas) && entradas != 0) {
        HTinit(entradas);

        int chave, maxFreq = 0, corMaisFreq = 0;
        for (int i = 0; i < entradas; i++) {
            scanf("%d", &chave);
            HTinsert(chave);
        }

        for (int i = 0; i < M; i++) {
            if (!null(ht[i]) && ht[i].frequencia > maxFreq) {
                maxFreq = freq(ht[i]);
                corMaisFreq = key(ht[i]);
            }
        }

        if (resIndex == resCap) {
            resCap = resCap == 0 ? 10 : resCap * 2;
            resultados = realloc(resultados, resCap * sizeof(int));
        }
        resultados[resIndex++] = corMaisFreq;

        free(ht);
    }

    for (int i = 0; i < resIndex; i++) {
        printf("%d\n", resultados[i]);
    }

    free(resultados);
    return 0;
}
