#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge *link;

struct Edge
{
    int v;
    int c;
    link prox;
};

typedef struct Graph
{
    int V, e;
    link *adj;
} *Graph;

typedef struct
{
    int *data; // Vetor
    int front; // Primeiro
    int rear;  // Ultimo
    int items;
} Queue;

Queue *queueInit(int tam)
{

    Queue *q = malloc(sizeof(Queue));
    q->front = 0;
    q->rear = 0;
    q->items = 0;
    q->data = malloc(sizeof(int) * tam);

    return q;
}

void queuePut(Queue *q, int value)
{
    q->data[q->rear] = value;
    q->rear++;
    q->items++;
}

int queueGet(Queue *q)
{
    int v = q->data[q->front];
    q->front++;
    q->items--;
    return v;
}

bool isEmpty(Queue *q)
{
    return q->items == 0;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->V = v;
    g->e = 0;
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
    // Adiciona o w na lista de adj de v.
    g->adj[v] = new(w, c, g->adj[v]);
    g->e++;
}

bool bellmanFord(Graph g, int s, int *dist, int *pa)
{
    bool onqueue[g->e + 2];
    int V = g->V + 1;

    for (int i = 0; i < g->V; i++)
    {
        dist[i] = __INT_MAX__;
        pa[i] = -1;
        onqueue[i] = false;
    }

    Queue *q = queueInit(g->e + 2);

    dist[s] = 0;
    pa[s] = s;
    queuePut(q, s);
    onqueue[s] = true;

    queuePut(q, V);
    int k = 0;

    while (true)
    {
        int v = queueGet(q);

        if (v < V)
        {
            onqueue[v] = false;
            for (link a = g->adj[v]; a != NULL; a = a->prox)
            {
                if (dist[v] + a->c < dist[a->v])
                {
                    dist[a->v] = dist[v] + a->c;
                    pa[a->v] = v;

                    if (!onqueue[a->v])
                    {
                        queuePut(q, a->v);
                        onqueue[a->v] = true;
                    }
                }
            }
        }
        else
        {
            if (isEmpty(q))
                return true;

            if (++k > g->V)
                return false;

            queuePut(q, v);
        }
    }
}



int main() {
    // Exemplo:
    // Grafo com 5 vértices: 0, 1, 2, 3, 4
    Graph g = graphInit(5);

    // Adiciona arestas (v, w, custo)
    insertEdge(g, 0, 1, 6);
    insertEdge(g, 0, 3, 7);
    insertEdge(g, 1, 2, 5);
    insertEdge(g, 1, 3, 8);
    insertEdge(g, 1, 4, -4);
    insertEdge(g, 2, 1, -2);
    insertEdge(g, 3, 2, -3);
    insertEdge(g, 3, 4, 9);
    insertEdge(g, 4, 0, 2);
    insertEdge(g, 4, 2, 7);

    int dist[5];
    int pa[5];

    if (bellmanFord(g, 0, dist, pa)) {
        printf("Menores distâncias a partir do vértice 0:\n");
        for (int i = 0; i < 5; i++) {
            printf("Para %d: %d\n", i, dist[i]);
        }
    } else {
        printf("Existe ciclo negativo no grafo.\n");
    }

    return 0;
}