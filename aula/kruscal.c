#include <stdio.h>
#include <stdlib.h>

// Assume que estas estruturas e funções estão definidas em outro lugar:
// struct Edge {
//     int u, v; // Vértices conectados pela aresta
//     int weight; // Peso da aresta
// };
//
// // Função de comparação para ordenar arestas (usada por qsort)
// int compareEdges(const void *a, const void *b) {
//     return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
// }
//
// // Funções da estrutura de dados Union-Find (assumimos que estão implementadas)
// void initialize(int n); // Inicializa 'n' conjuntos disjuntos
// int find(int i);       // Encontra o representante do conjunto que contém 'i'
// void unite(int i, int j); // Mescla os conjuntos que contêm 'i' e 'j'

// Um placeholder para a estrutura Edge e a função de comparação
typedef struct Edge {
    int u, v;
    int weight;
} Edge;

int compareEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Funções Union-Find placeholder
// Em uma implementação real, você teria arrays para parent e rank/size
int *parent;
int *rank; // Usando rank para a heurística union-by-rank

void initialize(int n) {
    parent = (int *)malloc(n * sizeof(int));
    rank = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]); // Compressão de caminho
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);

    if (root_i != root_j) {
        // União por rank
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
    }
}



Edge* MST_Kruskal(Edge* all_edges, int n, int m, int *num_mst_edges) {

    qsort(all_edges, m, sizeof(Edge), compareEdges);

    Edge *mst_edges = (Edge *)malloc((n - 1) * sizeof(Edge));
    *num_mst_edges = 0;

    initialize(n);

    for (int i = 0; i < m; i++) {
        Edge current_edge = all_edges[i];
        int u = current_edge.u;
        int v = current_edge.v;

        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            mst_edges[*num_mst_edges] = current_edge;
            (*num_mst_edges)++;

            unite(u, v);

            if (*num_mst_edges == n - 1) {
                break;
            }
        }
    }

    return mst_edges;
}

// Exemplo de uso:
int main() {
    int n = 4; 
    int m = 5; 

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    int num_mst_edges;
    Edge* mst = MST_Kruskal(edges, n, m, &num_mst_edges);

    printf("Arestas na Árvore Geradora Mínima:\n");
    for (int i = 0; i < num_mst_edges; i++) {
        printf("(%d, %d) - Peso: %d\n", mst[i].u, mst[i].v, mst[i].weight);
    }

    free(mst); 

    return 0;
}

Edge* kruscal(Edge *all_edges, int n, int m, int *num_mst_edges){

    qsort(all_edges);

    Edge* mst = (Edge*) malloc(sizeof(Edge) * n-1);
    *num_mst_edges = 0;

    for(int i = 0; i < m; i++){
        Edge atual = all_edges[i];

        int u = atual.u;
        int v = atual.v;

        int raiz_u = atual.u;
        int raiz_v = atual.v;

        if(raiz_u != raiz_v){
            mst[*num_mst_edges] = atual;
            (*num_mst_edges) ++;

            unite(u,v);

            if(*num_mst_edges == n - 1)
                break;
        }
    }

return mst;
}