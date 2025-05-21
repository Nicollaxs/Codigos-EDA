#include <stdio.h>
#include <stdlib.h>

// MatrizInit Insert Remove Edge

typedef struct Grafo
{
    int V;
    int e;
    int **adj;
    int **tc;
} *Grafo;

typedef struct Edge
{
    int v;
    int w;
} Edge;

typedef struct Pilha
{
    int v;
    struct Pilha *prox;
} Pilha;

Pilha *topo;
int *pre;
int count = 0;

void push(int v)
{

    Pilha *novo = malloc(sizeof(struct Pilha));
    novo->v = v;
    novo->prox = topo;
    topo = novo;
}

int pop()
{
    if (!topo)
    {
        printf("Pilha vazia ! \n");
        return -1;
    }

    Pilha *aux = topo;
    topo = topo->prox;
    int v = aux->v;

    free(aux);
    return v;
}

Grafo graphInit(int V)
{

    Grafo g = malloc(sizeof(*g));
    g->V = V;
    g->e = 0;
    g->adj = matrizInit(V, V, 0);

    pre = malloc(sizeof(int) * V);

    for (int i = 0; i < V; i++)
    {
        pre[i] = -1;
    }

    return g;
}

int **matrizInit(int v, int w, int c)
{
    int **m = malloc(sizeof(int *) * v);

    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);
        for (int j = 0; j < w; j++)
        {
            m[i][j] = c;
        }
    }

    return m;
}

Edge edge(int v, int w)
{
    Edge e;
    e.v = v;
    e.w = w;

    return e;
}

void insertEdge(Grafo g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
    g->e++;
}

void removeEdge(Grafo g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;
    g->e--;
}

void dfs(Grafo g, Edge e)
{

    int w = e.w;
    pre[w] = count++;

    for (int i = 0; i < g->V; i++)
    {
        if (g->adj[w][i] == 1 && pre[i] == -1)
        {
            printf("( %d , %d )\n", e.w, i);
            dfs(g, edge(w, i));
        }
    }
}

void dfsInterativa(Grafo g, int start)
{
    push(start);

    while (topo != NULL)
    {

        int a = pop();
        pre[a] = count++;

        for (int i = 0; i < g->V; i++)
        {
            if (g->adj[a][i] == 1 && pre[i] == -1)
            {
                push(i);
            }
        }
    }
}

void GRAPHtc(Grafo g)
{
    int i, s, t;

    g->tc = matrizInit(g->V, g->V, 0);

    for (s = 0; s < g->V; s++)
        for (t = 0; t < g->V; t++)
            g->tc[s][t] = g->adj[s][t];

    for (s = 0; s < g->V; s++)
        g->tc[s][s] = 1;

    for (i = 0; i < g->V; i++)     // COLUNAS
        for (s = 0; s < g->V; s++) // LINHAS
            if (g->tc[s][i] == 1)
                for (t = 0; t < g->V; t++)
                    if (g->tc[i][t] == 1)
                        g->tc[s][t] = 1;
}

void teste(){
    printf("Teste");
}