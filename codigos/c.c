#include <stdio.h>

void troca(int *t, int *p)
{
    int v = *t;
    *t = *p;
    *p = v;
}

int main(void)
{
    int t = 3;
    int p = 5;

    troca(&t, &p);

    printf(" Valor de t = %d\n Valor de p = %d \n ", t, p);

    return 0;
}   