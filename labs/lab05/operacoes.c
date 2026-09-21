#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "operacoes.h"

void inicializar_conjunto(conjunto* c) {
    if (c == NULL) return;
    no_elemento* p = c->head;

    while(p != NULL) {
        no_elemento* aux = p;
        p = p->prox;
        free(aux);
    }
    free(p);
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
            no_elemento* p_anterior = p;
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
    no_elemento* tail = NULL;

    no_elemento* p_j = c_j->head;
    no_elemento* p_k = c_k->head;

    while (p_j != NULL && p_k != NULL) {
        if(p_j->valor_elemento < p_k->valor_elemento) {
            no_elemento* novo_elemento = malloc(sizeof(no_elemento));
            if (novo_elemento != NULL) {
                novo_elemento->valor_elemento = p_j->valor_elemento;
                novo_elemento->prox = NULL;
            
                if (temp.head == NULL) {
                    temp.head = novo_elemento;
                } else {
                    tail->prox = novo_elemento;
                }
                tail = novo_elemento;
                temp.tamanho++;
            }
            p_j = p_j->prox;
        }
        else if (p_j->valor_elemento > p_k->valor_elemento) {
            no_elemento* novo_elemento = malloc(sizeof(no_elemento));
            if (novo_elemento != NULL) {
                novo_elemento->valor_elemento = p_k->valor_elemento;
                novo_elemento->prox = NULL;

                if (temp.head == NULL) {
                    temp.head = novo_elemento;
                } else {
                    tail->prox = novo_elemento;
                }
                tail = novo_elemento;
                temp.tamanho++;
            }

            p_k = p_k->prox;
        }
        else {
            no_elemento* novo_elemento = malloc(sizeof(no_elemento));
            if (novo_elemento != NULL) {
                novo_elemento->valor_elemento = p_j->valor_elemento;
                novo_elemento->prox = NULL;

                if (temp.head == NULL) {
                    temp.head = novo_elemento;
                } else {
                    tail->prox = novo_elemento;
                }
                tail = novo_elemento;
                temp.tamanho++;
            }
            p_j = p_j->prox;
            p_k = p_k->prox;
        }
        
    }
    
    while (p_k != NULL) {
        no_elemento* novo_elemento = malloc(sizeof(no_elemento));
        if (novo_elemento != NULL) {
            novo_elemento->valor_elemento = p_k->valor_elemento;
            novo_elemento->prox = NULL;

            if (temp.head == NULL) temp.head = novo_elemento;
            else tail->prox = novo_elemento;
            
            tail = novo_elemento;
            temp.tamanho++;
        }
        p_k = p_k->prox;
    }

    while (p_j != NULL) {
        no_elemento* novo_elemento = malloc(sizeof(no_elemento));
        if (novo_elemento != NULL) {
            novo_elemento->valor_elemento = p_j->valor_elemento;
            novo_elemento->prox = NULL;

            if (temp.head == NULL) temp.head = novo_elemento;
            else tail->prox = novo_elemento;
            
            tail = novo_elemento;
            temp.tamanho++;
        }
        p_j = p_j->prox;
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
    no_elemento* tail = NULL;

    no_elemento* p_j = c_j->head;
    no_elemento* p_k = c_k->head;

    while (p_j != NULL && p_k != NULL) {
        if(p_j->valor_elemento < p_k->valor_elemento) {
            no_elemento* novo_elemento = malloc(sizeof(no_elemento));
            if (novo_elemento != NULL) {
                novo_elemento->valor_elemento = p_j->valor_elemento;
                novo_elemento->prox = NULL;
            
                if (temp.head == NULL) {
                    temp.head = novo_elemento;
                } else {
                    tail->prox = novo_elemento;
                }
                tail = novo_elemento;
                temp.tamanho++;
            }
            p_j = p_j->prox;
        }
        else if (p_j->valor_elemento > p_k->valor_elemento) {
            p_k = p_k->prox;
        }
        else {
            p_j = p_j->prox;
            p_k = p_k->prox;
        }
    }

    while (p_j != NULL) {
        no_elemento* novo_elemento = malloc(sizeof(no_elemento));
        if (novo_elemento != NULL) {
            novo_elemento->valor_elemento = p_j->valor_elemento;
            novo_elemento->prox = NULL;

            if (temp.head == NULL) temp.head = novo_elemento;
            else tail->prox = novo_elemento;
            
            tail = novo_elemento;
            temp.tamanho++;
        }
        p_j = p_j->prox;
    }

    inicializar_conjunto(c_i);
    c_i->head = temp.head;
    c_i->tamanho = temp.tamanho;
}

void conjunto_intersecao(conjunto* c_i, conjunto* c_j, conjunto* c_k) {
    conjunto temp = {0, NULL};
    no_elemento* tail = NULL;

    no_elemento* p_j = c_j->head;
    no_elemento* p_k = c_k->head;

    while (p_j != NULL && p_k != NULL) {
        if(p_j->valor_elemento < p_k->valor_elemento) {
            p_j = p_j->prox;
        }
        else if (p_j->valor_elemento > p_k->valor_elemento) {
            p_k = p_k->prox;
        }
        else {
            no_elemento* novo_elemento = malloc(sizeof(no_elemento));
            if (novo_elemento != NULL) {
                novo_elemento->valor_elemento = p_j->valor_elemento;
                novo_elemento->prox = NULL;
            }
            if (temp.head == NULL) {
                temp.head = novo_elemento;
            } else {
                tail->prox = novo_elemento;
            }
            tail = novo_elemento;
            temp.tamanho++;
            p_j = p_j->prox;
            p_k = p_k->prox;
        }
        
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