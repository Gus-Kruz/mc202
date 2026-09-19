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
    if (c == NULL) return;
    no_elemento* p = c->head;

    while(p != NULL) {
        no_elemento* aux = p;
        p = p->prox;
        free(aux);
    }

    c->head = NULL;
    c->tamanho = 0;
}

void adicionar_elemento(conjunto* c, int valor_novo_elemento) {
    no_elemento* novo_elemento = malloc(sizeof(no_elemento));
    if (novo_elemento == NULL) {
        return;
    }

    novo_elemento->valor_elemento = valor_novo_elemento;
    novo_elemento->prox = NULL;

    if (c->head == NULL) {
        c->head = novo_elemento;
        c->tamanho = 1;
        return;
    }

    no_elemento* p = c->head;

    // caso que insere no início

    if (p->valor_elemento > valor_novo_elemento) {
        c->head = novo_elemento;
        novo_elemento->prox = p;
        c->tamanho++;
        return;
    }

    // caso que o primeiro elemento é igual
    if (p->valor_elemento == valor_novo_elemento) {
        free(novo_elemento);
        return;
    }

    // percorre a lista até econtrar o final ou encontrar um número menor que ele

    while(p->valor_elemento < valor_novo_elemento) {
        no_elemento* p_anterior = p;
        // caso que chega no final da lista
        if (p->prox == NULL) {
            p->prox = novo_elemento;
            c->tamanho++;
            return;
        }
        p = p->prox;
        if (p->valor_elemento == valor_novo_elemento) {
            free(novo_elemento);
            return;
        } else if (p->valor_elemento > valor_novo_elemento) {
            p_anterior->prox = novo_elemento;
            novo_elemento->prox = p;
            c->tamanho++;
            return;
        }
    }
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

void imprimir_elementos(conjunto* c, int i_conjunto) {
    no_elemento* p = c->head;
    printf("C%d = {", i_conjunto);
    if (c->tamanho > 0) {
        if(c->tamanho > 1) {
            for (int i = 0; i < (c->tamanho)-1; i++) {
                printf("%d, ", p->valor_elemento);
                p = p->prox;
            }
        }
        printf("%d}\n", p->valor_elemento);
    } else {
        printf("}\n");
    }

}

void limpar_vetor(conjunto vetor_conjuntos[]) {
    for (int i = 0; i < 128; i++) {
        conjunto* c = &vetor_conjuntos[i];
        inicializar_conjunto(c);
    }
}

int main() {
    char comando;
    int i_conjunto, j_conjunto, k_conjunto;
    int n_elementos;
    int valor_elemento;

    conjunto vetor_conjuntos[128];

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
            case 'p':
                scanf(" %d", &i_conjunto);

                imprimir_elementos(&vetor_conjuntos[i_conjunto], i_conjunto);
                break;
            case 't':
                limpar_vetor(vetor_conjuntos);
                return 0;
        }
    }
}