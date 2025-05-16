#include <stdio.h>
#include <stdlib.h>

// MatrizInit GraphInit InsertEdge RemoveEdge Edge Bsf

typedef struct Graph
{
    int v, e;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

typedef struct Fila
{
    int v;
    struct Fila *prox;
} Fila;

Fila *comeco;
Fila *ultimo;
int *visitados;
int contador;

void enqueue(int v)
{
    Fila *novo = malloc(sizeof(struct Fila));
    novo->v = v;

    if (!comeco)
    {
        comeco = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->prox = novo;
        ultimo = novo;
    }
}

int dequeue()
{
    if (!comeco)
    {
        return -1;
    }

    Fila *aux = comeco;
    int v = aux->v;
    free(aux);
    return v;
}

int **matrizInit(int v, int w, int c)
{
    int **m = malloc(sizeof(int *) * v);

    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);

        for (int j = 0; j < w; j++)
        {
            m[i][j] = 0;
        }
    }

    return m;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->v = v;
    g->e = 0;
    g->adj = matrizInit(v, v, 0);

    return g;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

void insertEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;

    g->e++;
}

void removeEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;

    g->e--;
}

void bsf(Graph g, int start)
{
    enqueue(start);
    visitados[start] = contador++;

    while (comeco)
    {

        int a = dequeue();

        for (int i = 0; i < g->v; i++)
        {
            if (g->adj[a][i] == 1 && visitados[i] != -1)
            {
                enqueue(i);
                visitados[i] = contador++;
            }
        }
    }
}
