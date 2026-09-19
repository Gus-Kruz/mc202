#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "operacoes.h"

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