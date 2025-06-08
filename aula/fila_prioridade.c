#include <stdio.h>
#include <stdlib.h>

#define less(a, b) ((a) < (b))
typedef int Item;

static Item *pq;  // Heap
static int *qp;   // Mapeamento do item -> posição -- Exemplo qp[1] retorna a posição do elemento 1 na heap.
static int N;     // Tamanho do heap

void showPQ() {
    printf("Heap (pq): ");
    for (int i = 1; i <= N; i++) {
        printf("%d ", pq[i]);
    }
    printf("\n");
}

void PQInit(int maxN) {
    pq = malloc(sizeof(Item) * (maxN + 1));
    qp = malloc(sizeof(int) * (maxN + 1));
    for (int i = 0; i <= maxN; i++) qp[i] = -1;
    N = 0;
}

void exchange(int i, int j) {
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixup(int k) {
    while (k > 1 && less(pq[k / 2], pq[k])) {
        exchange(k, k / 2);
        k = k / 2;
    }
}

void fixDown(int k) {
    int j;
    while (2 * k <= N) {
        j = 2 * k;
        if (j < N && less(pq[j], pq[j + 1])) j++;
        if (!less(pq[k], pq[j])) break;
        exchange(k, j);
        k = j;
    }
}

void PQinsert(int k) {
    pq[++N] = k;
    qp[k] = N;
    fixup(N);
    printf("Inserido %d:\n", k);
    showPQ();
}

Item PQdelMax() {
    Item max = pq[1];
    exchange(1, N--);
    fixDown(1);
    qp[max] = -1;
    printf("Removido maior (%d):\n", max);
    showPQ();
    return max;
}

int main() {
    PQInit(10);  // capacidade máxima 10

    PQinsert(40);
    PQinsert(10);
    PQinsert(30);
    PQinsert(50);

    PQdelMax(); // remove o maior (50)

    free(pq);
    free(qp);
    return 0;
}
