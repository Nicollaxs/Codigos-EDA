#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *link;

struct node
{
    int v;
    link prox;
};

typedef struct Graph
{
    int v;
    int e;
    link *adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

int *pre;
int contador = 0;
int *territorios;

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->v = v;
    g->e = 0;
    g->adj = malloc(sizeof(link) * (v+1));
    pre = malloc(sizeof(int) * (v+1));
    territorios = malloc(sizeof(int) *(v + 1));

    for (int i = 1; i <= g->v; i++)
    {
        g->adj[i] = NULL;
        pre[i] = -1;
        territorios[i] = -1;
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
    return e;
}

void insertEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);
    g->e++;
}

int dfs(Graph g, Edge e)
{
    int w = e.w;
    pre[w] = contador++;

    int preco = w;
    for(link l = g->adj[w]; l!= NULL; l = l->prox)
    {
        if (pre[l->v] == -1)
        {
            preco |= dfs(g, edge(l->v, l->v));
        }
    }

    return preco;
}

int precoSeguranca(Graph g)
{
    int preco = 0;
    contador = 0;


    for (int i = 1; i <= g->v; i++)
    {
        if (pre[i] == -1)
        {
            int p = dfs(g, edge(i, i));
            territorios[i] = p;
        }
    }

    for (int i = 1; i <= g->v; i++)
    {
        if (territorios[i] != -1)
        {
            preco ^= territorios[i];
        }

    }

    return preco;
}

int main()
{

    int quantidadeVertices;
    int relacoes;

    scanf("%d %d", &quantidadeVertices, &relacoes);

    Graph g = graphInit(quantidadeVertices);

    for (int i = 0; i < relacoes; i++)
    {
        int v, w;
        scanf("%d %d", &v, &w);
        insertEdge(g, edge(v, w));
    }

    printf("%d\n", precoSeguranca(g));

    return 0;
}