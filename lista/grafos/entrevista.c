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
int *componente;
int contador = 0;

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

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->adj = matrizInit(v, v, 0);
    g->v = v;
    g->e = 0;

    pre = malloc(sizeof(int) * v);
    for (int i = 0; i < v; i++)
        pre[i] = -1;

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

void dfs(Graph g, Edge e, int componenteAtual)
{
    int w = e.w;
    pre[w] = contador++;
    componente[w] = componenteAtual;

    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[w][i] == 1 && pre[i] == -1)
        {
            dfs(g, edge(i, i), componenteAtual);
        }
    }
}

int componenteConexo(Graph g)
{
    componente = malloc(sizeof(int) * g->v);
    for (int i = 0; i < g->v; i++)
        componente[i] = -1;

    contador = 0;
    int componenteAtual = 0;

    for (int i = 0; i < g->v; i++)
    {
        if (pre[i] == -1)
        {
            dfs(g, edge(i, i), componenteAtual);
            componenteAtual++;
        }
    }
    return componenteAtual;
}

int temAmigosNaEntrevista(int vet[], int tamanho, int maxComp)
{
    int *freq = calloc(maxComp, sizeof(int));
    for (int i = 0; i < tamanho; i++)
    {
        int comp = componente[vet[i]];
        freq[comp]++;
        if (freq[comp] > 1)
        {
            free(freq);
            return 1;
        }
    }
    free(freq);
    return 0;
}

int main()
{
    int vertices;
    scanf("%d", &vertices);

    Graph g = graphInit(vertices);

    char *linha = malloc((g->v + 1) * sizeof(char));
    for (int i = 0; i < g->v; i++)
    {
        scanf("%s", linha);
        for (int j = 0; j < g->v; j++)
        {
            g->adj[i][j] = linha[j] - '0';
        }
    }
    free(linha);

    int totalComponentes = componenteConexo(g);

    int quantidadeEntrevistas;
    scanf("%d", &quantidadeEntrevistas);

    char *respostas = malloc(quantidadeEntrevistas * sizeof(char));

    for (int i = 0; i < quantidadeEntrevistas; i++)
    {
        int participantes;
        scanf("%d", &participantes);

        int *vet = malloc(sizeof(int) * participantes);
        for (int j = 0; j < participantes; j++)
        {
            int p;
            scanf("%d", &p);
            vet[j] = p - 1;
        }

        int resultado = temAmigosNaEntrevista(vet, participantes, totalComponentes);
        respostas[i] = (resultado == 1) ? 'S' : 'N';

        free(vet);
    }

    for (int i = 0; i < quantidadeEntrevistas; i++)
        printf("%c\n", respostas[i]);

    free(respostas);
    free(pre);
    free(componente);

    for (int i = 0; i < g->v; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);

    return 0;
}
