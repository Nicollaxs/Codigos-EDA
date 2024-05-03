#include <stdio.h>
#include <stdlib.h>

/*
    Alocação dinamica de memoria com a função malloc.
    Retorna um ponteiro para a região de memoria alocada ou Null.
*/

int main(void)
{

    int *x;

    x = malloc(sizeof(int));

    if (x)
    {
        printf("Sucesso ao alocar memoria \n");
        printf("x : %d\n", *x);
        *x = 50;
        printf("x : %d\n", *x);
    }
    else
    {
        printf("Erro ao alocar memoria \n");
    }
    return 0;
}