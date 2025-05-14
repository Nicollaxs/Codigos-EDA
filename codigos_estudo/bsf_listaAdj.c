#include <stdlib.h>
#include <stdio.h>

// graphInit new edge insertEdge removeEdge

typedef struct node *link;

struct node
{
    int v;
    link prox;
};

typedef struct Grafo
{
    int v;
    int e;
    link *adj;
} *Grafo;

typedef struct Edge
{
    int v, w;
} Edge;

typedef struct Fila
{
    int v;
    struct Fila *prox;
} Fila;

Fila *comeco;
Fila *fim;
int *visitados;
int contador;

void enqueue(int v)
{
    Fila *f = malloc(sizeof(Fila));
    f->v = v;
    f->prox = NULL;

    if (!comeco)
    {
        comeco = f;
        fim = f;
    }
    else
    {
        fim->prox = f;
        fim = f;
    }
}

int dequeue()
{
    if (comeco == NULL)
    {
        printf("Fila vazia ! \n");
        return -1;
    }

    Fila *remove = comeco;
    int v = remove->v;
    comeco = remove->prox;

    if (comeco == NULL)
        fim = NULL;

    free(remove);
    return v;
}

Grafo graphInit(int v)
{

    Grafo grafo = malloc(sizeof(*grafo));
    grafo->v = v;
    grafo->e = 0;

    grafo->adj = malloc(sizeof(link) * v);

    for (int i = 0; i < v; i++)
    {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

link new(int v, link prox)
{
    link novo = malloc(sizeof(struct node));
    novo->v = v;

    novo->prox = prox;
    prox = novo;

    return novo;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

void insertEdge(Grafo g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);

    g->e++;
}

void removeEdge(Grafo g, int v, int w)
{
    link atual = g->adj[v];
    link anterior = NULL;

    while (atual)
    {
        if (atual->v == w)
        {
            if (anterior == NULL)
                g->adj[v] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void removeE(Grafo g, Edge e){

    int v = e.v;
    int w = e.w;

    removeEdge(g,v,w);
    removeEdge(g,w,v);

}

void bfs(Grafo g, int start)
{
    enqueue(start);

    while (comeco != NULL)
    {

        int a = dequeue();
        visitados[a] = contador++;

        for (link l = g->adj[a]; l != NULL; l = l->prox)
        {
            if (visitados[l->v] == -1)
            {
                enqueue(l->v);
            }
        }
    }
}

int main()
{

    int tamanho = 8;
    Grafo g = graphInit(tamanho);

    insertEdge(g, edge(0, 2));
    insertEdge(g, edge(0, 5));
    insertEdge(g, edge(1, 7));
    insertEdge(g, edge(2, 6));
    insertEdge(g, edge(3, 4));
    insertEdge(g, edge(3, 5));
    insertEdge(g, edge(4, 5));
    insertEdge(g, edge(4, 6));
    insertEdge(g, edge(4, 7));

    printf("BFS : \n");

    visitados = malloc(sizeof(int) * tamanho);
    contador = 0;
    for (int i = 0; i < tamanho; i++)
    {
        visitados[i] = -1;
    }

    bfs(g, 0);

    for (int i = 0; i < tamanho; i++)
    {
        printf("Posicao %d : %d \n", i, visitados[i]);
    }
}
