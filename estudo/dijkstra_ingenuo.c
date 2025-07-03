#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge *link;

struct Edge
{
    int v, c;
    link prox;
};

typedef struct Graph
{
    int V, E;
    link *adj;
} *Graph;

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(*g));
    g->V = v;
    g->E = 0;
    g->adj = malloc(sizeof(link) * v);

    for (int i = 0; i < g->V; i++)
    {
        g->adj[i] = NULL;
    }

    return g;
}

link new(int v, int c, link prox)
{
    link n = malloc(sizeof(struct Edge));
    n->v = v;
    n->c = c;
    n->prox = prox;

    return n;
}

void insertEdge(Graph g, int v, int w, int c)
{
    g->adj[v] = new(w, c, g->adj[v]);
    g->E++;
}

void dijkstra(Graph g, int s, int *dist, int *pa)
{

    bool mature[g->V];

    for (int i = 0; i < g->V; i++)
    {
        dist[i] = __INT_MAX__;
        pa[i] = -1;
        mature[i] = false;
    }

    dist[s] = 0;
    pa[s] = s;

    while (true)
    {
        int min = __INT_MAX__;
        int y;

        for (int z = 0; z < g->V; z++)
        {
            if (mature[z])
                continue;

            if (dist[z] < min)
            {
                min = dist[z];
                y = z;
            }
        }

        if (min == __INT_MAX__)
            break;

        for (link l = g->adj[y]; l != NULL; l = l->prox)
        {
            if (dist[y] + l->c < dist[l->v])
            {
                dist[l->v] = dist[y] + l->c;
                pa[l->v] = y;
            }
        }

        mature[y] = true; 
    }
}

int main() {
    // Exemplo com 5 vértices
    Graph g = graphInit(5);

    // Adicionando arestas (v, w, custo)
    insertEdge(g, 0, 1, 10);
    insertEdge(g, 0, 3, 5);
    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 2);
    insertEdge(g, 2, 4, 4);
    insertEdge(g, 3, 0, 3);
    insertEdge(g, 3, 2, 9);
    insertEdge(g, 3, 4, 2);
    insertEdge(g, 4, 0, 7);
    insertEdge(g, 4, 2, 6);

    int dist[5];
    int pa[5];

    dijkstra(g, 0, dist, pa);

    printf("Menores distâncias a partir do vértice 0:\n");
    for (int i = 0; i < 5; i++) {
        printf("Para %d: %d\n", i, dist[i]);
    }

    printf("\nPredecessores:\n");
    for (int i = 0; i < 5; i++) {
        printf("Para %d: %d\n", i, pa[i]);
    }

    return 0;
}

