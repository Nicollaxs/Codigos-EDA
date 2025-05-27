#include <stdio.h>
#include <stdlib.h>

// Insert Remove MatrizInit GraphInit Edge

typedef struct Graph
{
    int v;
    int e;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

typedef struct node *link;

struct node
{
    int v;
    link *prox;
};

link topo = NULL;

void push(int v)
{
    link new = malloc(sizeof(struct node));
    new->v = v;
    new->prox = topo;
    topo = new;
}

int pop()
{
    if (!topo)
        return -1;

    link aux = topo;
    int v = topo->v;
    topo = topo->prox;
    free(aux);
    return v;
}

int **matrizInit(int v, int w, int x)
{
    int **mat = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        mat[i] = malloc(sizeof(int));
        for (int j = 0; j < w; j++)
        {
            mat[i][j] = x;
        }
    }

    return mat;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

Graph graphInit(int v)
{

    Graph g = malloc(sizeof(*g));
    g->v = v;
    g->adj = matrizInit(v, v, 0);
    g->e = 0;

    return g;
}

void insertEdge(Graph g, Edge e)
{

    g->adj[e.v][e.w] = 1;
    g->adj[e.w][e.v] = 1;
    g->e++;
}

void removeEdge(Graph g, Edge e)
{

    g->adj[e.v][e.w] = 0;
    g->adj[e.w][e.v] = 0;
    g->e--;
}

int *pre;
int count = 0;

void dfs(Graph g, int w)
{

    pre[w] = count++;

    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[w][i] == 1)
            if (pre[i] == -1)
                dfs(g, i);
    }
}

void dfsIterativa(Graph g, Edge e)
{

    push(e.w);

    while (topo != NULL)
    {
        int w = pop();

        pre[w] = count++;

        for (int i = 0; i < g->v; i++)
        {
            if (g->adj[w][i] == 1)
            {
                if (pre[i] == -1)
                    push(i);
            }
        }
    }
}

int compoentesDesconexas(Graph g){
    int contador = 0;

    for(int i = 0; i < g->v; i++){
        if(pre[i] == -1){
            dfs(g,i);
            contador ++;
        }
    }

    return contador;
}
