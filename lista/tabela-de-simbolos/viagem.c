#include <stdio.h>
#include <stdlib.h>

typedef struct Rest{
    int cod;
    int nota;
    struct Rest *prox;
} Rest;

int dias = 3;

void insere(Rest **comeco, int cod, int nota){
    Rest *novo = (Rest*) malloc(sizeof(Rest));
    novo->cod = cod;
    novo->nota = nota;
    novo->prox = NULL;

    if(!*comeco){
        *comeco = novo;
        return;
    }

    Rest *aux = *comeco;
    while(aux->prox){
        aux = aux->prox;
    }

    aux->prox = novo;
}

void imprime(Rest *aux){
    while(aux){
        printf("%d %d \n", aux->cod, aux->nota);
        aux = aux->prox;
    }
}

int melhorRest(Rest *aux){

    int melhorNota = 0;
    int melhorCodigo = 0;
    while(aux){

        if(aux->nota == melhorNota){
            if(aux->cod < melhorCodigo){
                melhorNota = aux->nota;
                melhorCodigo = aux->cod;
            }
        }

        if(aux->nota > melhorNota){
            melhorNota = aux->nota;
            melhorCodigo = aux->cod;
        }
        aux = aux->prox;
    }
    return melhorCodigo;
}


int main(){

    int vetor[3];

    for(int i = 1; i <= dias ; i++){
        int valor;
        scanf("%d",&valor);
        Rest *comeco = NULL;

        while(valor >= 1){
            int cod, nota;
            scanf("%d %d",&cod,&nota);
            insere(&comeco,cod,nota);
            valor--;
        }
        
        vetor[i-1] = melhorRest(comeco); 
    }

    for (int i = 0; i < 3; i++){
        printf("Dia %d \n %d \n", i + 1, vetor[i]);
        printf("\n");
    }
    
    return 0;
}