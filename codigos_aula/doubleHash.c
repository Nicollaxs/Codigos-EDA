#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Item {
    int chave;
} Item;

// Macros
#define eq(A,B) ((A) == (B))
#define null(A) ((A.chave == Nullitem.chave))
#define hash(v,M) ((v) % (M))
#define hashtwo(v,M) ((v) * 97 + 1) // Evita 0
#define key(A) ((A).chave)

// Globais
Item Nullitem = {-1};
int M;
Item *ht;
int maxCol = 10; // Máximo de colisões

// Inicializa para evitar erros pois o grow precisa do insert e virse-versa
void grow();
bool insert(Item item);

// Inicializa a tabela hash
void init(int max) {
    M = max;
    ht = malloc(sizeof(Item) * M);
    for (int i = 0; i < M; i++)
        ht[i] = Nullitem;
}

// Aumenta o tamanho da tabela
void grow() {
    Item *t = ht;
    int oldM = M;

    M = M * 2;
    ht = malloc(sizeof(Item) * M);

    for (int i = 0; i < M; i++)
        ht[i] = Nullitem;

    for (int i = 0; i < oldM; i++) {
        if (!null(t[i])) {
            insert(t[i]);
        }
    }

    free(t);
}

// Inserção com hashing duplo
bool insert(Item item) {
    int i = hash(key(item), M);
    int h = hashtwo(key(item), M);
    int c = maxCol;

    while (c && !null(ht[i])) {
        i = (i + h) % M;
        c--;
    }

    if (!c) {
        grow();
        return insert(item);
    }

    ht[i] = item;
    return true;
}

int grau(int chave){
    int i = hash(chave, M);
    int h = hashtwo(chave, M);

    int c = maxCol;
    int qtd = 0;

    // Primeira tentativa não é colisão
    if (!null(ht[i]) && key(ht[i]) != chave) {
        qtd++;
        i = (i + h) % M;
        c--;
    } else {
        return 0; // encontrou de primeira ou posição livre
    }

    while (c && !null(ht[i]) && key(ht[i]) != chave) {
        qtd++;
        i = (i + h) % M;
        c--;
    }

    return qtd;

// Busca com hashing duplo
Item search(int chave) {
    int i = hash(chave, M);
    int h = hashtwo(chave, M);
    int c = maxCol;

    while (c && !null(ht[i])) {
        if (eq(key(ht[i]), chave))
            return ht[i];
        i = (i + h) % M;
        c--;
    }

    return Nullitem;
}

// Programa principal
int main() {
    init(5);

    Item a = {10}, b = {15}, c = {20}, d = {25};

    insert(a);
    insert(b);
    insert(c);
    insert(d);

    Item res = search(15);
    if (!null(res)) {
        printf("Item encontrado: %d\n", res.chave);
    } else {
        printf("Item não encontrado.\n");
    }

    return 0;
}
