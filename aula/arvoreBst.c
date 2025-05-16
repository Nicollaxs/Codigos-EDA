#include <stdio.h>
#include <stdlib.h>

typedef struct STnode* link;

struct STnode {
    link l;
    link r;
    int item;
    int n;
};

#define NULLITEM -1

link h, z;

link new(link l, link r, int item, int n) {
    link x = malloc(sizeof(*x));
    x->l = l;
    x->r = r;
    x->item = item;
    x->n = n;
    return x;
}

void STinit() {
    z = new(NULL, NULL, NULLITEM, 0);
    h = z;
}

int stcount() {
    return h->n;
}

void sortR(link n) {
    if (n == z) return;
    sortR(n->l);
    printf("%d ", n->item);
    sortR(n->r);
}

link insertT(link h, int item) {
    if (h == z)
        return new(z, z, item, 1);

    if (item < h->item)
        h->l = insertT(h->l, item);
    else
        h->r = insertT(h->r, item);

    h->n = h->l->n + h->r->n + 1;
    return h;
}

void STinsert(int item) {
    h = insertT(h, item);
}

int search(link h, int item) {
    if (h == z) return NULLITEM;
    if (h->item == item)
        return item;
    if (item < h->item)
        return search(h->l, item);
    else
        return search(h->r, item);
}

// EXEMPLO DE USO:
int main() {
    STinit();
    STinsert(10);
    STinsert(5);
    STinsert(15);
    STinsert(3);
    STinsert(7);

    sortR(h); // Vai imprimir: 3 5 7 10 15
    return 0;
}
