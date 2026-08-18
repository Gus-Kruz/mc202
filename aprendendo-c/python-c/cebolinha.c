#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PALAVRA 20

void cebolizar(char palavra_original[], char palavra_cebola[]) {
    int tamanho = strlen(palavra_original);
    bool ultima_R = false;
    int j = 0;

    for(int i = 0; i < tamanho; i++) {
        char letra_atual = palavra_original[i];
        if (letra_atual == 'R') {
            if (!ultima_R) {
                palavra_cebola[j] = 'L';
                j++;
            }
            ultima_R = true;
        }
        else {
            palavra_cebola[j] = letra_atual;
            j++;
            ultima_R = false;
        }
    }
    palavra_cebola[j] = '\0';
}

int main() {
    char palavra_original[MAX_PALAVRA];
    char palavra_cebola[MAX_PALAVRA];

    scanf("%s", palavra_original);

    cebolizar(palavra_original, palavra_cebola);
    printf("%s\n", palavra_cebola);

}