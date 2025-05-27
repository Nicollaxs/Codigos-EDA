#include <stdio.h>
#include <stdlib.h>

// Edge new GraphInit GraphInsert GraphRemove

typedef struct node *link;

struct node
{
    int valor;
    link *prox;
};

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

int *pre;
int count = 0;
link topo;

void push(int v)
{
    link l = malloc(sizeof(struct node));
    l->prox = topo;
    l->valor = v;
    topo = l;
}

int pop()
{
    if (!topo)
    {
        printf("Pilha vazia");
        return -1;
    }

    link aux = topo;
    int v = topo->valor;
    topo = topo->prox;
    free(aux);

    return v;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(*g));
    g->v = v;
    g->e = 0;

    g->adj = malloc(sizeof(link) * v);

    for (int i = 0; i < v; i++)
    {
        g->adj[i] = NULL;
    }
}

link new(int valor, link prox)
{
    link new = malloc(sizeof(struct node));
    new->valor = valor;
    new->prox = prox;
    return new;
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

void dfs(Graph g, int w)
{
    pre[w] = count++;

    for (link l = g->adj[w]; l != NULL; l = l->prox)
    {
        if (pre[l->valor] == -1)
            dsf(g, l->valor);
    }
}

void dfsInterativo(Graph g, int start)
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

void ordenacaoTopologica(Graph g, int ts[], int in[])
{
    
    for(int i = 0; i < g->v; i++){
        in[i] = 0;
        ts[i] = -1;
    }

    for(int i = 0; i < g->v; i++){
        for(link l = g->adj[i]; l!=NULL; l->prox){
            in[l->valor]++;
        }
    }

    for(int i = 0; i<g->v; i++){
        if(in[i] == 0){
            enqueue(i);
        }
    }

    int contador = 0;

    while(!isEmpty()){
        int v = dequeue();
        ts[count++] = v;

        for(link l = g->adj[v]; l!=NULL; l = l->prox){
            in[l->valor]--;
            if(in[l->valor] == 0)
                enqueue(l->valor);
        }
    }

}
