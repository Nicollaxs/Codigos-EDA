#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000
// new Insert Remove GrafoInit edge

typedef struct node *link;
// anotar essa parte
struct node
{
    int valor;
    link prox;
};

typedef struct Grafo
{
    int V;
    int e;
    link *adj;
} Grafo;

typedef struct Edge
{
    int v;
    int w;
} Edge;

typedef struct Pilha
{
    int v;
    struct Pilha *prox;
} Pilha;

Pilha *topo = NULL;

void push(int v)
{
    Pilha *novo = malloc(sizeof(Pilha));
    novo->v = v;
    novo->prox = topo;
    topo = novo;
}

int pop()
{
    if (topo == NULL)
        return -1;

    Pilha *p = topo;
    int v = p->v;
    topo = p->prox;
    free(p);
    return v;
}

int *pre;
int count = 0;

Grafo *graphInit(int V)
{

    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->e = 0;
    grafo->adj = malloc(sizeof(link) * V);

    for (int i = 0; i < V; i++)
    {
        grafo->adj[i] = NULL;
    }

    pre = malloc(sizeof(int) * V);

    for (int i = 0; i < V; i++)
    {
        pre[i] = -1;
    }

    return grafo;
}

link new(int valor, link prox)
{
    link l = malloc(sizeof(struct node));
    l->valor = valor;
    l->prox = prox;
    return l;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

void insertEdge(Grafo *g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v, g->adj[w]);
    g->e++;
}

void removeEd(Grafo *g, int v, int w)
{

    link atual = g->adj[v];
    link anterior = NULL;

    while (atual)
    {
        if (atual->valor == w)
        {
            if (anterior == NULL)
            {
                g->adj[v] = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void removeEdge(Grafo *g, Edge e)
{

    int v = e.v;
    int w = e.w;

    removeEd(g, v, w);
    removeEd(g, w, v);

    g->e--;
}

void dfs(Grafo *g, int w)
{

    pre[w] = count++;

    link l;
    for (l = g->adj[w]; l != NULL; l = l->prox)
    {
        if (pre[l->valor] == -1)
        {
            dfs(g, l->valor);
        }
    }
}

void dfsInterarivo(Grafo *g, int start)
{

    push(start);

    while (topo != NULL)
    {
        int v = pop();

        if (pre[v] == -1)
        {
            pre[v] = count++;

            for (link l = g->adj[v]; l != NULL; l = l->prox)
            {
                if (pre[l->valor] == -1)
                    push(l->valor);
            }
        }
    }
}

void graphcptD1(Grafo g, int s, int *pa, int *dist){

    bool mature[1000];
    for(int v = 0; v <g->v; v++){
        pa[v] = -1;
        mature[v] = false;
        dist[v] = INT_MAX;
    }

    pa[s] = s;
    dist[s] = 0;

    while(true){
        int min = INT_MAX;
        int y;
        for(int z = 0; z < g->v; z++){
            if(mature[z])
                continue;
            if(dist[z] < min){
                min = dist[z];
                y = z;
            }
        }

        if(min == INT_MAX)
            break;
        
        for(link a = g->adj[y]; a!= NULL; a = a->next){
            if(mature[a->v])
                continue;
            
            if(dist[y] + a->c < dist[a->v]){
                dist[a->v] = dist[y] + a->c;
                pa[a->v] = y;
            }
        }
        mature[y] = true;
    }
}

int main()
{
    int V = 8; // número de vértices
    Grafo *g = graphInit(V);

    // Inserindo algumas arestas
    insertEdge(g, edge(0, 2));
    insertEdge(g, edge(0, 5));
    insertEdge(g, edge(1, 7));
    insertEdge(g, edge(2, 6));
    insertEdge(g, edge(3, 4));
    insertEdge(g, edge(3, 5));
    insertEdge(g, edge(4, 5));
    insertEdge(g, edge(4, 6));
    insertEdge(g, edge(4, 7));

    printf("DFS Recursiva:\n");
    count = 0;
    for (int i = 0; i < V; i++)
        pre[i] = -1;
    dfs(g, 0);
    for (int i = 0; i < V; i++)
    {
        printf("pre[%d] = %d\n", i, pre[i]);
    }

    printf("\nDFS Iterativa:\n");
    count = 0;
    for (int i = 0; i < V; i++)
        pre[i] = -1;
    dfsInterarivo(g, 0);
    for (int i = 0; i < V; i++)
    {
        printf("pre[%d] = %d\n", i, pre[i]);
    }

    return 0;
}
