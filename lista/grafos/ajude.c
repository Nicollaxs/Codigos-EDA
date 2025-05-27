#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
    int v, e;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

int *pre;
int contador;
int menorIndiceComponente;

int **matrizInit(int v, int w, int valor)
{
    int **m = malloc(sizeof(int *) * v);
    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);
        for (int j = 0; j < w; j++)
            m[i][j] = valor;
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
    int v = e.v, w = e.w;
    if (g->adj[v][w] == 0)
    {
        g->adj[v][w] = 1;
        g->adj[w][v] = 1;
        g->e++;
    }
}

void dfs(Graph g, int v)
{
    pre[v] = 1;
    contador++;

    if (v < menorIndiceComponente)
        menorIndiceComponente = v;

    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[v][i] && !pre[i])
        {
            dfs(g, i);
        }
    }
}

void componentesConexos(Graph g, int start)
{
    pre = calloc(g->v, sizeof(int));

    int maiorTamanho = 0;
    int melhorIndice = -1;

    // Processa o componente de João primeiro
    contador = 0;
    menorIndiceComponente = start;
    dfs(g, start);
    maiorTamanho = contador;
    melhorIndice = menorIndiceComponente;

    // Verifica se João está isolado
    int temAresta = 0;
    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[start][i])
        {
            temAresta = 1;
            break;
        }
    }

    // Processa os outros componentes
    for (int i = 0; i < g->v; i++)
    {
        if (!pre[i])
        {
            contador = 0;
            menorIndiceComponente = i;
            dfs(g, i);

            if (contador > maiorTamanho)
            {
                maiorTamanho = contador;
                melhorIndice = menorIndiceComponente;
            }
            else if (contador == maiorTamanho)
            {
                // desempate: menor índice diferente de João
                if (melhorIndice == start || menorIndiceComponente < melhorIndice)
                {
                    melhorIndice = menorIndiceComponente;
                }
            }
        }
    }

    if (melhorIndice == start)
    {
        if (!temAresta)
            printf("Fique em casa\n");
        else
            printf("Bora para estrada\n");
    }
    else
    {
        printf("Vamos para %d\n", melhorIndice);
    }

    free(pre);
}

int main()
{
    int n, joao;
    scanf("%d %d", &n, &joao);

    Graph g = graphInit(n);

    int v, w;
    while (scanf("%d %d", &v, &w) != EOF)
    {
        insertEdge(g, edge(v, w));
    }

    componentesConexos(g, joao);

    return 0;
}
