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

void montar_csr_2(int k, coordenada *VC, int *R) {
    int n_R = VC[k-1].i + 1;
    int n_elementos = 0;
    int index_lista = 0;
    for (int l = 0; l < n_R; l++) {
        if (VC[index_lista].i >= l) {
            
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

    int *R = (int *) malloc((VC[k-1].i + 1) * sizeof(int));

    montar_csr_1(k, A, C, VC);

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

    montar_csr_2(k, VC, R);

    printf("Vetor R: ");
    for (int l = 0; l < (VC[k-1].i + 1); l++) {
        printf("%d ", R[l]);
    }
    printf("\n");

    return 0;
}