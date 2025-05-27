#include <stdio.h>
#include <stdlib.h>

// Edge insert new remove enqueue dequeue

typedef struct node *link;

struct node
{
    int v;
    link *prox;
};

typedef struct Grafo
{
    int v;
    int e;
    link *adj;
} *Grafo;

typedef struct Edge
{
    int v, w;
} Edge;

link comeco = NULL;
link fim = NULL;
int *visitados;
int count = 0;

void enqueue(int v)
{
    link l = malloc(sizeof(struct node));
    l->v = v;
    l->prox = NULL;

    if (!comeco)
    {
        comeco = l;
        fim = l;
    }
    else
    {
        fim->prox = l;
        fim = l;
    }
}

int dequeue()
{
    if (!comeco)
    {
        return -1;
    }

    link aux = comeco;
    int v = comeco;
    comeco = comeco->prox;
    free(comeco);
    return v;
}

Grafo graphInit(int v)
{
    Grafo g = malloc(sizeof(struct Grafo));
    g->v = v;
    g->e = 0;
    g->adj = malloc(sizeof(link) * v);

    for (int i = 0; i < v; i++)
    {
        g->adj[i] = NULL;
    }

    return g;
}

link new(int v, link prox)
{
    link n = malloc(sizeof(struct node));
    n->prox = prox;
    n->v = v;

    return n;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
}

void insertEdge(Grafo g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);
    g->e++;
}

void removeEdge(Grafo g, int v, int w)
{
    removeEdgeAux(g, v, w);
    removeEdgeAux(g, w, v);
}

void removeEdgeAux(Grafo g, int v, int w)
{
    link atual = g->adj[v];
    link anterior = NULL;

    while (atual)
    {
        if (atual->v == w)
        {
            if (anterior == NULL)
            {
                atual = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        atual = atual->prox;
    }
}

void bfs(Grafo g, int start)
{

    enqueue(start);

    while (comeco != NULL)
    {
        int v = dequeue();

        if (visitados[v] == -1)
        {
            visitados[v] = count++;

            for (link l = g->adj[v]; l != NULL; l = l->prox)
            {
                if (visitados[l->v] == -1)
                {
                    enqueue(l->v);
                }
            }
        }
    }
}
