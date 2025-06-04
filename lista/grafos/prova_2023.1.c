#include <stdio.h>
#include <stdlib.h>

typedef struct No *link;

struct No
{
    int v;
    int numeroDaSemente;
    link prox;
};

typedef struct Graph
{
    int v, e;
    link *adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->v = v;
    g->e = 0;

    g->adj = malloc(sizeof(link) * v);
    for (int i = 0; i < g->v; i++)
    {
        g->adj[i] = NULL;
    }

    return g;
}

link new(int v, link prox)
{
    link n = malloc(sizeof(link));
    n->v = v;
    n->prox = prox;

    return n;
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

    g->adj[v] = new(w, g->adj[v]);
}

void primordiais(Graph g)
{
    int *in = malloc(sizeof(int) * g->v);

    for (int i = 0; i < g->v; i++)
    {
        in[i] = 0;
    }

    for (int i = 0; i < g->v; i++)
    {
        for (link l = g->adj[i]; l != NULL; l = l->prox)
        {
            in[l->v]++;
        }
    }

    printf("Sementes Primordiais : \n");
    for (int i = 0; i < g->v; i++)
    {
        if (in[i] == 0)
        {
            printf("%d", i);
        }
    }
}

void finais(Graph g)
{
    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[i] == NULL)
        {
            printf("%d", i);
        }
    }
}




