#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_inversoes;
    int pos_original;
    char *sequencia;
} cadeia;

int medir_inversoes(char *sequencia, int j) {
    int n_ocorr[4] = {0,0,0,0}; // n_ocorr = [n_A, n_C, n_G, n_T]
    int n_inversoes = 0;

    for (int i = j-1 ; i >= 0; i--) {
        switch (sequencia[i]) {
        case 'T':
            n_inversoes += n_ocorr[0] + n_ocorr[1] + n_ocorr[2];
            n_ocorr[3]++;
            break;
        case 'G':
            n_inversoes += n_ocorr[0] + n_ocorr[1];
            n_ocorr[2]++;
            break;
        case 'C':
            n_inversoes += n_ocorr[0];
            n_ocorr[1]++;
            break;
        case 'A':
            n_ocorr[0]++;
        }
    }

    return n_inversoes;
}

int compare_cadeias(const void *a, const void *b) {
    const cadeia *c1 = (const cadeia *) a;
    const cadeia *c2 = (const cadeia *) b;

    if (c1->n_inversoes != c2->n_inversoes) {
        return (c1->n_inversoes - c2->n_inversoes);
    } else {
        return (c1->pos_original - c2->pos_original);
    }
}

int main() {
    int c, j, k;

    scanf(" %d", &c);

    for(int i = 0; i < c; i++) {

        scanf(" %d %d", &j, &k);

        cadeia *DNAS = (cadeia *) malloc(k * sizeof(cadeia));

        for (int i = 0; i < k; i++) {
            DNAS[i].sequencia = (char *) malloc((j+1) * sizeof(char));

            scanf(" %s", DNAS[i].sequencia);
            DNAS[i].pos_original = i;
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