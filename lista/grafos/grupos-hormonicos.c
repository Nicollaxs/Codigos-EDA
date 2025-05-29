#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

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

link new(int v, link prox)
{

    link n = malloc(sizeof(struct node));
    n->prox = prox;
    n->v = v;
    return n;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->e = 0;
    g->v = v;
    g->adj = malloc(sizeof(link) * v);

    cor = malloc(sizeof(int) * v);
    visitado = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        g->adj[i] = NULL;

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

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);
    g->e++;
}

int ehBipartido(Graph g, int start)
{
    enqueue(start);
    cor[start] = 0;

    while (comeco != NULL)
    {
        int v = dequeue();
        visitado[v] = contador++;

        for (link l = g->adj[v]; l != NULL; l = l->prox)
        {
            if (visitado[l->v] == -1)
            {
                cor[l->v] = 1 - cor[v];
                enqueue(l->v);
            }
            else
            {
                if (cor[l->v] == cor[v])
                {
                    return 0;
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
    }
    else
    {
        printf("Nao\n");
    }
}