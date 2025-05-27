#include <stdio.h>
#include <stdlib.h>

// GraphInit MatrizInit InsertEdge Edge
typedef struct node *link;

struct node
{
    int v;
    link prox;
};

typedef struct Graph
{
    int v;
    int e;
    int **adj;
} *Graph;

typedef struct Edge
{
    int v, w;
} Edge;

int *pre;
int contador = 0;
int menorIndiceComponente;

int **matrizInit(int v, int w, int c)
{
    int **m = malloc(sizeof(int *) * v);
    pre = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        m[i] = malloc(sizeof(int) * w);
        for (int j = 0; j < w; j++)
        {
            m[i][j] = c;
        }
    }

    for (int i = 0; i < v; i++)
    {
        pre[i] = -1;
    }

    return m;
}

Graph graphInit(int v)
{
    Graph g = malloc(sizeof(struct Graph));
    g->adj = matrizInit(v, v, 0);
    g->e = 0;
    g->v = v;
    return g;
}

Edge edge(int v, int w)
{
    Edge e = {v, w};
    return e;
}

void insertEdge(Graph g, Edge e)
{
    int v = e.v;
    int w = e.w;

    g->adj[v][w] = 1;
    g->adj[w][v] = 1;
    g->e++;
}

void dfs(Graph g, Edge e)
{
    int w = e.w;
    pre[w] = contador++;

    if (w < menorIndiceComponente)
    {
        menorIndiceComponente = w;
    }

    for (int i = 0; i < g->v; i++)
        if (g->adj[w][i] == 1 && pre[i] == -1)
            dfs(g, edge(i, i));
}


void componentesConexos(Graph grafo, int cidadeInicialJoao) {
    // Variáveis para guardar as informações do componente de João
    int tamanhoComponenteJoao;
    int menorNoComponenteJoao; // O nó com menor índice dentro do componente de João

    // 1. Processa o componente de João
    contador = 0; // Zera o contador de nós para a DFS
    menorIndiceComponente = cidadeInicialJoao; // Inicializa para encontrar o menor nó no componente de João
    dfs(grafo, edge(cidadeInicialJoao, cidadeInicialJoao)); // Roda a DFS a partir da cidade de João
    
    tamanhoComponenteJoao = contador;          // Guarda o tamanho do componente de João
    menorNoComponenteJoao = menorIndiceComponente; // Guarda o nó de menor índice do componente de João

    // 2. Inicializa as variáveis que vão rastrear o melhor componente encontrado até agora.
    //    No início, o melhor é o próprio componente de João.
    int melhorTamanhoComponenteGeral = tamanhoComponenteJoao;
    int representanteMenorNoMelhorComponenteGeral = menorNoComponenteJoao;

    contador = 0; // Zera o contador para as próximas DFS

    // 3. Itera por todas as cidades para encontrar outros componentes
    for (int indiceCidadeAtual = 0; indiceCidadeAtual < grafo->v; indiceCidadeAtual++) {
        // Verifica se a cidade 'indiceCidadeAtual' já foi visitada (pre[indiceCidadeAtual] != -1).
        // Se não foi visitada (pre[indiceCidadeAtual] == -1), ela pertence a um novo componente.
        if (pre[indiceCidadeAtual] == -1) {
            // Encontramos um novo componente que ainda não foi explorado.
            menorIndiceComponente = indiceCidadeAtual; // Inicializa para encontrar o menor nó neste novo componente
            dfs(grafo, edge(indiceCidadeAtual, indiceCidadeAtual)); // Roda DFS para este novo componente
            
            int tamanhoComponenteDescoberto = contador;
            int menorNoComponenteDescoberto = menorIndiceComponente;

            // 4. Compara o componente descoberto com o "melhor componente geral"
            if (tamanhoComponenteDescoberto > melhorTamanhoComponenteGeral) {
                // O componente descoberto é maior que o melhor que tínhamos.
                melhorTamanhoComponenteGeral = tamanhoComponenteDescoberto;
                representanteMenorNoMelhorComponenteGeral = menorNoComponenteDescoberto;
            } else if (tamanhoComponenteDescoberto == melhorTamanhoComponenteGeral) {
                // O componente descoberto tem o MESMO tamanho do melhor que tínhamos.
                // Agora aplicamos as regras de desempate:

                // Regra 1: Se o "melhor componente geral" atual é o de João, João tem a preferência.
                // (ou seja, se representanteMenorNoMelhorComponenteGeral == menorNoComponenteJoao)
                // Nesse caso, não fazemos nada, pois João já é o preferido.

                // Regra 2: Se o "melhor componente geral" NÃO é o de João,
                // preferimos o componente (entre o "melhor geral atual" e o "descoberto")
                // que tenha a cidade (nó) de menor índice como representante.
                if (representanteMenorNoMelhorComponenteGeral != menorNoComponenteJoao) {
                    if (menorNoComponenteDescoberto < representanteMenorNoMelhorComponenteGeral) {
                        representanteMenorNoMelhorComponenteGeral = menorNoComponenteDescoberto;
                        // O tamanho continua o mesmo (melhorTamanhoComponenteGeral)
                    }
                }
            }
        }
        contador = 0; // Zera o contador para a próxima iteração/DFS
    }

    // 5. Decide a saída com base no melhor componente encontrado
    if (representanteMenorNoMelhorComponenteGeral == menorNoComponenteJoao) {
        // O melhor componente escolhido é o de João.
        if (tamanhoComponenteJoao == 1) {
            // Condição "Fique em casa": João está no maior componente (o dele próprio),
            // e este componente tem apenas 1 nó (ele mesmo).
            printf("Fique em casa\n");
        } else {
            printf("Bora pra estrada\n");
        }
    } else {
        // O melhor componente escolhido NÃO é o de João.
        printf("Vamos para %d\n", representanteMenorNoMelhorComponenteGeral);
    }
}

int main()
{
    int quantidadeDeVertices;
    int verticeAtual;

    scanf("%d %d", &quantidadeDeVertices, &verticeAtual);

    Graph g = graphInit(quantidadeDeVertices);

    int v, w;
    while (scanf("%d %d", &v, &w) != EOF)
    {
        insertEdge(g, edge(v, w));
    }

    componentesConexos(g, verticeAtual);

    return 0;
}