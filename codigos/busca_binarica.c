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


int busca_binaria_recursiva(int *vet, int chave, int inicio, int fim){
    int meio;
    if(inicio <= fim){
        meio = (inicio + fim)/2;

        if(vet[meio] == chave)
            return meio; //retorna a posição se encontrou
       
        if(vet[meio] > chave)
            return busca_binaria_recursiva(vet,chave,inicio,meio - 1); //retorna o valor da chamada recursiva
            
        return busca_binaria_recursiva(vet,chave,meio + 1,fim); //retorna o valor da chamada recursiva
                
        }  
   
        return -1; //elemento não encontrado

    }

int main(){
    int array[13] = {13,14,19,43,47,52,65,82,89,91,108,133,139};

    int chave = 89, inicio = 0, fim = 12;
    if(busca_binaria_recursiva(array, chave, inicio, fim) >= 0)
        printf("Valor encontrado : %d \n", busca_binaria_recursiva(array, chave,inicio,fim));
    else
        printf("Valor nao encontrado\n");
}