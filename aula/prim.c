#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 1000

typedef struct Edge* link;
struct Edge {
    int w;
    int c;
    link next;
};

typedef struct grafo {
    int v;
    link *adj;
} *Grafo;

// --- Funções para criar o grafo ---
Grafo initGrafo(int V) {
    Grafo g = malloc(sizeof(*g));
    g->v = V;
    g->adj = malloc(V * sizeof(link));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

link new(int w, int c, link next){
    link a = malloc(sizeof(*a));
    a->c = c;
    a->w = w;
    a->next = next;
    return a;
}

void insereAresta(Grafo g, int u, int v, int c) {
    g->adj[u] = new(v, c, g->adj[u]);
}

// --- Fila de prioridade baseada em min-heap ---

static int *pq;  // Índices dos vértices
static int *qp;  // Posição na heap de cada vértice (-1 se não está)
static int N;    // Tamanho da heap
static int *dist; // Ponteiro para vetor de distâncias (global para heap)

#define less(a,b) (dist[a] < dist[b])

void exchange(int i, int j) {
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixup(int k) {
    while (k > 1 && less(pq[k], pq[k/2])) {
        exchange(k, k/2);
        k = k/2;
    }
}

void fixDown(int k) {
    int j;
    while (2*k <= N) {
        j = 2*k;
        if (j < N && less(pq[j+1], pq[j])) j++;
        if (!less(pq[j], pq[k])) break;
        exchange(k, j);
        k = j;
    }
}

void PQInit(int maxN) {
    pq = malloc(sizeof(int) * (maxN+1));
    qp = malloc(sizeof(int) * (maxN+1));
    for (int i=0; i<=maxN; i++) qp[i] = -1;
    N = 0;
}

bool PQEmpty() {
    return N == 0;
}

bool PQContains(int v) {
    return qp[v] != -1;
}

void PQInsert(int v) {
    if (PQContains(v)) return;
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
    fixup(qp[v]);
}

// --- PRIM usando a fila de prioridade ---
void prim(Grafo g, int *pa) {
    bool tree[1000];
    int preco[1000];

    for(int i = 0; i < g->v; i++){
        pa[i] = -1;
        tree[i] = false;
        preco = INT_MAX;
    }

    pa[0] = 0;
    tree[0] = true;

    for(link a = g->adj[0]; a!=NULL; a++){
        pa[a->w] = 0;
        preco[a->w] = a->c;
    }

    PQInit(g->v);

    for(int i = 0; i<g->v; i++)
        PQInsert(i);

    while(!PQEmpty()){
        int y = PQDelMin();
        if(preco[y] == INT_MAX) break;

        tree[y] = true;

        for(link a = g->adj[a]; a!= NULL; a = a->next){
            if(!tree[a->w] && a->c < preco[a->w]){
                preco[a->w] = a->c;
                PQDecreaseKey(a->w);
                pa[a->w] = y;
            }
        }
    }
}

int main() {
}
