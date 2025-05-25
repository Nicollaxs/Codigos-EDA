#include <stdio.h>
#include <stdlib.h>

typedef struct Node *link;

struct Node
{
    int v;
    link prox;
};

typedef struct Edge
{
    int v, w;
} Edge;

typedef struct Graph
{
    int v;
    int e;
    link *adj;
} *Graph;

int *pre;
int contador = 0;

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->e = 0;
    g->v = v;

    g->adj = malloc(sizeof(link) * v);

    for (int i = 0; i < v; i++)
    {
        g->adj[i] = NULL;
    }

    pre = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        pre[i] = -1;
    }

    return g;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

link new(int v, link prox)
{
    link n = malloc(sizeof(struct Node));
    n->v = v;
    n->prox = prox;
    return n;
}

void insertEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);
    g->e++;
}

void dfs(Graph g, Edge e)
{
    int w = e.w;
    pre[w] = contador++;

    for (link l = g->adj[w]; l != NULL; l = l->prox)
    {
        if (pre[l->v] == -1)
            dfs(g, edge(l->v, l->v));
    }
}

int nucleosDesconexos(Graph g)
{

    int quantidade = 0;

    for (int i = 0; i < g->v; i++)
    {
        if (pre[i] == -1)
        {
            dfs(g, edge(i, i));
            quantidade++;
        }
    }

    return quantidade;
}

int main()
{
    int qtdVertices;
    scanf("%d", &qtdVertices);

    Graph g = graphInit(qtdVertices);

    int v, w;
    while (scanf("%d %d", &v, &w) != EOF)
    {
        insertEdge(g, edge(v, w));
    }

    printf("%d\n", nucleosDesconexos(g));

    return 0;
}