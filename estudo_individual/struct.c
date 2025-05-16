#include <stdio.h>

typedef struct pessoa{
    int idade;
    float altura;
}Pessoa;

int main(){
    Pessoa p;
    p.idade = 5;
    p.altura = 1.65;

    printf("%d \n",p.idade);
    printf("%f",p.altura);

    return 0;
}