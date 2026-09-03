#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_inversoes;
    char *sequencia;
} cadeia;

int medir_inversoes(char *sequencia, int j) {
    int n_inversoes = 0;
    for (int i = 0; i < j-1; i++) {
        int distancia = sequencia[i] - sequencia[i+1];
        if (distancia > 0) {
            n_inversoes += distancia;
        }
    }
    return n_inversoes;
}

int compare_cadeias(const void *a, const void *b) {
    const cadeia *c1 = (const cadeia *) a;
    const cadeia *c2 = (const cadeia *) b;

    return (c1->n_inversoes - c2->n_inversoes);
}

int main() {
    int c, j, k;

    scanf(" %d", &c);

    for(int i = 0; i < c; i++) {

        scanf(" %d %d", &j, &k);

        cadeia *DNAS = (cadeia *) malloc(k * sizeof(cadeia));

        for (int i =0; i < k; i++) {
            DNAS[i].sequencia = (char *) malloc(j * sizeof(char));

            scanf(" %s", DNAS[i].sequencia);
            DNAS[i].n_inversoes = medir_inversoes(DNAS[i].sequencia, j);
        }

        qsort(DNAS, k, sizeof(cadeia), compare_cadeias);

        for (int i = 0; i < k; i++) {
            printf("%s\n", DNAS[i].sequencia);
        }
        printf("\n");

        for(int i = 0; i < k; i++) {
            free(DNAS[i].sequencia);
        }

        free(DNAS);
    }

    return 0;
}