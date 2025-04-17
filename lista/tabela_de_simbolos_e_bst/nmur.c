#include <stdio.h>
#include <stdlib.h>

// Definição das cores para os nós da árvore Red-Black
#define RED 1
#define BLACK 0

// Tamanho máximo do vetor de suporte
#define MAX 300000

// Definindo o tipo link como ponteiro para STnode
typedef struct STnode* link;

// z será o nó nulo (folha), h é a raiz da árvore
link z, h;

// Estrutura de um nó da árvore Red-Black
typedef struct STnode {
    int chave;    // Valor armazenado no nó
    link l, r;    // Ponteiros para filho esquerdo e direito
    int n;        // Número de nós na subárvore enraizada neste nó
    int cor;      // Cor do nó (RED ou BLACK)
} STnode;

// Cria um novo nó com a chave especificada
link new(int chave) {
    link x = malloc(sizeof(STnode));
    x->chave = chave;
    x->l = x->r = z; // Aponta filhos para o nó nulo
    x->n = 1;
    x->cor = RED;    // Todo novo nó é vermelho inicialmente
    return x;
}

// Verifica se o nó é vermelho
int isRed(link x) {
    if (x == z) return 0;
    return x->cor == RED;
}

// Rotaciona a subárvore para a esquerda
link rotacionaEsq(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->cor = h->cor;
    h->cor = RED;
    x->n = h->n;
    h->n = h->l->n + h->r->n + 1;
    return x;
}

// Rotaciona a subárvore para a direita
link rotacionaDir(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->cor = h->cor;
    h->cor = RED;
    x->n = h->n;
    h->n = h->l->n + h->r->n + 1;
    return x;
}

// Inverte as cores de um nó e seus filhos
link flipColor(link h) {
    h->cor = RED;
    h->l->cor = BLACK;
    h->r->cor = BLACK;
    return h;
}

// Busca uma chave na árvore (retorna 1 se existe, 0 se não)
int busca(link h, int chave) {
    if (h == z) return 0;
    if (chave < h->chave) return busca(h->l, chave);
    if (chave > h->chave) return busca(h->r, chave);
    return 1;
}

// Insere uma chave na árvore Red-Black
link insert(link h, int chave) {
    if (h == z) return new(chave);

    if (chave < h->chave)
        h->l = insert(h->l, chave);
    else if (chave > h->chave)
        h->r = insert(h->r, chave);

    // Correções da árvore Red-Black
    if (isRed(h->r) && !isRed(h->l)) h = rotacionaEsq(h);
    if (isRed(h->l) && isRed(h->l->l)) h = rotacionaDir(h);
    if (isRed(h->l) && isRed(h->r)) h = flipColor(h);

    // Atualiza o tamanho da subárvore
    h->n = h->l->n + h->r->n + 1;
    return h;
}

// Percorre a árvore em ordem (in-order) e preenche o vetor
void arvoreParaVetor(link h, int *vetor, int *idx) {
    if (h == z) return;
    arvoreParaVetor(h->l, vetor, idx);
    vetor[(*idx)++] = h->chave;
    arvoreParaVetor(h->r, vetor, idx);
}

int main() {
    // Inicializa o nó nulo z
    z = malloc(sizeof(STnode));
    z->l = z->r = z;
    z->cor = BLACK;
    z->n = 0;
    
    // A árvore começa vazia (apontando para z)
    h = z;

    int n;
    scanf("%d", &n);  // Lê a quantidade de valores a serem inseridos

    // Insere os valores na árvore, ignorando duplicados
    int valor;
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        if (!busca(h, valor)) h = insert(h, valor);
    }

    // Converte a árvore em vetor ordenado
    int vetor[MAX], tam = 0;
    arvoreParaVetor(h, vetor, &tam);

    // Se o número de elementos for ímpar, insere o valor 1 bilhão
    if (tam % 2 != 0) {
        if (!busca(h, 1000000000)) {
            h = insert(h, 1000000000);
            vetor[tam++] = 1000000000;
        }
    }

    // Para cada par de elementos consecutivos, soma e insere a soma na árvore
    for (int i = 0; i < tam; i += 2) {
        int soma = vetor[i] + vetor[i + 1];
        if (!busca(h, soma)) h = insert(h, soma);
    }

    // Atualiza vetor com os novos elementos inseridos
    tam = 0;
    arvoreParaVetor(h, vetor, &tam);

    // Imprime os elementos dos índices 0, 4, 8, ...
    for (int i = 0; i < tam; i += 4)
        printf("%d\n", vetor[i]);

    // Imprime o total de elementos únicos na árvore
    printf("Elementos : %d\n", h->n);

    return 0;
}
