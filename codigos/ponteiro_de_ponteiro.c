#include <stdio.h>

int main(void){

    int A = 100;
    int *B;
    int **C;

    B = &A;
    C = &B;

    printf("Endereco de A: %p\tConteudo de A: %d\n", &A,A);
    printf("Endereco de B: %p\tConteudo de B: %p\n", &B,B);
    printf("Conteudo apontado por B: %d\n", *B);
    printf("Endereco de C: %p\tConteudo de C: %p\n", &C,C);
    printf("Conteudo apontado por c: %d\n", **C);

return 0;
}