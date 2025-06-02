#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node
{
    int v;
    link prox;
};

typedef struct Graph
{
    int v, e;
    link *adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

int *salario;
int *chefe;
int *resultados;

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->e = 0;
    g->v = v;

    g->adj = malloc(sizeof(link) * (v + 1));
    for (int i = 0; i <= g->v; i++)
    {
        g->adj[i] = NULL;
    }

    return g;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

link new(int v, link prox)
{
    link n = malloc(sizeof(struct node));
    n->v = v;
    n->prox = prox;
    return n;
}

void insertEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v] = new(w, g->adj[v]);
}

int insatisfeitos(Graph g)
{
    int quantidade = 0;

    for (int i = 1; i <= g->v; i++)
    { // i representa todos os funcionarios

        for (link l = g->adj[i]; l != NULL; l = l->prox)
        { // Verifico todos os funcionarios de i
            if (salario[l->v] > salario[i])
            {
                quantidade++;
                break;
            }
        }
    }

    return quantidade;
}

int main()
{

    int N;
    scanf("%d", &N);

    salario = malloc(sizeof(int) * (N + 1));
    chefe = malloc(sizeof(int) * (N + 1));
    resultados = malloc(sizeof(int) * (N + 1));

    for (int i = 0; i <= N; i++)
    {
        salario[i] = 0;
        chefe[i] = 0;
        resultados[i] = 0;
    }

    Graph g = graphInit(N);

    for (int i = 1; i <= N; i++)
    {
        int c, s; // salario e chefe
        scanf("%d %d", &c, &s);
        chefe[i] = c;
        salario[i] = s;
        insertEdge(g, edge(chefe[i], i));
    }

    int contador = 0;
    resultados[contador++] = insatisfeitos(g);

    int mudanca;
    scanf("%d", &mudanca);

    for (int i = 1; i <= mudanca; i++)
    {

        int funcionario, novoSalario; // salario e chefe
        scanf("%d %d", &funcionario, &novoSalario);

        salario[funcionario] = novoSalario;
        resultados[contador++] = insatisfeitos(g);
    }

    for (int i = 0; i < contador; i++)
    {
        printf("%d\n", resultados[i]);
    }
}