#include <stdio.h>
#include <stdlib.h>


int main(){
    int *x;

    x = malloc(sizeof(int));

    if(x){
        printf("Alocou memoria");
        printf("x: %d \n",*x);
        *x = 50;
        printf("x: %d \n",*x);
    }
    else
        printf("Não alocou memoria");
    return 0;
}