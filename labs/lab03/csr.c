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

void montar_csr_1(int k, int *A, int *C, coordenada *VC) {
    for (int l = 0; l < k; l++) {
        A[l] = VC[l].x;
        C[l] = VC[l].j;
    }
}

void montar_csr(int k, int *A, int *C, coordenada *VC, int *R) {
    int n_linhas = VC[k-1].i + 1;
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

int main() {
    int k, i, j, x;

    scanf("%d", &k);
    int *A = (int *) malloc(k * sizeof(int));
    int *C = (int *) malloc(k * sizeof(int));
    coordenada *VC = malloc(k * sizeof(coordenada));

    for (int l = 0; l < k; l++) {
        scanf(" %d %d %d", &VC[l].i, &VC[l].j, &VC[l].x);
    }

    qsort(VC, k, sizeof(coordenada), compare_coordenadas);

    printf("Vetor VC: ");
    for (int l = 0; l < k; l++) {
        printf("%d ", VC[l].i);
    }
    printf("\n");

    int *R = (int *) malloc((VC[k-1].i + 2) * sizeof(int));

    montar_csr(k, A, C, VC, R);

    printf("Vetor A: ");
    for (int l = 0; l < k; l++) {
        printf("%d ", A[l]);
    }
    printf("\n");

    printf("Vetor C: ");
    for (int l = 0; l < k; l++) {
        printf("%d ", C[l]);
    }
    printf("\n");

    printf("Vetor R: ");
    for (int l = 0; l < (VC[k-1].i + 2); l++) {
        printf("%d ", R[l]);
    }
    printf("\n");

    return 0;
}