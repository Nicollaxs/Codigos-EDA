#include <stdio.h>
#include <stdlib.h>

typedef int Key;
typedef struct {
    Key key;
    // outros campos, se necessário
} Item;

#define NULLitem (Item){0}
#define eq(A,B) ((A) == (B))
#define less(A,B) ((A) < (B))
#define key(A) ((A).key)

typedef struct STnode *link;

struct STnode {
    Item item;
    link *links;
    int sz;
};

static link head, z;
static int N, lgN;

// Prototipação das funções
Item search(link t, Key v, int k);
Item STsearch(Key v);
link new(Item item, int k);
void STinit(int max);
int randX(void);
void insertR(link t, link x, int k);
void STinsert(Item item);

// Função de busca
Item search(link t, Key v, int k) {
    Key tk = key(t->links[k]->item);

    if (eq(tk, v))
        return t->links[k]->item;

    if (t->links[k] == z) {
        if (k > 0)
            return search(t, v, k - 1);
        else
            return NULLitem;
    }
    if (less(v, tk))
        return search(t, v, k - 1);

    return search(t->links[k], v, k);
}

Item STsearch(Key v) {
    return search(head, v, lgN);
}

// Função para criar novo nó
link new(Item item, int k) {
    link x = malloc(sizeof(*x));
    x->item = item;
    x->links = malloc(k * sizeof(link));
    x->sz = k;

    for (int i = 0; i < k; i++)
        x->links[i] = z;

    return x;
}

// Inicialização da Skip List
void STinit(int max) {
    N = 0;
    lgN = 0;
    z = new(NULLitem, 0);
    head = new(NULLitem, max + 1);
}

// Função randômica para definir nível
int randX(void) {
    int i, j, t = rand();

    for (i = 1, j = 2; i < lgN; i++, j += j) {
        if (t > (RAND_MAX / j))
            break;
    }

    if (i > lgN)
        lgN = i;

    return i;
}

// Inserção recursiva
void insertR(link t, link x, int k) {
    Key v = key(x->item);

    if (less(v, key(t->links[k]->item))) {
        if (k < x->sz) {
            x->links[k] = t->links[k];
            t->links[k] = x;
        }

        if (k == 0)
            return;

        insertR(t, x, k - 1);
        return;
    }

    insertR(t->links[k], x, k);
}

// Inserção pública
void STinsert(Item item) {
    STinsertAux(item, randX());
}

void STinsertAux(Item item, int k) {
    insertR(head, new(item, k), lgN);
    N++;
}


int main() {
    STinit(10); // Inicializa a skip list para até 10 elementos

    Item a = {10};
    Item b = {20};
    Item c = {15};
    Item d = {25};

    STinsert(a);
    STinsert(b);
    STinsert(c);
    STinsert(d);

    printf("Procurando a chave 15...\n");
    Item result = STsearch(15);
    if (result.key != 0) {
        printf("Encontrado: %d\n", result.key);
    } else {
        printf("Item não encontrado.\n");
    }

    printf("Procurando a chave 30...\n");
    result = STsearch(30);
    if (result.key != 0) {
        printf("Encontrado: %d\n", result.key);
    } else {
        printf("Item não encontrado.\n");
    }

    return 0;
}
