#include <stdio.h>

int main() {
    int a, soma = 0, valor; 

    scanf("%d", &a);

    while (a > 0) { 
        scanf("%d", &valor);
        soma += valor;
        a--;
    }

    printf("%d\n", soma);

    return 0;
}
