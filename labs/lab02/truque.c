#include <stdio.h>
#include <math.h>

int somar_truque(int S[], int R[], int i, int j, int r) {
    int s = 0;

    // caso em que um bloco não é formado
    if (i / r == j / r) {
        for (int k = i; k <= j; k++) {
            s += S[k];
        }
        return s;
    }

    // somando os elementos excluídos à esquerda
    int proximo_bloco = ((i / r) + 1) * r;
    for (int k = i; k < proximo_bloco; k++) {
        s += S[k];
    }

    // somando os blocos de R
    int bloco_inicio = (i / r) + 1;
    int bloco_fim = j / r;
    for (int k = bloco_inicio; k < bloco_fim; k++) {
        s += R[k];
    }

    // somando os elementos excluidos a direita
    int inicio_do_fim = bloco_fim * r;
    for (int k = inicio_do_fim; k <= j; k++) {
        s += S[k];
    }

    return s;
}       

void atualizar_truque(int S[], int R[], int i, int x, int r) {
    R[i / r] += x - S[i];
    S[i] = x;
}

int main() {
    int n;
    scanf("%d", &n);

    int S[n];
    for (int i = 0; i < n; i++) {
        scanf("%d ", &S[i]);
    }

    // calculando o vetor R
    int r = ceil(sqrt(n));
    int num_blocos = (n - 1) / r + 1;
    int R[num_blocos];

    for (int k = 0; k < num_blocos; k++) {
        R[k] = 0;
    }

    for (int i = 0; i < n; i++) {
        R[i / r] += S[i];
    }

    char operacao;
    int i, v;
    
    while (scanf(" %c %d %d", &operacao, &i, &v) != EOF) {
        if (operacao == 's') {
            printf("%d\n", somar_truque(S, R, i, v, r));
        } else if (operacao == 'a') {
            atualizar_truque(S, R, i, v, r);
        }
    }

    return 0;
}