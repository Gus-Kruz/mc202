#include <stdlib.h>
typedef struct no{
    int valor;
    struct no* prox;
} no;

void remover_valor(no** cabeca, int x) {
    if (*cabeca == NULL) {
        return;
    }

    no** p = cabeca;

    while(*p != NULL) {
        if ((*p)->valor == x) {
            no* aux = *p;
            *p = (*p)->prox;
            free(aux);
        } else {
            p = &((*p)->prox);
        }
    }
}

void movenexttofront(no** cabeca, no* t) {
    no* alvo = t->prox;
    no* aux = alvo->prox;

    alvo->prox = *cabeca;

    *cabeca = alvo;

    t->prox = aux;

}

void remover_menor(no** cabeca) {
    no** p = cabeca;
    no* end_menor = *p;
    no* anterior;
    int menor = (*p)->valor;
    while((*p)->prox != NULL) {
        if((*p)->prox->valor < menor) {
            menor = (*p)->valor;
            end_menor = *p;
        }
        p = &((*p)->prox);
    }

}