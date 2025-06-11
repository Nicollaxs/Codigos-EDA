#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 1000

typedef struct Edge* link;
struct Edge {
    int v;
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

link new(int v, int c, link next){
    link a = malloc(sizeof(*a));
    a->c = c;
    a->v = v;
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

void PQInit(int maxN, int *distRef) {
    pq = malloc(sizeof(int) * (maxN+1));
    qp = malloc(sizeof(int) * (maxN+1));
    for (int i=0; i<=maxN; i++) qp[i] = -1;
    N = 0;
    dist = distRef;
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

// --- Dijkstra usando a fila de prioridade ---
void graphcptD1(Grafo g, int s, int *pa, int *dist) {
    bool mature[MAXV];
    for (int v=0; v < g->v; v++) {
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
                if (PQContains(v))
                    PQDecreaseKey(v);
                else
                    PQInsert(v);
            }
        }
    }
}

// --- Função para imprimir distâncias ---
void printDistances(int *dist, int V, int s) {
    printf("Distancias minimas a partir do vertice %d:\n", s);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("Vertice %d: nao alcancavel\n", i);
        else
            printf("Vertice %d: %d\n", i, dist[i]);
    }
}

int main() {
    int V = 5;
    Grafo g = initGrafo(V);

    // Inserindo algumas arestas (grafo direcionado)
    insereAresta(g, 0, 1, 10);
    insereAresta(g, 0, 3, 5);
    insereAresta(g, 1, 2, 1);
    insereAresta(g, 1, 3, 2);
    insereAresta(g, 2, 4, 4);
    insereAresta(g, 3, 1, 3);
    insereAresta(g, 3, 2, 9);
    insereAresta(g, 3, 4, 2);
    insereAresta(g, 4, 0, 7);
    insereAresta(g, 4, 2, 6);

    int pa[MAXV];
    int dist[MAXV];

    int origem = 0;
    graphcptD1(g, origem, pa, dist);
    printDistances(dist, V, origem);

    // Liberar memória do grafo
    for (int i = 0; i < V; i++) {
        link a = g->adj[i];
        while (a != NULL) {
            link tmp = a;
            a = a->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);

    free(pq);
    free(qp);

    return 0;
}
