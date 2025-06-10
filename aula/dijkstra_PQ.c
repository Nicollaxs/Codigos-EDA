#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define less(a, b) (dist[a] < dist[b])  // Agora usamos a distância como critério

typedef int Item;

static Item *pq;  // Índices dos vértices
static int *qp;   // Mapeamento: vértice -> posição na heap
static int N;     // Tamanho da heap
static int *dist; // Distância global para uso nas comparações

void exchange(int i, int j) {
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;

    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixup(int k) {
    while (k > 1 && less(pq[k], pq[k / 2])) {
        exchange(k, k / 2);
        k = k / 2;
    }
}

void fixDown(int k) {
    int j;
    while (2 * k <= N) {
        j = 2 * k;
        if (j < N && less(pq[j + 1], pq[j])) j++;
        if (!less(pq[j], pq[k])) break;
        exchange(k, j);
        k = j;
    }
}

void PQInit(int maxN, int *distRef) {
    pq = malloc(sizeof(Item) * (maxN + 1));
    qp = malloc(sizeof(int) * (maxN + 1));
    for (int i = 0; i <= maxN; i++) qp[i] = -1;
    N = 0;
    dist = distRef; // ponteiro para distâncias globais
}

bool PQEmpty() {
    return N == 0;
}

bool PQContains(int v) {
    return qp[v] != -1;
}

void PQInsert(int v) {
    pq[++N] = v;
    qp[v] = N;
    fixup(N);
}

int PQDelMin() {
    int min = pq[1];
    exchange(1, N--);
    fixDown(1);
    qp[min] = -1;
    return min;
}

void PQDecreaseKey(int v) {
    fixup(qp[v]);  // dist[v] foi reduzido, suba na heap
}

void graphcptD1(Grafo g, int s, int *pa, int *dist) {
    bool mature[1000];

    for (int v = 0; v < g->v; v++) {
        pa[v] = -1;
        mature[v] = false;
        dist[v] = INT_MAX;
    }

    dist[s] = 0;
    pa[s] = s;

    PQInit(g->v, dist);
    PQInsert(s);

    while (!PQEmpty()) {
        int y = PQDelMin();
        mature[y] = true;

        for (link a = g->adj[y]; a != NULL; a = a->next) {
            int v = a->v;
            if (mature[v]) continue;

            if (dist[y] + a->c < dist[v]) {
                dist[v] = dist[y] + a->c;
                pa[v] = y;

                if (PQContains(v)) {
                    PQDecreaseKey(v);
                } else {
                    PQInsert(v);
                }
            }
        }
    }
}

