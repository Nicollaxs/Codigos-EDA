#include <stdio.h>

typedef struct No{
    int item;
    struct No *proximo;
    struct No *anterior;
}No;

typedef struct {
    No *ultimo;
    int tamanho;
    No *proximo;
}Cabeca;


//Operações Basicas
Cabeca * criarLista(){
    Cabeca *lista = malloc(sizeof(Cabeca));

    lista->proximo= NULL;
    lista->ultimo= NULL;
    lista->tamanho= 0;

    return lista;
}

No * criarNo(int item){
    No *novo = malloc(sizeof(No));
    novo -> item = item;    
    novo ->anterior = NULL;    
    novo ->proximo = NULL;    

    return novo;
}

int vazia(Cabeca *lista){
    return (lista->proximo==NULL);
}

No * buscar(Cabeca *lista, int item){
    No *atual;

    for(atual = lista->proximo; atual && atual->item != item; atual = atual->proximo);

    if(atual)
        return atual;
    else
        printf("Elemento não encontrado !");    
}

void inserirNoInicio(Cabeca *lista, No *elem){

    elem->anterior = NULL;
    elem->proximo = lista->proximo;
    lista->proximo = elem;

    if(elem->proximo!=NULL)
        elem->proximo->anterior = elem;
    else
        lista->ultimo=elem;

    lista->tamanho++;
}

void inserirDepois(Cabeca *lista, No *ref, No *elem){

    elem->proximo = ref->proximo;
    elem->anterior = ref;
    ref->proximo = elem;

    if(elem->proximo!=NULL)
        elem->proximo->anterior = elem;
    else    
        lista->ultimo = elem;
    lista->tamanho++;
}

void inserirAntes(Cabeca *lista, No *ref, No* elem){

    elem->proximo = ref;
    elem->anterior = ref->anterior;
    ref->anterior = elem;

    if(elem->anterior!=NULL)
        elem->anterior->proximo = elem ;
    else
        lista->proximo= elem;


    lista->tamanho++;
}

void inserirNoFim(Cabeca *lista, No * elem){

    elem->anterior = lista->ultimo;
    elem->proximo = NULL;
    lista->ultimo = elem;

    if(elem->anterior!=NULL)
        elem->anterior->proximo = elem;
    else 
        lista->proximo = elem;

    lista->tamanho++;
}

void remover_no(Cabeca *lista, No *lixo){

    if(lista->proximo == lixo)
        lista->proximo = lixo->proximo;
    else
        lixo->anterior->proximo = lixo->proximo;


    if(lista->ultimo==lixo)
        lista->ultimo == lixo->anterior;
    else
        lixo->proximo->anterior = lixo->anterior;
    

    lista->tamanho--;

}

void imprimir(Cabeca *lista) {
    No *atual = lista->proximo; // Inicialize atual com o primeiro nó da lista
    while (atual != NULL) { // Use um loop while para iterar sobre a lista
        printf("%d ", atual->item); // Adicione um espaço para separar os valores
        atual = atual->proximo;
    }
    printf("\n"); // Adicione uma nova linha no final da impressão
}


int main (void){ 
    Cabeca *lista = criarLista();
    No *no = criarNo(2);
    No *no2 = criarNo(5);
    inserirNoInicio(lista,no);
    inserirDepois(lista,no,no2);

    imprimir(lista);
    return 0;
}