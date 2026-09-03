#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int i;
    int j;
    int x;
} coordenada;

int compare_coordenadas(const void *a, const void *b) {
    const coordenada *c1 = (const coordenada *) a;
    const coordenada *c2 = (const coordenada *) b;

    if (c1->i != c2->i) {
        return (c1->i - c2->i);
    }

    return (c1->j - c2->j);
}

void montar_csr(int *A, int *C, coordenada *VC, int *R, int k, int n_linhas) {
    int index_lista = 0;

    for (int l = 0; l <= n_linhas; l++) {
        while (index_lista < k) {
            A[index_lista] = VC[index_lista].x;
            C[index_lista] = VC[index_lista].j;
            if (VC[index_lista].i < l) {
                index_lista++;
            } else {
                R[l] = index_lista;
                if (VC[index_lista].i == l) {
                    index_lista++;
                    break;
                } else {
                    R[l+1] = index_lista;
                    break;
                }
            }
        }
        if (index_lista == k) {
            R[l] = index_lista;
        }
    }
}

int buscar_elemento(int *R, int *A, int *C, int n_linhas, int i_busca, int j_busca) {
    bool encontrou_j = false;
    int posicao;

    if (i_busca > n_linhas || R[i_busca] == R[i_busca + 1]) {
        return 0;
    } else {
        for (int k = R[i_busca]; k < R[i_busca+1]; k++) {
            if (j_busca == C[k]) {
                encontrou_j = true;
                posicao = k;
                break;
            }
        }
        if (encontrou_j) {
            return A[posicao];
        } else {
            return 0;
        }
    }
}

int main() {
    int k, i_busca, j_busca, valor_encontrado;

    scanf("%d", &k);
    int *A = (int *) malloc(k * sizeof(int));
    int *C = (int *) malloc(k * sizeof(int));
    coordenada *VC = (coordenada *) malloc(k * sizeof(coordenada));

    for (int l = 0; l < k; l++) {
        scanf(" %d %d %d", &VC[l].i, &VC[l].j, &VC[l].x);
    }

    qsort(VC, k, sizeof(coordenada), compare_coordenadas);

    int n_linhas = VC[k-1].i + 1;

    int *R = (int *) malloc((VC[k-1].i + 2) * sizeof(int));

    montar_csr(A, C, VC, R, k, n_linhas);

    free(VC);

    while (true) {
        scanf(" %d %d", &i_busca, &j_busca);
        if (i_busca == -1 && j_busca == -1) {
            free(A);
            free(C);
            free(R);
            exit(EXIT_SUCCESS);
        } else {
            valor_encontrado = buscar_elemento(R, A, C, n_linhas, i_busca, j_busca);
            printf("(%d,%d) = %d\n", i_busca, j_busca, valor_encontrado);
        }
    }

    return 0;
}