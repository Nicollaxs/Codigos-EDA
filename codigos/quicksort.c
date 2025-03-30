#include <stdio.h>
#include <stdlib.h>


int particiona(int *vet, int inicio, int fim){
    int pivo = (vet[inicio] + vet[fim] + (vet[(inicio + fim)/2])) / 3;
    
    while(inicio < fim){

       while(inicio < fim && vet[inicio] <= pivo){
        inicio = inicio + 1;
       }

       while(inicio < fim && vet[fim] > pivo){
        fim = fim - 1;
       }

       int aux = vet[inicio];
       vet[inicio] = vet[fim];
       vet[fim] = aux;
    }

    return inicio;
}

void quickSort(int *vetor, int inicio, int fim){
    if(inicio < fim){
        int pos = particiona(vetor, inicio, fim);
        quickSort(vetor,inicio,pos - 1);
        quickSort(vetor, pos, fim);
    }
}

int imprimir (int *v,int tam){
    
    for(int i = 0; i < tam; i++)
        printf("%d,", v[i]);
    printf("\n");
    
}

int main(){
    int vet[] = {47,35,12,49,56,25,71,83,5,3,1,70,99,10,61}; //tamanho 15

    imprimir(vet,15);
    quickSort(vet,0,14);
    imprimir(vet,15);
    return 0;
}


