#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no_elemento {
    int valor_elemento;
    struct no_elemento* prox;
} no_elemento;

typedef struct conjunto {
    int tamanho;
    struct no_elemento* head;
} conjunto;

void inicializar_conjunto(conjunto* c) {
    while(c->head != NULL) {
        no_elemento* p = c->head;
        c->head = c->head->prox;
        free(p);
    }
    c->tamanho = 0;
    c->head = NULL;
}

void adicionar_elemento(conjunto* c, int valor_novo_elemento) {
    no_elemento* p = c->head;
    
    while(p != NULL) {
        if (p->valor_elemento == valor_novo_elemento) {
            return;
        }
        p = p->prox;
    }

    no_elemento* novo_elemento = malloc(sizeof(no_elemento));
    if (novo_elemento == NULL) {
        return;
    }

    novo_elemento->valor_elemento = valor_novo_elemento;
    novo_elemento->prox = NULL;

    if (c->head == NULL) {
        c->head = novo_elemento;
    } else {
        p = c->head;
        while (p->prox != NULL) {
            p = p->prox;
        }
        p->prox = novo_elemento;
    }

    c->tamanho++;
}

void remover_elemento(conjunto* c, int valor_elemento_rem) {
    if (c->head == NULL) {
        return;
    }
    no_elemento* p = c->head;
    if (p->valor_elemento == valor_elemento_rem){
        c->head = p->prox;
        free(p);
        c->tamanho--;
        return;
    } else {
        while (p->prox != NULL) {
            no_elemento * p_anterior = p;
            p = p->prox;
            if(p->valor_elemento == valor_elemento_rem) {
                p_anterior->prox = p->prox;
                free(p);
                c->tamanho--;
                return;
            }
        }
    }
}

void conjunto_uniao(conjunto* c_i, conjunto* c_j, conjunto* c_k) {
    conjunto temp = {0, NULL};

    no_elemento* p = c_j->head;
    while (p != NULL) {
        adicionar_elemento(&temp, p->valor_elemento);
        p = p->prox;
    }

    p = c_k->head;
    while (p != NULL) {
        adicionar_elemento(&temp, p->valor_elemento);
        p = p->prox;
    }

    inicializar_conjunto(c_i);
    c_i->head = temp.head;
    c_i->tamanho = temp.tamanho;
}

bool buscar_elemento(conjunto* c, int valor_buscado) {
    no_elemento* p = c->head;
    while (p != NULL) {
        if (p->valor_elemento == valor_buscado) {
            return true;
        }
        p = p->prox;
    }
    return false;
}

void conjunto_diferenca(conjunto*c_i, conjunto* c_j, conjunto* c_k) {
    conjunto temp = {0, NULL};

    no_elemento* p = c_j->head;
    while (p != NULL) {
        if (!buscar_elemento(c_k, p->valor_elemento)) {
            adicionar_elemento(&temp, p->valor_elemento);
        }
        p = p->prox;
    }

    inicializar_conjunto(c_i);
    c_i->head = temp.head;
    c_i->tamanho = temp.tamanho;
}

void conjunto_intersecao(conjunto* c_i, conjunto* c_j, conjunto* c_k) {
    conjunto temp = {0, NULL};

    no_elemento* p = c_j->head;
    while (p != NULL) {
        if (buscar_elemento(c_k, p->valor_elemento)) {
            adicionar_elemento(&temp, p->valor_elemento);
        }
        p = p->prox;
    }

    inicializar_conjunto(c_i);
    c_i->head = temp.head;
    c_i->tamanho = temp.tamanho;
}

void limpar_vetor(conjunto vetor_conjuntos[]) {
    for (int i = 0; i < 128; i++) {
        conjunto c = vetor_conjuntos[i];
        while(c.head != NULL) {
            no_elemento* p = c.head;
            c.head = c.head->prox;
            free(p);
        }
    }
    free(vetor_conjuntos);
}

int main() {
    char comando;
    int i_conjunto;
    int j_conjunto;
    int k_conjunto;
    int n_elementos;
    int valor_elemento;

    conjunto* vetor_conjuntos = malloc(128 * sizeof(conjunto));

    for (int i = 0; i < 128; i++) {
        vetor_conjuntos[i].tamanho = 0;
        vetor_conjuntos[i].head = NULL;
    }

    while (scanf(" %c", &comando) == 1) {
        switch (comando) {
            case 'c':
                scanf(" %d", &i_conjunto);
                inicializar_conjunto(&vetor_conjuntos[i_conjunto]);
                break;
            case 'i':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &n_elementos);

                for (int i = 0; i < n_elementos; i++) {
                    scanf(" %d", &valor_elemento);
                    adicionar_elemento(&vetor_conjuntos[i_conjunto], valor_elemento);
                }
                break;
            case 'r':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &n_elementos);

                for (int i = 0; i < n_elementos; i++) {
                    scanf(" %d", &valor_elemento);
                    remover_elemento(&vetor_conjuntos[i_conjunto], valor_elemento);
                }
                break;
            case 'u':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &j_conjunto);
                scanf(" %d", &k_conjunto);

                conjunto_uniao(&vetor_conjuntos[i_conjunto], &vetor_conjuntos[j_conjunto], &vetor_conjuntos[k_conjunto]);
                break;
            case 'n':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &j_conjunto);
                scanf(" %d", &k_conjunto);

                conjunto_intersecao(&vetor_conjuntos[i_conjunto], &vetor_conjuntos[j_conjunto], &vetor_conjuntos[k_conjunto]);
                break;
            case 'm':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &j_conjunto);
                scanf(" %d", &k_conjunto);

                conjunto_diferenca(&vetor_conjuntos[i_conjunto], &vetor_conjuntos[j_conjunto], &vetor_conjuntos[k_conjunto]);
                break;
            case 'e':
                scanf(" %d", &i_conjunto);
                scanf(" %d", &valor_elemento);
                
                if(buscar_elemento(&vetor_conjuntos[i_conjunto], valor_elemento)) {
                    printf("%d esta em C%d\n", valor_elemento, i_conjunto);
                } else {
                    printf("%d nao esta em C%d\n", valor_elemento, i_conjunto);
                }
                break;
            case 't':
                limpar_vetor(vetor_conjuntos);
                return 0;
        }
    }
}