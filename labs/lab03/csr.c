#include <stdio.h>
#include <stdlib.h>

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

void montar_csr(int k, int *A, int *C, coordenada *VC, int *R) {
    int index_entradas = 0;
    int n_elementos = 0;

    for (int l = 0; l <= VC[k-1].i; l++) {
        while (index_entradas < k) {
            if (VC[index_entradas].i < l) {
                n_elementos++;
            }
            A[index_entradas] = VC[index_entradas].x;
            C[index_entradas] = VC[index_entradas].j;
            

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

    int *R = (int *) malloc(VC[k-1].i * sizeof(int));

    for (int l = 0; l < k; l++) {
        printf("%d ", VC[l].i);
    }
    printf("\n");

    montar_csr(k, A, C, VC, R);

    /*for (int l = 0; l < k; l++) {
        printf("%d ", A[l]);
    }
    printf("\n");

    for (int l = 0; l < k; l++) {
        printf("%d ", C[l]);
    }
    printf("\n");

    for (int l = 0; l < VC[k].i; l++) {
        printf("%d ", R[l]);
    }
    printf("\n");*/

    return 0;
}