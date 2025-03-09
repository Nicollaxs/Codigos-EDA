#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int array[],int tamanho, int valor){
    int inicio = 0;
    int fim = tamanho - 1;
    int meio = (inicio + fim)/2;

    while(inicio <= fim){
        if(array[meio] == valor)
            return meio;
        if(array[meio] < valor){
            inicio = meio + 1;
            meio = (inicio + fim)/2;
        } else {
            fim = meio - 1 ;
            meio = (inicio + fim)/2;
        }
    }

    return -1;

}

int main(){
    int array[13] = {13,14,19,43,47,52,65,82,89,91,108,133,139};

    int valor = 0;

    if(busca_binaria(array, 13, valor) >= 0)
        printf("Valor encontrado : %d \n", busca_binaria(array, 13, valor));
    else
        printf("Valor nao encontrado\n");
}