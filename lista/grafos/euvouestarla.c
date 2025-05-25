#include <stdio.h>
#include <stdlib.h>

// MatrizInit GraphInit Insert Edge

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

int **matrizInit(int v, int w, int c)
{
    int **m = malloc(sizeof(int*) * v);

    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);
        for (int j = 0; j < w; j++)
            m[i][j] = c;
    }

    return m;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->e = 0;
    g->v = v;
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

int main()
{

    int N, M, J;

    scanf("%d %d %d", &N, &M, &J);

    Graph g = graphInit(N);

    int pre[N];

    for (int i = 0; i < N; i++)
    {
        pre[i] = -1;
    }

    for (int i = 0; i < N; i++)
    {
        int qtdVizinhos;
        scanf("%d", &qtdVizinhos);

        for (int j = 0; j < qtdVizinhos; j++)
        {
            int vizinho;
            scanf("%d", &vizinho);
            Edge e = edge(i, vizinho);
            insertEdge(g,e);
        }
    }

    for (int i = 0; i < M; i++)
    {
        int visitado;
        scanf("%d", &visitado);
        pre[visitado] = 1;

        for (int j = 0; j < N; j++)
        {
            if (g->adj[visitado][j] == 1)
            {
                pre[j] = 1;
            }
        }
    }

    int valores[J];
    for (int i = 0; i < J; i++)
    {
        int v;
        scanf("%d", &v);
        valores[i] = v;
    }

    for (int i = 0; i < J; i++)
    {
        if (pre[valores[i]] == 1)
            printf("Eu vou estar la\n");
        else
            printf("Nao vou estar la\n");
    }

    return 0;
}
