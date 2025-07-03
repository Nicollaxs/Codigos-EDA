#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 1000

typedef struct Edge *link;
struct Edge
{
    int w;
    int c;
    link next;
};

typedef struct grafo
{
    int v;
    link *adj;
} *Grafo;

Grafo initGrafo(int V)
{
    Grafo g = malloc(sizeof(*g));
    g->v = V;
    g->adj = malloc(V * sizeof(link));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

link new(int v, int c, link next)
{
    link a = malloc(sizeof(*a));
    a->c = c;
    a->w = v;
    a->next = next;
    return a;
}

void insereAresta(Grafo g, int u, int v, int c) {
    g->adj[u] = new(v, c, g->adj[u]);
    g->adj[v] = new(u, c, g->adj[v]); 
}


static int *pq;   // Índices dos vértices
static int *qp;   // Posição na heap de cada vértice (-1 se não está)
static int N;     // Tamanho da heap
static int *dist; // Ponteiro para vetor de distâncias (global para heap)

#define less(a, b) (dist[a] < dist[b])

void exchange(int i, int j)
{
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixup(int k)
{
    while (k > 1 && less(pq[k], pq[k / 2]))
    {
        exchange(k, k / 2);
        k = k / 2;
    }
}

void fixDown(int k)
{
    int j;
    while (2 * k <= N)
    {
        j = 2 * k;
        if (j < N && less(pq[j + 1], pq[j]))
            j++;
        if (!less(pq[j], pq[k]))
            break;
        exchange(k, j);
        k = j;
    }
}

void PQInit(int maxN, int *distRef)
{
    pq = malloc(sizeof(int) * (maxN + 1));
    qp = malloc(sizeof(int) * (maxN + 1));
    for (int i = 0; i <= maxN; i++)
        qp[i] = -1;
    N = 0;
    dist = distRef;
}

bool PQEmpty()
{
    return N == 0;
}

bool PQContains(int v)
{
    return qp[v] != -1;
}

void PQInsert(int v)
{
    if (PQContains(v))
        return;
    pq[++N] = v;
    qp[v] = N;
    fixup(N);
}

int PQDelMin()
{
    int min = pq[1];
    exchange(1, N--);
    fixDown(1);
    qp[min] = -1;
    return min;
}

void PQDecreaseKey(int v)
{
    fixup(qp[v]);
}

int dijkstra(Grafo g, int s, int f, int *pa, int *dist)
{
    bool mature[1000];

    for (int i = 0; i < g->v; i++)
    {
        pa[i] = -1;
        dist[i] = INT_MAX;
        mature[i] = false;
    }

    pa[s] = s;
    dist[s] = 0;

    PQInit(g->v, dist);
    PQInsert(s);

    while (!PQEmpty())
    {
        int y = PQDelMin();
        mature[y] = true;

        for (link a = g->adj[y]; a != NULL; a = a->next)
        {
            if (mature[a->w])
                continue;

            if (dist[y] + a->c < dist[a->w])
            {
                dist[a->w] = dist[y] + a->c;
                pa[a->w] = y;

                if (PQContains(a->w))
                    PQDecreaseKey(a->w);
                else
                    PQInsert(a->w);
            }
        }
    }

    return dist[f];
}

int main(){

    int N, M;
    scanf("%d %d", &N, &M);

    Grafo g = initGrafo(N);

    int *pa = malloc(sizeof(int) * N);
    int *dist = malloc(sizeof(int) * N);

    for(int i = 1; i <= M; i++){
        int A,B,C;

        scanf("%d %d %d", &A, &B, &C);
        insereAresta(g, A - 1, B - 1, C);
    }

    printf("%d\n", dijkstra(g, 0, N - 1, pa, dist)); 
}