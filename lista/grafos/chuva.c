#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph
{
    int v; // Número de linhas (N)
    int e; // Não usado consistentemente para colunas na lógica da gota, mas parte da struct original
    char **adj;
} *Graph;

typedef struct Edge
{
    int v; // representa a linha
    int w; // representa a coluna
} Edge;

// Variáveis globais 'pre' e 'contador' não são usadas nesta lógica.
// Se não forem para outro propósito, podem ser removidas.
// int *pre;
// int contador = 0;

char **matrizInit(int linhas, int colunas, char valDefault)
{
    char **m = malloc(sizeof(char *) * linhas);
    if (m == NULL)
    {
        perror("Falha ao alocar memória para linhas da matriz");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < linhas; i++)
    {
        m[i] = malloc(sizeof(char) * colunas);
        if (m[i] == NULL)
        {
            perror("Falha ao alocar memória para colunas da matriz");
            for (int k = 0; k < i; ++k)
                free(m[k]); // Liberar o que já foi alocado
            free(m);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < colunas; j++)
        {
            m[i][j] = valDefault;
        }
    }
    return m;
}

Graph graphInit(int num_linhas_v, int num_colunas_w)
{
    Graph g = malloc(sizeof(struct Graph));
    if (g == NULL)
    {
        perror("Falha ao alocar memória para o grafo");
        exit(EXIT_FAILURE);
    }
    g->adj = matrizInit(num_linhas_v, num_colunas_w, '.');
    g->e = 0;            // Mantendo como no original
    g->v = num_linhas_v; // g->v armazena o número de linhas
    return g;
}

Edge edge(int linha_v, int coluna_w)
{
    Edge e_obj = {linha_v, coluna_w};
    return e_obj;
}

// A função 'gota' original não é chamada na main, mas é funcional se necessária.
/*
void gota(Graph g, Edge e)
{
    int v_linha = e.v;
    int w_coluna = e.w;
    g->adj[v_linha][w_coluna] = 'o';
}
*/

void dfs(Graph g, Edge celulaAtual, int M_numColunas) // Nome 'dfs' mantido, lógica interna corrigida
{
    int r = celulaAtual.v; // linha atual (r para 'row')
    int c = celulaAtual.w; // coluna atual (c para 'column')

    // 1. Verifica se a célula está fora dos limites da matriz
    // g->v contém o número de linhas (N)
    if (r < 0 || r >= g->v || c < 0 || c >= M_numColunas)
    {
        return;
    }

    // 2. Verifica o conteúdo da célula atual
    // Se for uma prateleira '#', a água não pode ocupar este espaço.
    if (g->adj[r][c] == '#')
    {
        return;
    }
    // Se a célula já está molhada ('o'), esta chamada DFS específica não precisa
    // reprocessá-la. A propagação a partir dela já teria sido iniciada.
    if (g->adj[r][c] == 'o')
    {
        return;
    }

    // 3. Se chegou aqui, a célula é '.' (espaço vazio). Molha ela.
    g->adj[r][c] = 'o';

    // 4. Propaga a água a partir da célula (r,c) que acabou de ser molhada.

    // REGRA DE QUEDA VERTICAL:
    // A água sempre tenta cair para a célula diretamente abaixo.
    dfs(g, edge(r + 1, c), M_numColunas);

    // REGRA DE ESPALHAMENTO HORIZONTAL:
    // Se a água na célula (r,c) está sobre uma prateleira (ou seja, g->adj[r+1][c] == '#'),
    // então ela tenta escorrer para (r, c-1) e (r, c+1).
    // (Verifica também se r+1 está dentro dos limites antes de acessar g->adj[r+1][c])
    if (r + 1 < g->v && g->adj[r + 1][c] == '#')
    {
        dfs(g, edge(r, c - 1), M_numColunas); // Espalha para esquerda
        dfs(g, edge(r, c + 1), M_numColunas); // Espalha para direita
    }
}

int main()
{
    int N, M;
    if (scanf("%d %d", &N, &M) != 2)
    {
        fprintf(stderr, "Erro ao ler N e M.\n");
        return 1;
    }

    Graph g = graphInit(N, M);

    char *linhaBuffer = malloc(sizeof(char) * (M + 2)); // M chars + '\0' + margem

    for (int i = 0; i < N; i++)
    {
        scanf("%s", linhaBuffer);
        for (int j = 0; j < M; j++)
        {
            if (linhaBuffer[j] == '\0')
                break; // Segurança para strings menores que M
            g->adj[i][j] = linhaBuffer[j];
        }
    }

    int linhaComeco = 0;
    int colunaComeco = -1; // Inicializa como não encontrado

    // Encontra a coluna inicial da gota na primeira linha
    for (int j = 0; j < M; j++)
    { // CORRIGIDO: Iterar por M (colunas)
        if (g->adj[linhaComeco][j] == 'o')
        {
            colunaComeco = j;
            break;
        }
    }

    if (colunaComeco != -1)
    {
        // Para que a DFS processe corretamente a célula inicial (que já é 'o'),
        // mudamos temporariamente para '.' antes da primeira chamada.
        g->adj[linhaComeco][colunaComeco] = '.';
        dfs(g, edge(linhaComeco, colunaComeco), M);
    }

    // Imprime o resultado
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%c", g->adj[i][j]);
        }
        printf("\n");
    }

    // Liberar memória alocada
    free(linhaBuffer);
    for (int i = 0; i < g->v; i++)
    { // g->v contém N (número de linhas)
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);

    return 0;
}