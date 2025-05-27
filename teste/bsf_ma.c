#include <stdio.h>
#include <stdlib.h>

typedef struct Node *link;

struct Node{
    int v;
    link *prox;
};

typedef struct Graph{
    int v;
    int e;
    int **adj;
}*Graph;


typedef struct Edge{
    int v, w;
}Edge;

link comeco;
link fim;

void enqueue(int v){
    link l = malloc(sizeof(struct Node));
    l->v = v;
    l->prox = NULL;

    if(!comeco){
        comeco = l;
        fim = l;
    } else {
        fim->prox = l;
        fim = l;
    }
}

int dequeue(){
    if(!comeco)
        return -1;

    link aux = comeco;
    int v = comeco->v;
    comeco = comeco->prox;
    free(aux);
    return v;
}

int **matrizInit(int v, int w, int c){
    int **mat = malloc(sizeof(int) * v);
    
    for(int i = 0; i < v; i ++){
        mat[i] = malloc(sizeof(int) * w);
        for(int j = 0; j < w; j++){
            mat[i][j] = c;
        }
    }

    return mat;
}

Graph graphInit(int v){
    Graph g = malloc(sizeof(struct Graph));
    g->v = v;
    g->e = 0;
    g->adj = matrizInit(v,v,0);

    return g;
}

Edge edge(int v, int w){
    Edge e = {v,w};
    return e;
}

void insertEdge(Graph g, Edge e){
    int v =  e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
    g->e++;
}

void removeEdge(Graph g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 0;
    g->adj[w][v] = 0;
    g->e--;
}

int *visitados;
int count = 0;

void bsf(Graph g, Edge e){
    enqueue(e.w);

    while(comeco){

        int w = dequeue();
        visitados[w] = count++;

        for(int i = 0; i < g->v; i++){
            if(g->adj[w][i] == 1 && visitados[i] == -1){
                enqueue(i);
            }
        }
    }
}

//Grafo reverso com matriz de adjacencia.
Graph graphReverse(Graph g){

    Graph r = graphInit(g->v);
    
    for(int i = 0; i < g->v; i++){
        for(int j = 0; j < g->v; j ++){
            if(g->adj[i][j] == 1){
                r->adj[j][i] = 1;
            }
        }
    }

    return r;
}

//Grafo reverso Lista de Adj
Graph graphReverse(Graph g){
    Graph r = graphInit(g->v);

    for(int i = 0; i < g->v; i++){

        for(link l = g->adj[i]; l!=NULL; l = l->prox){
            insertEdge(r, edge(l->v,i));
        }
    }

    return r;
}


