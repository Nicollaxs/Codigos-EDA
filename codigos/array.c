#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main(){

    int vet[10];

    srand(time(NULL));

    for(int i = 0; i < 10; i++){
        vet[i] = rand() % 100; //Isso garante que o resultado vai ser entre 0 e 99.
    }

    printf("\n\n");

    for(int n = 0; n < 10;n++)
        printf("%d ",vet[n]);

    printf("\n\n");
    
    return 0;
}