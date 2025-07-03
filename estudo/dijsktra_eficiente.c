#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAXV 1000
typedef struct Edge *link;

struct Edge{
    int v, c;
    link prox;
};

typedef struct Graph{
    int v, e;
    link *adj;
}*Graph;

Graph graphInit(int v){
    Graph g = malloc(sizeof(Graph));
    g->v = v;
    g->e = 0;
    g->adj = malloc(sizeof(struct Edge) * v);
    
    for(int i = 0; i < g->v; i++){
        g->adj[i] = -1;
    }
    
    return g;
}

link new(int v, int c, link prox){
    link n = malloc(sizeof(struct Edge));
    n->prox = prox;
    n->v = v;
    n->c = c;

    return n;
}

void insertEdge(Graph g, int u, int v, int c){
    //u = valor da lista de adjacencia
    //v = item que será adicionado a lista de adj de u.
    //c custo da aresta.
    g->adj[u] = new(v,c,g->adj[u]);
}

// --- Fila de prioridade baseada em min-heap ---

int *pq;
int *qp;
int *dist;
int N;

// less exchange fixUp fixDown PQinit PQinsert PQdelmin PQempty PQcontains PQdecreasekey

#define less(a,b) (dist[a] < dist[b])

void exchange(int i, int j){
    int t = pq[i];

    pq[i] = pq[j];
    pq[j] = pq[i];

    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixUp(int k){
    while(k > 1 && less(pq[k], pq[k/2])){
        exchange(k,k/2);
        k = k/2;
    }
}

void fixDown(int k){
    int j;
    while(2*k <= N){
        j = 2*k;

        if(j <= N && less(pq[j+1], pq[j])){
            j++;
        }

        if(!less(pq[j], pq[k])){
            break;
        }

        exchange(k,j);
        k = j;
    }
}

void PQinit(int n, int *distRef){
    pq = malloc(sizeof(int) * n);
    qp = malloc(sizeof(int) * n);

    for(int i = 0; i <= n; i++){
        qp[i] = -1;
    }

    dist = distRef;
}

bool PQEmpty(){
    return N == 0;
}

bool PQcontains(int v){
    return qp[v] != -1;
}

void PQInsert(int v){
    if(PQcontains(v))
        return;
    
    pq[++N] = v;
    qp[v] = N;
    fixUp(N);
}

int PQdelmin(){
    int min = pq[1];
    exchange(1, N--);
    fixDown(1);
    qp[min] = -1;
    return min;
}

void PQdecreasekey(int v){
    fixUp(qp[v]);
}

// --- Implementação do Djkstra ---