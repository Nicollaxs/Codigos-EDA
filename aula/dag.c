#include <stdio.h>
#include <stdlib.h>

//new Insert Remove GrafoInit edge

typedef struct node *link;
// anotar essa parte
struct node{
    int valor;
    link prox;  
};

typedef struct Grafo{
    int V;
    int e;
    link *adj;
}*Grafo;

typedef struct Edge{
    int v;
    int w;
}Edge;

typedef struct Pilha{
    int v;
    struct Pilha *prox;
}Pilha;


Pilha *topo = NULL;

void push(int v){
    Pilha *novo = malloc(sizeof(Pilha));
    novo->v = v;
    novo->prox = topo;
    topo = novo;
}

int pop(){
    if(topo == NULL)
        return -1;

    Pilha *p = topo;
    int v = p->v;
    topo = p->prox;
    free(p);
    return v;
}

int *pre;
int count = 0;

Grafo* graphInit(int V){

    Grafo grafo = malloc(sizeof(*grafo));
    grafo->V = V;
    grafo->e = 0;
    grafo->adj = malloc(sizeof(link)*V);

    for(int i = 0; i < V; i ++){
        grafo->adj[i] = NULL;
    }

    pre = malloc(sizeof(int) * V);

    for(int i = 0; i < V; i++){
        pre[i] = -1;
    }

    return grafo;
}

link new(int valor, link prox){
    link l = malloc(sizeof(struct node));
    l->valor = valor;
    l->prox = prox; 
    return l;
}

Edge edge(int v, int w) {
    Edge e = {v, w};
    return e;
}


void insertEdge(Grafo *g, Edge e){
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
    g->adj[w] = new(v,g->adj[w]);
    g->e ++; 
}

void removeEd(Grafo *g, int v, int w){

    link atual = g->adj[v];
    link anterior = NULL;

    while(atual){
        if(atual->valor == w){
            if(anterior == NULL){
                g->adj[v] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void removeEdge(Grafo *g, Edge e){
    
    int v = e.v;
    int w = e.w;

    removeEd(g,v,w);
    removeEd(g,w,v);

    g->e--;
}

void dfs(Grafo *g, int w){

    pre[w] = count++;

    link l;
    for(l = g->adj[w]; l != NULL; l = l->prox){
        if(pre[l->valor] == -1){
            dfs(g, l->valor);
        }
    }
}

void dfsInterarivo(Grafo *g, int start){
    
    push(start);

    while(topo != NULL){
        int v = pop();

        if(pre[v] == -1){
            pre[v] = count ++;
        }

        for(link l = g->adj[v]; l != NULL; l = l->prox){
            if(pre[l->valor] == -1){
                push(l->valor);
            }
        }
    }
}

Grafo graphReserve(Grafo g){
    Grafo new = matrizInit(g->v, g->v, 0);
    for(int i = 0; i < g->v; i++){
        for(link l = g->adj[i]; l != NULL; l = l->prox)
        {
            insertEdge(new, edge(l->valor, i));
        }
    }
    return new;
}


////////////////////////////////// IMPLEMENTAÇÃO DE DAG COM DFS //////////////////////////////////////

int cnt; // variável global usada para preencher o vetor ts

void tsDfsRecursivo(Grafo g, int v, int ts[]) {
    pre[v] = 0;
    for(link t = g->adj[v]; t != NULL; t = t->prox) {
        if(pre[t->valor] == -1)
            tsDfsRecursivo(g, t->valor, ts);
    }
    ts[cnt++] = v;
}

void dag(Grafo g, int ts[]) {
    cnt = 0;
    for(int v = 0; v < g->V; v++) {
        ts[v] = -1;
        pre[v] = -1;
    }

    for(int v = 0; v < g->V; v++) {
        if(pre[v] == -1)
            tsDfsRecursivo(g, v, ts);
    }
}


///////////////////// IMPLEMENTAÇÃO DE DAG COM BSF ///////////////////////////////

void dag_bsf(Grafo g, int ts[]){

    for(int v = 0; v < g->V; v++){
        ts[v] = -1;
        in[v] = 0;
    }

    for(int v = 0; g->V; v++)
        for(link l = g->adj[v]; l!= NULL; l = l->prox)
            in[l->valor]++;
        
    queueInit(g->V);

    for(int v = 0; v < g->V; v++){
        if(in[v] == 0)
            enqueue(v);
    }

    int cont = 0;

    while(!queueIsEmpty()){
        int v = dequeue();
        ts[count++] = v;

        for(link l = g->adj[v]; l!=NULL; l = l->prox){
            in[l->valor]--;

            if(in[l->valor] == 0)
                enqueue(l->valor);
        }
    }
}






  






