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

char animais[5005][30];

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
}

int dfs(Graph g, int u, int *visited)
{
    if (visited[u] != -1)
    {
        return visited[u];
    }

    int maxLength = 1;
    for (link l = g->adj[u]; l != NULL; l = l->prox)
    {
        int len = 1 + dfs(g, l->v, visited);

        if (len > maxLength)
            maxLength = len;
    }

    visited[u] = maxLength;
    return maxLength;
}

int buscaIndice(char nome[], int quantidadeAnimais)
{

    for (int i = 0; i < quantidadeAnimais; i++)
    {
        if (strcmp(animais[i], nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    int quantidadeAnimais, quantidadeRelacoes;

    scanf("%d %d", &quantidadeAnimais, &quantidadeRelacoes);
    Graph g = graphInit(quantidadeAnimais);

    for (int i = 0; i < quantidadeAnimais; i++)
    {
        scanf("%s", animais[i]);
    }

    for (int i = 0; i < quantidadeRelacoes; i++)
    {
        char presa[30];
        char predador[30];
        scanf("%s %s", presa, predador);

        insertEdge(g, edge(buscaIndice(presa, quantidadeAnimais), buscaIndice(predador, quantidadeAnimais)));
    }

    int visited[quantidadeAnimais];

    for (int i = 0; i < quantidadeAnimais; i++)
    {
        visited[i] = -1;
    }

    int max = 0;

    for (int i = 0; i < quantidadeAnimais; i++)
    {
        int len = dfs(g, i, visited);

        if (len > max)
            max = len;
    }

    printf("%d\n", max);

    return 0;
}
