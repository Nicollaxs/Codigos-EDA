#include <stdio.h>
#include <stdlib.h>

#define hash(v,m) ((16161 * (unsigned)v % m))

typedef struct Item {
    int chave; //valor ASCII do caractere
    int freq; //frequência
} Item;

Item NULLitem = {-1,-1};

#define key(x) (x.chave)
#define less(a,b) (key(a) < key(b))
#define null(A) (key(A) == key(NULLitem))
#define eq(a,b) ((a == b))

static int M, N;
static Item *ht;

void HTinit(int max){
    M = max;

    ht = malloc(sizeof(Item) * M);

    for(int i = 0; i < M; i++){
        ht[i] = NULLitem;
    }
}

void HTinsert(Item item){
    int v = key(item);
    int i = hash(v, M);

    while(!null(ht[i])){
        if(eq(v, key(ht[i]))){
            ht[i].freq += item.freq;// Se já existe, só soma a frequência
            return;
        }

        i = (i + 1) % M;
    }

    ht[i] = item;
    N++;
}

Item HTsearh(int v){
    int i = hash(v,M);

    while(!null(ht[i])){
        if(eq(key(ht[i]),v)){
            return ht[i];
        }

        i = (i + 1) % M;
    }

    return NULLitem;
}

// Função para ordenar os itens para saída
int compare(const void *a, const void *b) {
    Item *ia = (Item *)a;
    Item *ib = (Item *)b;
    
    if (ia->freq != ib->freq)
        return ia->freq - ib->freq; // frequência crescente
    else
        return ia->chave - ib->chave; // ASCII crescente
}


int main(){

    char letras[1005];
    int frist =1;

    while(fgets(letras, sizeof(letras), stdin)){
        HTinit(300);

        int i = 0;

        while(letras[i] != '\0' && letras[i] != '\n'){
            int c = (int) letras[i];
            Item novo = {c,1};
            HTinsert(novo);
            i++;
        }

        Item items[N];
        int count = 0;
        for(int i = 0; i < M; i++){
            if(!null(ht[i])){
                items[count++] = ht[i];
            }
        }

        qsort(items, count, sizeof(Item), compare);

        if(!frist)
            printf("\n");
        frist = 0;

        
        for(int i = 0; i < count; i++){
            printf("%d %d\n",items[i].chave,items[i].freq);
        }

        free(ht);
    }


    return 0;
}
