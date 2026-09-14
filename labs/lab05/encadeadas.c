#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_elemento {
    int valor_elemento;
    struct no_elemento* prox;
} no_elemento;

typedef struct conjunto {
    bool inicializado;
    int tamanho;
    struct no_elemento* head;
} conjunto;

void adicionar_elemento(conjunto* conjunto, int valor_novo_elemento) {
    no_elemento* novo_elemento = malloc(sizeof(no_elemento));
    novo_elemento->valor_elemento = valor_novo_elemento;

    if (conjunto->head == NULL) {
        novo_elemento->prox = conjunto->head;
        conjunto->head = novo_elemento;
    } else {
        no_elemento* p = conjunto->head;
        while(p->prox != NULL) {
            if(p->valor_elemento == valor_novo_elemento) {
                //free(novo_elemento);
                return;
            } else {
                p = p->prox;
            }
        }
        if(p->valor_elemento == valor_novo_elemento) {
            //free(novo_elemento);
            return;
        } else {
            novo_elemento->prox = NULL;
            p->prox = novo_elemento;
        }
    }
}

void remover_elemento(conjunto* conjunto, int valor_elemento_rem) {
    no_elemento* p = conjunto->head;

    if (conjunto->head->valor_elemento == valor_elemento_rem) {
        conjunto->head = p->prox;
        free(p);
        return;
    } else {
        no_elemento* p_anterior = conjunto->head;
        no_elemento* p = p_anterior->prox;
        while(p->prox != NULL) {
            if(p->valor_elemento == valor_elemento_rem) {
                p_anterior->prox = p->prox;
                free(p);
                return;
            }
            p_anterior = p_anterior->prox;
            p = p->prox;
        }
    
        if (p->valor_elemento == valor_elemento_rem) {
            p_anterior->prox = NULL;
            free(p);
        }
    }
}

int main() {
    char comando;
    int i_conjunto;
    int j_conjunto;
    int k_conjunto;
    int n_elementos;
    int valor_elemento;
    conjunto** vetor_conjuntos = malloc(129 * sizeof(conjunto*));
    for (int i = 1; i < 129; i++) {
        vetor_conjuntos[i]->inicializado = false;
        vetor_conjuntos[i]->tamanho = 0;
        vetor_conjuntos[i]->head = NULL;
    }

    while (scanf(" %c", &comando) == 1) {

        switch (comando) {
            case 'c':
                scanf(" %d", &i_conjunto);
                inicializar_conjunto(vetor_conjuntos, i_conjunto);

                break;
            case 'i':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &n_elementos);

                for (int i = 0; i < n_elementos; i++) {
                    scanf("%d", &valor_elemento);
                }

                vetor_conjuntos[i_conjunto]->tamanho += n_elementos;

                break;
            case 'r':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &n_elementos);
                
                for(int i = 0; i < n_elementos; i++) {
                    scanf("%d", &valor_elemento);
                    remover_elemento(vetor_conjuntos[i_conjunto], valor_elemento);
                }
                
                vetor_conjuntos[i_conjunto]->tamanho -= n_elementos;
                
                break;

            case 'u':
                scanf(" %d", &j_conjunto);
                scanf(" %d", &k_conjunto);

        }

    }
    if (vetor_conjuntos[1]->head == NULL) {
        printf("tá inicializando!");
    }
}