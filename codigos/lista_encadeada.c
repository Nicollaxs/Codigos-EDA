#include <stdio.h>

typedef struct no{
    int valor;
    struct no *proximo;
} No;

//procedimento para inserir no inicio

void inserir_no_inicio(No **lista, int num){
    No *novo = malloc(sizeof(No)); // Alocar memoria na heap

    if(novo){   // verificar se foi alocado
        novo->valor = num;  // Atribuir valor do novo nó
        novo->proximo = *lista; // inserir no começo da lista pois o *lista vai te dar o endereço do começo
        *lista = novo; // agora o começo da lista será o "novo"
    } 
    else 
        printf("Erro ao alocar memoria ! \n");
}

//procedimento para inserir no fim

void inserir_no_fim(No **lista, int num){
    No *aux, *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = num;
        novo->proximo = NULL;

        //é o primeiro ?

        if(*lista==NULL)
            *lista = novo;
        else{
            aux = *lista;
            while(aux->proximo);
                aux = aux->proximo;
            aux->proximo = novo;
        }

    }
    else
    printf("Erro ao alocar memoria !");
}

void inserir_no_meio(No **lista, int num, int ant){

    
}

int main(void){

    return 0;
}