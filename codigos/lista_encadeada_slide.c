#include <stdio.h>

typedef struct No
{
    int valor;
    struct No *proximo;
} No;

typedef struct
{
    int tamanho;
    No *ultimo;
    No *proximo;
} Cabeca;

Cabeca *criarLista()
{
    Cabeca *cabeca = malloc(sizeof(Cabeca));

    cabeca->ultimo = NULL;
    cabeca->proximo = NULL;
    cabeca->tamanho = 0;

    return cabeca;
}

No *criarNo(int valor)
{
    No *novo = malloc(sizeof(No));

    novo->valor = valor;
    novo->proximo = NULL;

    return novo;
}

int vazia(Cabeca *lista)
{
    return (lista->proximo == NULL);
}

void inserirNoInicio(Cabeca *cabeca, No *elem)
{
    elem->proximo = cabeca->proximo;
    cabeca->proximo = elem;

    cabeca->tamanho++;

    if (elem->proximo == NULL)
        cabeca->ultimo = elem;
}

void inserirDepois(Cabeca *cabeca, No *ref, No *elem)
{

    elem->proximo = ref->proximo;
    ref->proximo = elem;

    cabeca->tamanho++;
    if (elem->proximo == NULL)
        cabeca->ultimo = elem;
}

void inserirNoFim(Cabeca *cabeca, No *elem)
{
    // Tem que ter um if caso a lista for vazia. Não fiz o metodo.
    // caso não seja vazia :
    cabeca->ultimo->proximo = elem;
    cabeca->ultimo = elem;
    elem->proximo = NULL;

    cabeca->tamanho++;
}

void removerInicio(Cabeca *cabeca)
{

    if (vazia(cabeca))
        return;

    No *lixo = cabeca->proximo;
    cabeca->proximo = lixo->proximo;
    if (vazia(cabeca))
        cabeca->ultimo = NULL;

    // Duvida, eu não precisaria dar o free(lixo) ?
}

void removerNo(Cabeca *cabeca, No *lixo)
{
    if (cabeca->proximo == lixo)
        cabeca->proximo = lixo->proximo;

    No *ant;

    for (cabeca->proximo = ant; ant != NULL && ant->proximo != lixo; ant = ant->proximo)
        ;

    if (ant)
    {
        ant->proximo = lixo->proximo;
        cabeca->tamanho--;
    }

    if (ant->proximo == NULL)
        cabeca->ultimo = ant;
}

int numeroDeCelulas(No *atual, int quantidade)
{

    if (!atual)
        return quantidade;
    else
    {
        atual = atual->proximo;
        quantidade++;
        return (numeroDeCelulas(atual, quantidade));
    }
}

void concatenar(Cabeca *primeira, Cabeca *segunda, No *atual)
{

    if (!atual)
        return;
    else
    {
        primeira->ultimo->proximo = atual;
        primeira->ultimo = atual;
        concatenar(primeira, segunda, atual->proximo);
    }
}

void inserirAposKesima(Cabeca *lista, No *atual, No *novo, int conteudo, int contador, int k)
{

    if (contador == k)
    {
        novo->valor = conteudo;
        inserirDepois(lista, atual, novo);
        printf("Inserido\n");
        return;
    }
    else
        inserirAposKesima(lista, atual->proximo, novo, conteudo, contador+1, k);
}

void trocarCelula(){
    //
}

void imprimir(Cabeca *lista)
{
    No *atual = lista->proximo;
    printf("Lista : ");
    while (atual)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(void)
{
    Cabeca *lista = criarLista();
    No *no = criarNo(2);
    No *no2 = criarNo(4);
    No *no3 = criarNo(3);
    No *no4 = criarNo(5);

    No *no5 = criarNo(NULL);

    inserirNoInicio(lista, no);
    inserirNoInicio(lista, no2);
    inserirNoInicio(lista, no3);
    inserirNoInicio(lista, no4);
   

    inserirAposKesima(lista, lista->proximo, no5, 9, 1, 3);

    imprimir(lista);

    return 0;
}