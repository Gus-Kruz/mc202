#include <stdio.h>

int main(void) {
    int i, n;
    int velocidades[100];

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", &velocidades[i]);
    }

    int duracao, limite;
    scanf("%d", &duracao);
    if (duracao == 1) {
        limite = 100;
    }
    else if (duracao == 2) {
        limite = 20;
    }
    else {
        limite = 10;
    }

    int max = 0;

    for(int i = 0; i < n; i++) {
        if (velocidades[i] > max && velocidades[i] <= limite) {
            max = velocidades[i];
        }
    }

    printf("%d\n", max);
}