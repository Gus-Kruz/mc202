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
    no** menor_p = p;
    int menor = (*p)->valor;
    while((*p) != NULL) {
        if((*p)->valor < menor) {
            menor = (*p)->valor;
            menor_p = p;
        }
        p = &((*p)->prox);
    }
    no* aux = *menor_p;
    *menor_p = (*menor_p)->prox;
    free(aux);
}

no* copiar_lista(no* cabeca_orig) {
    if (cabeca_orig == NULL) {
        return NULL;
    }
    no* cabeca_copia = malloc(sizeof(no));
    cabeca_copia->valor = cabeca_orig->valor;
    cabeca_copia->prox = NULL;

    no* atual_orig = cabeca_orig->prox;
    no* atual_copia = cabeca_copia;

    while(atual_orig != NULL) {
        atual_copia->prox = malloc(sizeof(no));
        atual_copia = atual_copia->prox;

        atual_copia->valor = atual_orig->valor;
        atual_copia->prox = NULL;

        atual_orig = atual_orig->prox;
    }

    return cabeca_copia;
}