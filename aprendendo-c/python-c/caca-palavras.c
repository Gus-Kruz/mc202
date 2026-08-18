#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PALAVRA  15

#define MAX_ALTURA  15
#define MAX_LARGURA 10

void ler_matriz(char matriz[MAX_ALTURA][MAX_LARGURA], int m, int n) {
    int i, j;
    char letra;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf(" %c", &letra);
            matriz[i][j] = letra;
        }
    }
}

void criar_matriz_ponto(char matriz[MAX_ALTURA][MAX_LARGURA], int m, int n) {
    int i, j;
    char letra;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            matriz[i][j] = '.';
        }
    }
}

void imprimir_matriz(char matriz[MAX_ALTURA][MAX_LARGURA], int m, int n) {
    int i, j;
    char letra;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void copiar_inverso(char palavra[], char inverso[]) {
    int i, j;
    i = strlen(palavra) - 1;  /* índice da última letra de palavra */
    j = 0;                             /* índice da primeira posição de inverso */
    while (i >= 0) {
        /* copia a i-ésima letra de palavra para a j-ésima posição de inverso */
        inverso[j] = palavra[i];
        i = i - 1;
        j = j + 1;
    }
    /* adicionamos o '\0' para indicar que a string inverso terminou */
    inverso[j] = '\0';
}

void marcar_ocorrencia_horizontal(char palavra[],
        char A[MAX_ALTURA][MAX_LARGURA],
        char B[MAX_ALTURA][MAX_LARGURA],
        int m, int n, int i, int j)
{   
    int tamanho = strlen(palavra);
    bool igual = true;
    if (j + tamanho <= n) {
        for (int k = 0; k < tamanho; k++) {
            if (A[i][j+k] != palavra[k]) {
                igual = false;
            }
        }
        if (igual) {
            for (int l = 0; l < tamanho; l++) {
                B[i][j+l] = palavra[l];
            }
        }
    }
}
void marcar_ocorrencia_vertical(char palavra[],
        char A[MAX_ALTURA][MAX_LARGURA],
        char B[MAX_ALTURA][MAX_LARGURA],
        int m, int n, int i, int j)
{   
    int tamanho = strlen(palavra);
    bool igual = true;
    if (i + tamanho <= m) {
        for (int k = 0; k < tamanho; k++) {
            if (A[i+k][j] != palavra[k]) {
                igual = false;
            }
        }
        if (igual) {
            for (int l = 0; l < tamanho; l++) {
                B[i+l][j] = palavra[l];
            }
        }
    }
}

void marcar_ocorrencia_diagonal(char palavra[],
        char A[MAX_ALTURA][MAX_LARGURA],
        char B[MAX_ALTURA][MAX_LARGURA],
        int m, int n, int i, int j)
{
    int tamanho = strlen(palavra);
    bool igual = true;
    if (i + tamanho <= m && j + tamanho <= n) {
        for (int k = 0; k < tamanho; k++) {
            if (A[i+k][j+k] != palavra[k]) {
                igual = false;
            }
        }
        if (igual) {
            for (int l = 0; l < tamanho; l++) {
                B[i+l][j+l] = palavra[l];
            }
        }
    }
    igual = true;
    if (i - tamanho + 1 >= 0 && j + tamanho <= n) {
        for (int k = 0; k < tamanho; k++) {
            if (A[i-k][j+k] != palavra[k]) {
                igual = false;
            }
        }
        if (igual) {
            for (int l = 0; l < tamanho; l++) {
                B[i-l][j+l] = palavra[l];
            }
        } 
    }
}

void marcar_ocorrencias(char palavra[],
        char A[MAX_ALTURA][MAX_LARGURA],
        char B[MAX_ALTURA][MAX_LARGURA],
        int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            marcar_ocorrencia_horizontal(palavra, A, B, m, n, i, j);
            marcar_ocorrencia_vertical(palavra, A, B, m, n, i, j);
            marcar_ocorrencia_diagonal(palavra, A, B, m, n, i, j);
        }
    }
}



int main() {
    int i;
    int m, n, p;
    char A[MAX_ALTURA][MAX_LARGURA];
    char B[MAX_ALTURA][MAX_LARGURA];
    char palavra[MAX_PALAVRA], inverso[MAX_PALAVRA];

    /* lê e cria matrizes */
    scanf("%d %d", &m, &n);
    ler_matriz(A, m, n);
    criar_matriz_ponto(B, m, n);

    /* lê e marca cada palavra */
    scanf("%d", &p);
    for (i = 0; i < p; i++) {
        scanf("%s", palavra);
        marcar_ocorrencias(palavra, A, B, m, n);
        copiar_inverso(palavra, inverso);
        marcar_ocorrencias(inverso, A, B, m, n);
    }

    /* imprime matriz resultante */
    imprimir_matriz(B, m, n);
}
