#include <stdio.h>
#include <stdlib.h>

// MatrizInit GraphInit Insert Remove Edge

typedef struct Graph
{
    int v, e;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

typedef struct Fila
{
    int v;
    struct Fila *prox;
} Fila;

Fila *cabeca;
Fila *ultimo;
int *visitados;
int contador;


void enqueue(int v)
{
    Fila *novo = malloc(sizeof(struct Fila));
    novo->v = v;
    novo->prox = NULL;

    if (!cabeca)
    {
        cabeca = novo;
        ultimo = novo;
    }
    else
    {
        ultimo->prox = novo;
        ultimo = novo;
    }
}

int dequeue()
{
    if (!cabeca)
    {
        printf("Fila Vazia !\n");
        return -1;
    }

    Fila *aux = cabeca;
    int v = aux->v;
    cabeca = cabeca->prox;
    free(aux);
    return v;
}

int** matrizInit(int v, int w, int c)
{
    int **m = malloc(sizeof(int *) * v);

    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);

        for (int j = 0; j < w; j++)
        {
            m[i][j] = 0;
        }
    }

    return m;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->v = v;
    g->adj = matrizInit(v,v,0);

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

void removeEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;

    g->e--;
}

void bfs(Graph g, int start)
{
    enqueue(start);
    visitados[start] = contador++;

    while(cabeca){

        int a = dequeue();
        
        for(int i = 0; i < g->v; i++){
            if(g->adj[a][i] == 1 && visitados[i] == -1){
                enqueue(i);
                visitados[i] = contador++;
            }
        }

    }
}

int main(){
    int tamanho = 8;
    Graph g = graphInit(8);

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


    printf("BFS : \n");
    visitados = malloc(sizeof(int) * tamanho);

    for(int i = 0; i<tamanho; i++){
        visitados[i] = -1;
    }

    bfs(g,0);

    for(int i = 0; i < tamanho; i++){
        printf("Posicao %d : %d \n", i, visitados[i]);
    }

    return 0;
}
