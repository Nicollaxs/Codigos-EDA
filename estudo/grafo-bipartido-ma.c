#include <stdio.h>
#include <stdlib.h>

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
    link prox;
};

int *cor;
link comeco;
link fim;
int *visitado;
int contador = 0;

void enqueue(int v)
{
    link l = malloc(sizeof(struct node));
    l->prox = NULL;
    l->v = v;

    if (!comeco)
    {
        comeco = l;
        fim = l;
        return;
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
        return -1;

    link aux = comeco;
    comeco = comeco->prox;
    int v = aux->v;
    free(aux);
    return v;
}

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
    g->e = 0;
    g->v = v;

    cor = malloc(sizeof(int) * g->v);
    visitado = malloc(sizeof(int) * g->v);
    for (int i = 0; i < v; i++)
    {
        cor[i] = -1;
        visitado[i] = -1;
    }

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

void removeVertice(Graph g, int v)
{

    for (int i = 0; i < g->v; i++)
    {
        if (g->adj[v][i] == 1)
        {
            g->adj[v][i] = 0;
        }
    }
}

int ehBipartido(Graph g, int start)
{
    enqueue(start);
    cor[start] = 0;

    while (comeco != NULL)
    {
        int v = dequeue();
        visitado[v] = contador++;

        for (int i = 0; i < g->v; i++)
        {
            if (g->adj[v][i] == 1)
            {
                if (visitado[i] == -1)
                {
                    cor[i] = 1 - cor[v];
                    enqueue(i);
                }
                else
                {
                    if (cor[i] == cor[v])
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
}

int main()
{

    int atletas, conflitos;
    scanf("%d %d", &atletas, &conflitos);

    Graph g = graphInit(atletas);

    for (int i = 0; i < conflitos; i++)
    {
        int v, w;
        scanf("%d %d", &v, &w);
        insertEdge(g, edge(v, w));
    }

    int resultado = ehBipartido(g, 0);

    if (resultado)
    {
        printf("Sim\n");
    } else {
        printf("Nao\n");
    }
}