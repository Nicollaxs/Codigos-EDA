#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXV 100005 // Aumentado para 10^5 + 5 para acomodar N = 10^5

typedef struct Edge* link;
struct Edge {
    int w;
    int c; // Capacidade do barco
    link next;
};

typedef struct grafo {
    int v;
    link *adj;
} *Grafo;

// --- Funções para criar o grafo ---
Grafo initGrafo(int V) {
    Grafo g = malloc(sizeof(*g));
    g->v = V;
    g->adj = malloc(V * sizeof(link));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

link new(int w, int c, link next){
    link a = malloc(sizeof(*a));
    a->c = c;
    a->w = w;
    a->next = next;
    return a;
}

void insereAresta(Grafo g, int u, int v, int c) {
    // Grafo não-direcionado, então insere aresta nos dois sentidos
    g->adj[u] = new(v, c, g->adj[u]);
    g->adj[v] = new(u, c, g->adj[v]);
}

// --- Fila de prioridade baseada em max-heap ---

static int *pq;    // Índices dos vértices
static int *qp;    // Posição na heap de cada vértice (-1 se não está)
static int N_heap; // Tamanho da heap
static int *key; // Ponteiro para vetor de chaves (capacidade máxima para chegar a este nó na MST)

// A função less agora compara para uma max-heap
#define less(a,b) (key[a] < key[b]) // a é 'menor' que b se a capacidade de a é menor que a capacidade de b

void exchange(int i, int j) {
    int t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

void fixup(int k) {
    while (k > 1 && less(pq[k/2], pq[k])) { // Alterado para max-heap: pai é menor que o filho
        exchange(k, k/2);
        k = k/2;
    }
}

void fixDown(int k) {
    int j;
    while (2*k <= N_heap) {
        j = 2*k;
        if (j < N_heap && less(pq[j], pq[j+1])) j++; // Alterado para max-heap: escolhe o maior filho
        if (!less(pq[k], pq[j])) break; // Alterado para max-heap: pai é maior ou igual ao filho
        exchange(k, j);
        k = j;
    }
}

void PQInit(int maxN) {
    pq = malloc(sizeof(int) * (maxN + 1));
    qp = malloc(sizeof(int) * (maxN + 1));
    for (int i = 0; i <= maxN; i++) qp[i] = -1;
    N_heap = 0;
}

bool PQEmpty() {
    return N_heap == 0;
}

bool PQContains(int v) {
    return qp[v] != -1;
}

void PQInsert(int v) {
    if (PQContains(v)) return;
    pq[++N_heap] = v;
    qp[v] = N_heap;
    fixup(N_heap);
}

int PQDelMax() { // Renomeado para DelMax
    int max = pq[1];
    exchange(1, N_heap--);
    fixDown(1);
    qp[max] = -1;
    return max;
}

void PQIncreaseKey(int v) { // Renomeado para IncreaseKey
    fixup(qp[v]);
}


// Estrutura para representar a MST
typedef struct MSTEdge {
    int to;
    int capacity;
    struct MSTEdge* next;
} MSTEdge;

MSTEdge* mst_adj[MAXV];

void addMSTEdge(int u, int v, int capacity) {
    MSTEdge* new_edge = malloc(sizeof(MSTEdge));
    new_edge->to = v;
    new_edge->capacity = capacity;
    new_edge->next = mst_adj[u];
    mst_adj[u] = new_edge;

    new_edge = malloc(sizeof(MSTEdge));
    new_edge->to = u;
    new_edge->capacity = capacity;
    new_edge->next = mst_adj[v];
    mst_adj[v] = new_edge;
}

// --- Prim para Maximum Spanning Tree ---
void prim_max_mst(Grafo g) {
    bool in_mst[MAXV];
    int parent[MAXV]; // Armazena o pai do nó na MST
    key = malloc(sizeof(int) * g->v); // Capacidade máxima para alcançar este nó

    for (int i = 0; i < g->v; i++) {
        in_mst[i] = false;
        key[i] = 0; // Inicializa com 0 para capacidades máximas
        parent[i] = -1;
        mst_adj[i] = NULL; // Inicializa a lista de adjacência da MST
    }

    PQInit(g->v);

    key[0] = INT_MAX; // Para garantir que o nó inicial seja selecionado primeiro (pode ser qualquer valor grande)
    PQInsert(0); // Começa da ilha 0 (ou 1, se as ilhas são 1-indexed)

    while (!PQEmpty()) {
        int u = PQDelMax(); // Pega o vértice com a maior chave
        in_mst[u] = true;

        if (parent[u] != -1 && key[u] != INT_MAX) { // Não adiciona aresta para o nó inicial com INT_MAX
            addMSTEdge(u, parent[u], key[u]);
        }

        for (link a = g->adj[u]; a != NULL; a = a->next) {
            if (!in_mst[a->w] && a->c > key[a->w]) { // Se a capacidade for maior, atualiza a chave
                key[a->w] = a->c;
                parent[a->w] = u;
                if (PQContains(a->w)) {
                    PQIncreaseKey(a->w);
                } else {
                    PQInsert(a->w);
                }
            }
        }
    }
    free(key); // Liberar a memória alocada para 'key'
}


// Função para encontrar a capacidade máxima de gargalo entre X e Y na MST
int find_max_bottleneck(int start_node, int end_node, int N_islands) {
    // DFS para encontrar o caminho e o gargalo
    int max_capacity_path = INT_MAX;
    int visited[MAXV];
    for (int i = 0; i < N_islands; i++) visited[i] = 0;

    // Pilha para DFS (representada por um array e um ponteiro de topo)
    int stack_nodes[MAXV];
    int stack_min_capacities[MAXV]; // Capacidade mínima até o nó atual
    int top = -1;

    // Adiciona o nó inicial à pilha
    stack_nodes[++top] = start_node;
    stack_min_capacities[top] = INT_MAX; // Capacidade infinita no início

    while (top != -1) {
        int u = stack_nodes[top];
        int current_min_capacity = stack_min_capacities[top--];

        if (u == end_node) {
            return current_min_capacity; // Encontrou o destino, retorna o gargalo
        }
        
        if (visited[u]) continue; // Já visitado neste caminho
        visited[u] = 1;

        for (MSTEdge* edge = mst_adj[u]; edge != NULL; edge = edge->next) {
            if (!visited[edge->to]) {
                stack_nodes[++top] = edge->to;
                stack_min_capacities[top] = (current_min_capacity < edge->capacity) ? current_min_capacity : edge->capacity;
            }
        }
    }
    return 0; // Não deve acontecer se o grafo é conectado
}


int main() {
    int N, B;
    scanf("%d %d", &N, &B); // N_islands e N_boats

    Grafo g = initGrafo(N);

    for (int k = 0; k < B; k++) {
        int I, J, P;
        scanf("%d %d %d", &I, &J, &P);
        // Ajusta para 0-indexado se as ilhas são 1-indexed na entrada
        insereAresta(g, I - 1, J - 1, P);
    }

    prim_max_mst(g); // Constrói a Maximum Spanning Tree

    int C; // Número de consultas
    scanf("%d", &C);

    for (int k = 0; k < C; k++) {
        int X, Y;
        scanf("%d %d", &X, &Y);
        // Ajusta para 0-indexado
        printf("%d\n", find_max_bottleneck(X - 1, Y - 1, N));
    }

    // Liberar memória alocada (importante para evitar memory leaks)
    for (int i = 0; i < N; i++) {
        link current_edge = g->adj[i];
        while (current_edge != NULL) {
            link temp = current_edge;
            current_edge = current_edge->next;
            free(temp);
        }
        MSTEdge* current_mst_edge = mst_adj[i];
        while (current_mst_edge != NULL) {
            MSTEdge* temp = current_mst_edge;
            current_mst_edge = current_mst_edge->next;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
    free(pq);
    free(qp);
    // 'key' é liberado dentro de prim_max_mst

    return 0;
}