#include <stdio.h>

int main(){

    char nome[] = {"Nicollas"};

    printf("Valores ASCII da String: \"%s\"\n", nome);

    for(int i = 0; nome[i] != '\0'; i++){
        printf("'%c' ->  %d\n",nome[i], nome[i]);
    }

    return 0;
}