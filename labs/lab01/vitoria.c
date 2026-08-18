#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int J, Z, t = 1;

    while (N != 0) {
        printf("Teste %d\n", t);
        t++;
        int diferenca = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d %d", &J, &Z);
            diferenca += (J - Z);
            printf("%d\n", diferenca);
        }
        printf("\n");

        scanf("%d", &N);
    }
    return 0;
}