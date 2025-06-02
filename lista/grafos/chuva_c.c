#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph
{
    int v;
    int e;
    char **adj;
} *Graph;

typedef struct Edge
{
    int v;
    int w;
} Edge;

char **matrizInit(int linhas, int colunas, char valDefault)
{
    char **m = malloc(sizeof(char *) * linhas);

    for (int i = 0; i < linhas; i++)
    {
        m[i] = malloc(sizeof(char) * colunas);
        for (int j = 0; j < colunas; j++)
        {
            m[i][j] = valDefault;
        }
    }
    return m;
}

Graph graphInit(int num_linhas_v, int num_colunas_w)
{
    Graph g = malloc(sizeof(struct Graph));
    g->adj = matrizInit(num_linhas_v, num_colunas_w, '.');
    g->e = 0;
    g->v = num_linhas_v;
    return g;
}

Edge edge(int linha_v, int coluna_w)
{
    Edge e_obj = {linha_v, coluna_w};
    return e_obj;
}

void dfs(Graph g, Edge celulaAtual, int M_numColunas)
{
    int r = celulaAtual.v;
    int c = celulaAtual.w;

    if (r < 0 || r >= g->v || c < 0 || c >= M_numColunas)
    {
        return;
    }

    if (g->adj[r][c] == '#')
    {
        return;
    }
    if (g->adj[r][c] == 'o')
    {
        return;
    }

    g->adj[r][c] = 'o';

    dfs(g, edge(r + 1, c), M_numColunas);

    if (r + 1 < g->v && g->adj[r + 1][c] == '#')
    {
        dfs(g, edge(r, c - 1), M_numColunas);
        dfs(g, edge(r, c + 1), M_numColunas);
    }
}

int main()
{
    int N, M;
    if (scanf("%d %d", &N, &M) != 2)
    {
        return 1;
    }

    Graph g = graphInit(N, M);

    char *linhaBuffer = malloc(sizeof(char) * (M + 2));

    for (int i = 0; i < N; i++)
    {
        scanf("%s", linhaBuffer);
        for (int j = 0; j < M; j++)
        {
            if (linhaBuffer[j] == '\0')
                break;
            g->adj[i][j] = linhaBuffer[j];
        }
    }

    int linhaComeco = 0;
    int colunaComeco = -1;

    for (int j = 0; j < M; j++)
    {
        if (g->adj[linhaComeco][j] == 'o')
        {
            colunaComeco = j;
            break;
        }
    }

    if (colunaComeco != -1)
    {
        g->adj[linhaComeco][colunaComeco] = '.';
        dfs(g, edge(linhaComeco, colunaComeco), M);
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%c", g->adj[i][j]);
        }
        printf("\n");
    }

    free(linhaBuffer);
    for (int i = 0; i < g->v; i++)
    {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);

    return 0;
}
