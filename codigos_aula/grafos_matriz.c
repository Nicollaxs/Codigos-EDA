#include <stdio.h>
#include <stdlib.h>

// Definição de aresta
typedef struct {
    int v; // vértice de origem
    int w; // vértice de destino
} Edge;

// Definição do grafo
typedef struct Graph {
    int e;       // número de arestas
    int v;       // número de vértices
    int **adj;   // matriz de adjacência
}*Graph; 

// Inicializa uma matriz v x w com valor val
int **matrizInit(int v, int w, int val) {
    int **m = malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++) {
        m[i] = malloc(w * sizeof(int));
        for (int j = 0; j < w; j++)
            m[i][j] = val;
    }
    return m;
}

// Inicializa um grafo com v vértices
Graph graphInit(int v) {
    //Graph já é um ponteiro pra struct
    Graph g = malloc(sizeof(*g)); //sizeof(*g) é o tamanho da struct, e não do ponteiro.
    g->v = v;
    g->e = 0;
    g->adj = matrizInit(v, v, 0);
    return g;
}

// Cria uma aresta
Edge edge(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

// Insere uma aresta no grafo
void graphInsertE(Graph g, Edge e) {
    int v = e.v, w = e.w;
    if (g->adj[v][w] == 0) g->e++;
    g->adj[v][w] = 1;
    g->adj[w][v] = 1; // se for não-direcionado
}

// Remove uma aresta do grafo
void graphRemoveE(Graph g, Edge e) {
    int v = e.v, w = e.w;
    if (g->adj[v][w] == 1) g->e--;
    g->adj[v][w] = 0;
    g->adj[w][v] = 0;
}

// Retorna as arestas do grafo no vetor a[]
int graphEdges(Edge a[], Graph G) {
    int v, w, e = 0;
    for (v = 0; v < G->v; v++) {
        for (w = v + 1; w < G->v; w++) {
            if (G->adj[v][w] == 1)
                a[e++] = edge(v, w);
        }
    }
    return e;
}

int main() {
    Graph g = graphInit(5);
    graphInsertE(g, edge(0, 1));
    graphInsertE(g, edge(0, 2));
    graphInsertE(g, edge(1, 3));

    Edge a[10];
    int n = graphEdges(a, g);
    printf("Arestas:\n");
    for (int i = 0; i < n; i++)
        printf("(%d, %d)\n", a[i].v, a[i].w);

    return 0;
}
