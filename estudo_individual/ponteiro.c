#include <stdio.h>

int main() {
    int a = 10;
    int* p = &a;     // p armazena o endereço de 'a'
    int** pp = &p;   // pp armazena o endereço de 'p' (correto!)

    // Usamos %p para endereços (ponteiros) e %d para inteiros
    printf("Endereço de a: %p \n", (void*)&a);
    printf("Valor de p (endereço de a): %p \n", (void*)p);
    printf("Valor de *p (conteúdo de a): %d \n\n", *p);

    printf("Endereço de p: %p \n", (void*)&p);
    printf("Valor de pp (endereço de p): %p \n", (void*)pp);
    printf("Valor de *pp (conteúdo de p, que é o endereço de a): %p \n", (void*)*pp);
    printf("Valor de **pp (conteúdo de a): %d \n", **pp);

    return 0;
}