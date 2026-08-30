#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char nome[51];
    char endereco[101];
    char telefone[16];
    char aniversario[9];
} contato;

void inserir_contato(contato lista_contatos[], int *tamanho_lista) {
    /*recebe uma lista de contatos, lê os dados do contato e adiciona a lista de contatos e imprime uma mensagem*/
    scanf(" %[^\n]", lista_contatos[*tamanho_lista].nome);
    scanf(" %[^\n]", lista_contatos[*tamanho_lista].endereco);
    scanf(" %s", lista_contatos[*tamanho_lista].telefone);
    scanf(" %s", lista_contatos[*tamanho_lista].aniversario);

    printf("Contato para %s inserido.\n", lista_contatos[*tamanho_lista].nome);
    printf("\n");

    (*tamanho_lista)++;
}

void remover_contato(contato lista_contatos[], int *tamanho_lista) {
    /* recebe um nome e uma lista, remove todos os contatos que tenham mesmo nome da lista e imprime o número de removidos*/
    char nome_remover[51];
    int removidos = 0;

    scanf(" %[^\n]", nome_remover);

    for (int i = 0; i < *tamanho_lista; i++) {
        if (strcmp(nome_remover, lista_contatos[i].nome) == 0) {
            for (int j = i; j < *tamanho_lista - 1; j++) {
                lista_contatos[j] = lista_contatos[j+1];
            }
            i--;
            (*tamanho_lista)--;
            removidos++;
        }
    }

    printf("Contatos de %s removidos: %d\n", nome_remover, removidos);
    printf("\n");
}

void buscar_contato(contato lista_contatos[], int *tamanho_lista) {
    /* recebe um nome, busca e imprime todos os contatos com o mesmo nome */
    char nome_buscar[51];
    bool encontrou = false;

    scanf(" %[^\n]", nome_buscar);

    printf("Resultado da busca:\n");

    for (int i = 0; i < *tamanho_lista; i++) {
        if (strcmp(nome_buscar, lista_contatos[i].nome) == 0) { 
            printf("(%d) %s	%s	%s	%s\n", (i+1), lista_contatos[i].nome, lista_contatos[i].endereco, lista_contatos[i].telefone, lista_contatos[i].aniversario);
            encontrou = true;
        }
    }

    if (!encontrou) {
        printf("Nenhum contato.\n");
    }

    printf("\n");
}

void imprimir_contatos(contato lista_contatos[], int *tamanho_lista) {
    /* imprime todos os contatos da lista*/
    printf("Listagem:\n");

    if (*tamanho_lista > 0) {
        for (int i = 0; i < *tamanho_lista; i++) {
            printf("(%d) %s	%s	%s	%s\n", (i+1), lista_contatos[i].nome, lista_contatos[i].endereco, lista_contatos[i].telefone, lista_contatos[i].aniversario);
        }
    } else {
        printf("Nenhum contato.\n");
    }

    printf("\n");
}

void finalizar_programa() {
    exit(EXIT_SUCCESS);
}

int main() {
    char operador;
    contato lista_contatos[1000];
    int tamanho_lista = 0;

    while (true) {  // programa finaliza no caso f 
        if(scanf(" %c", &operador) != 1) break;

        switch (operador) {
            case 'i':
                inserir_contato(lista_contatos, &tamanho_lista);
                
                break;
            case 'r':
                remover_contato(lista_contatos, &tamanho_lista);

                break;
            case 'b':
                buscar_contato(lista_contatos, &tamanho_lista);

                break;
            case 'p':
                imprimir_contatos(lista_contatos, &tamanho_lista);

                break;
            case 'f':
                finalizar_programa();
        }
    }
}