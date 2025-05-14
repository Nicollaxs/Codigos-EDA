#include <stdio.h>
#include <stdlib.h>

//MatrizInit Insert Remove Edge 

typedef struct Grafo{
    int V;
    int e;
    int **adj;
}*Grafo;

typedef struct Edge{
    int v;
    int w;
}Edge;

int *pre;
int count = 0;

Grafo graphInit(int V){

    Grafo g = malloc(sizeof(**g));
    g->V = V;
    g->e = 0;
    g->adj = matrizInit(V,V,0);

    pre = malloc(sizeof(int) * V);

    for(int i = 0; i < V; i++){
        pre[i] = -1;
    }

    return g;
}

int **matrizInit(int v, int w, int c){
    int **m = malloc(sizeof(int *)*v);

    for(int i = 0; i < v; i++){
        m[i] = malloc(sizeof(int) * w);
        for(int j = 0; j < w; i++){
            m[i][j] = c;
        }
    }

    return m;
}

Edge edge(int v, int w){
    Edge e;
    e.v = v;
    e.w = w;

    return e;
}

void insertEdge(Grafo g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
    g->e ++;
}

void removeEdge(Grafo g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;
    g->e = --;
}

void dfs(Grafo g, Edge e){

    int w = e.w;
    pre[w] = count++;

    for(int i = 0; i < g->V; i++){
        if(g->adj[w][i] == 1 && pre[i] == 0){
            printf("( %d , %d )\n", e.w, e.i);
            dfs(g, edge(w,i));
        }
    }
}




