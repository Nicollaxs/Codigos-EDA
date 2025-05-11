#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

//Definição do nó
struct node{
    int v;
    link next;
};

//Definição do Grafo
typedef struct Graph{
    int v;
    int e;
    link *listaAdj;
}*Graph;

//Definição de aresta
typedef struct Edge{
    int v,w;
}Edge;

//Função Para criar novo nó
link new(int v, link next){
    link novo = malloc(sizeof(*novo));
    novo->v = v;
    novo->next = next;

    return novo;
}

//Inicializa o Grafo
Graph graphInit(int V){
    int v;
    Graph g = malloc(sizeof(*g));
    g->v = V;
    g->e = 0;
    g->listaAdj = malloc(sizeof(link) * V); //Aloca lista de adj

    //Inicializa lista de adj
    for(v = 0;v < V; v++)
        g->listaAdj[v] = NULL;

    return g;
}

//Função para inserir
void graphInsert(Graph g, Edge e){
    int v = e.v;
    int w = e.w;

    g->listaAdj[v] = new(w,g->listaAdj[v]);
    g->listaAdj[w] = new(v, g->listaAdj[w]);
    g->e++;
}

//Função para remover
void graphRemove(Graph g, Edge e){
    int v = e.v;
    int w = e.w;

    link l = g->listaAdj[v], r = g->listaAdj[w];
    g->listaAdj[v] = g->listaAdj[v]->next;
    g->listaAdj[w] = g->listaAdj[w]->next;

    free(l);
    free(r);
}

//Função que cria aresta
Edge edge(int v, int w){
    Edge edg;
    edg.v = v;
    edg.w = w;

    return edg;
}

//Função que passa as arestas para uma lista
int graphEdges(Edge a[], Graph g) {
    int v;
    int count = 0;
    link l;

    for (v = 0; v < g->v; v++) {
        for (l = g->listaAdj[v]; l != NULL; l = l->next) {
            if (v < l->v) {
                a[count++] = edge(v, l->v);
            }
        }
    }

    return count;
}

void imprimeEdges(Edge a[], int qtd){

    for(int i = 0; i < qtd; i++){
        printf("(%d, %d)\n", a[i].v,a[i].w);
    }
}


int main(){

    Graph g = graphInit(4);

    Edge vet[4] = {edge(0,1),edge(0,2),edge(1,3),edge(2,3)};

    graphInsert(g,edge(0,1));
    graphInsert(g,edge(0,2));
    graphInsert(g,edge(1,3));
    graphInsert(g,edge(2,3));

    int n = graphEdges(vet, g);

    imprimeEdges(vet,n);

    return 0;
}







