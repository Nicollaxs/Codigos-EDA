#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particiona(int *vet, int inicio, int fim){
    int pivo = vet[fim];  // Escolhe o último elemento como pivô
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (vet[j] <= pivo) {
            i++;
            swap(&vet[i], &vet[j]); //caso entre aqui é feita uma troca com os mesmo indices
        }
    }
    swap(&vet[i + 1], &vet[fim]);
    return i + 1;
}

void quickSort(int *vetor, int inicio, int fim){
    if (inicio < fim) {
        int pos = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pos - 1);
        quickSort(vetor, pos + 1, fim);
    }
}

void imprimir(int *v, int tam) {
    for (int i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int main(){
    int vet[] = {1, 8, 16, 4, 9, 37};
    int tamanho = sizeof(vet) / sizeof(vet[0]);

    printf("Vetor antes da ordenacao: \n");
    imprimir(vet, tamanho);

    quickSort(vet, 0, tamanho - 1);

    printf("Vetor depois da ordenacao: \n");
    imprimir(vet, tamanho);

    return 0;
}
