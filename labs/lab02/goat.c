#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int encontrar_final(char palavra[]) {
    int i = 0;
    while (palavra[i] != '\0') {
        i++;
    }

    return i;
}

void regra_um(char palavra[]) {
    if (palavra[0] == 'a' || palavra[0] == 'A'
    || palavra[0] == 'e' || palavra[0] == 'E'
    || palavra[0] == 'i' || palavra[0] == 'I'
    || palavra[0] == 'o' || palavra[0] == 'O'
    || palavra[0] == 'u' || palavra[0] == 'U') {
        int i_final = strlen(palavra);
        palavra[i_final] = 'm';
        palavra[i_final + 1] = 'a';
        palavra[i_final + 2] = '\0';
    }
}

void aplicar_regras(char palavra[]) {
    regra_um(palavra);
}

int main() {
    char frase[10000][100];
    int i = 0;
    while (true) {
        if (scanf("%s", frase[i]) != EOF) {
            i++;
        }
        else {
            break;
        }
    }
    for (int j = 0; j < i; j++) {
        aplicar_regras(frase[j]);
        printf("%s ", frase[j]);
    }
    return 0;
}