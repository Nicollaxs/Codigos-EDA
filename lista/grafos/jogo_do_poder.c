#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
    int v, w;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

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
    Edge e = {v, w};
    return e;
}

Graph graphInit(int v, int w)
{
    Graph g = malloc(sizeof(struct Graph));
    g->adj = matrizInit(v, w, 0);
    g->w = w;
    g->v = v;

    return g;
}

int dfs(Graph g, int poder, int linha, int coluna)
{

    int maiorLinha = -1;
    int maiorColuna = -1;

    int poder = g->adj[linha][coluna];
    int maior = 0;

    if (coluna - 1 >= 0) // Verifica se eu posso fazer a verificação na esquerda
        if (g->adj[linha][coluna - 1] < poder)
        {
            if (g->adj[linha][coluna - 1] > maior)
            {
                maior = g->adj[linha][coluna - 1];
                maiorLinha = linha;
                maiorColuna = coluna - 1;
            }
        }

    if (coluna + 1 < g->w) // Verifica se eu posso fazer a verificação na direita
        if (g->adj[linha][coluna + 1] < poder)
        {
            if (g->adj[linha][coluna + 1] > maior)
            {
                maior = g->adj[linha][coluna + 1];
                maiorLinha = linha;
                maiorColuna = coluna + 1;
            }
        }

    if (linha - 1 >= 0) // Verifica se eu posso fazer a verificação na linha de cima
        if (g->adj[linha - 1][coluna] < poder)
        {
            if (g->adj[linha - 1][coluna] > maior)
            {

                maior = g->adj[linha - 1][coluna];
                maiorLinha = linha - 1;
                maiorColuna = coluna;
            }
        }

    if (linha + 1 < g->v) // Verifica se eu posso fazer a verificação na linha de baixo
        if (g->adj[linha + 1][coluna] < poder)
        {
            if (g->adj[linha + 1][coluna] > maior)
            {
                maior = g->adj[linha + 1][coluna];
                maiorLinha = linha + 1;
                maiorColuna = coluna;
            }
        }

    if (maiorLinha == -1)
    {
        return;
    }

    poder += maior;
    return poder + dfs(g, poder, maiorLinha, maiorColuna);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    Graph g = graphInit(N, M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int v;
            scanf("%d", &v);
            g->adj[i][j] = v;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int resultado = dfs(g, g->adj[i][j], i, j);
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d ", g->adj[i][j]);
        }
    }
}