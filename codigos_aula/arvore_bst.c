#include <stdio.h>
#include <stdlib.h>

// Definindo tipo Item e funções auxiliares (exemplo com int)
typedef int Item;

#define nullItem -1

int key(Item item) {
    return item; // Se o item for só um int, a chave é o próprio valor
}

int less(int a, int b) {
    return a < b;
}

// Estrutura e typedef
typedef struct STNode* link;

struct STNode {
    Item item;
    link l, r;
    int n;
};

link h, z;

// Cria novo nó
link new(Item item, link l, link r, int n) {
    link x = malloc(sizeof(*x));
    x->item = item;
    x->l = l;
    x->r = r;
    x->n = n;
    return x;
}

// Inicializa BST
void STinit() {
    z = new(nullItem, NULL, NULL, 0); // nó nulo
    h = z;
}

// Conta elementos
int STcount() {
    return h->n;
}

// Percurso em ordem (in-order)
void sortR(link r, void (*visit)(Item)) {
    if (r == z) return;
    sortR(r->l, visit);
    visit(r->item);
    sortR(r->r, visit);
}

// Rotação à direita
link rotacionaDireita(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

// Rotação à esquerda
link rotacionaEsquerda(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

// Inserção recursiva
link insertT(link h, Item item) {
    if (h == z)
        return new(item, z, z, 1);

    int k = key(item);
    int t = key(h->item);

    if (less(k, t)) {
        h->l = insertT(h->l, item);
        // Ex: h = rotacionaDireita(h); // depende do balanceamento desejado
    } else {
        h->r = insertT(h->r, item);
        // Ex: h = rotacionaEsquerda(h); // depende do balanceamento desejado
    }

    // Atualiza o tamanho da subárvore
    h->n = h->l->n + h->r->n + 1;

    return h;
}

// Inserção pública
void STinsert(Item item) {
    h = insertT(h, item);
}

// Busca recursiva
Item searchR(link h, int k) {
    if (h == z) return nullItem;

    int t = key(h->item);
    if (k == t) return h->item;
    if (less(k, t)) return searchR(h->l, k);
    else return searchR(h->r, k);
}

// Busca pública
Item STsearch(int k) {
    return searchR(h, k);
}
