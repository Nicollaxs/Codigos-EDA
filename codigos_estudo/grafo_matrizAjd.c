#include <stdio.h>
#include <stdlib.h>

//matrizInit GraphInit Edge GraphInsert GraphRemove 

typedef struct Graph{
    int v;
    int e;
    int **adj;
}*Graph;

typedef struct Edge{
    int v, w;
}Edge;

int** matrizInit(int v, int w, int c){
    int **m = malloc(sizeof(int *) * v); //Aloca um vetor

    for(int i = 0; i < v; i++){
        m[i] = malloc(sizeof(int) * w); // Em cada linha do vetor aloca outro vetor
        for(int j = 0; j < w; j++){
            m[i][j] = c;
        }
    }

    return m;
}

Graph graphInit(int V){

    Graph g = malloc(sizeof(*g));
    g->v = V;  
    g->e = 0; 
    g->adj = matrizInit(V,V,0);

    return g;
}

Edge edge(int v, int w){
    Edge edg;
    edg.v = v;
    edg.w = w;

    return edg;
}

void graphInsert(Graph g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
    g->e ++;
}

void graphRemove(Graph g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;
    g->e --;
}

void dfsR(Graph g, Edge e){
    int t,w = e.w;

    pre[w] = count++; //Lista de já visitados

    for(t = 0; t < g->v; t++){
        if(g->adj[w][t] != 0) //Verifica se na matriz é uma aresta
            if(pre[t] == -1) // Verifica se ainda não foi visitado
                dfsR(g,edge(w,t));
    }
}
