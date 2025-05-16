#include <stdio.h>
#include <stdlib.h>


// fgets : "F" significa file. "Get" sginifica pegar. "S" string

int main(){

    char palavras[10] = {"Nicollas"};


    //Parametos necessarios
    // 1° - Onde vamos salvar o texto digitado
    // 2° - Quantidade maxima de caracterres que devem ser lidos
    // 3° - stdin


    //Lembrando que a função tem o delimitador então o tamanho do vetor então 
    // O tamanho do vetor vai ser N - 1.
    //(com o \n e o \0 no final.)

    printf("Digite o seu nome : \n");
    fgets(palavras, 10, stdin);
    printf("%s \n", palavras);


    return 0;
}