#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Observações: fiz tamanho ser retornado para não ter que usar strlen() várias vezes

int regra_um(char palavra[], int tamanho) {
    if (palavra[0] == 'a' || palavra[0] == 'A'
    || palavra[0] == 'e' || palavra[0] == 'E'
    || palavra[0] == 'i' || palavra[0] == 'I'
    || palavra[0] == 'o' || palavra[0] == 'O'
    || palavra[0] == 'u' || palavra[0] == 'U') {
        palavra[tamanho] = 'm';
        palavra[tamanho + 1] = 'a';
        palavra[tamanho + 2] = '\0';
        tamanho += 2;
    }
    return tamanho;
}

void leftshift_array(char array[], int tamanho) {
    char ajudante = array[0];

    for (int i = 0; i < tamanho-1; i++) {
        array[i] = array[i+1];
    }

    array[tamanho-1] = ajudante;
}

int regra_dois(char palavra[], int tamanho) {
    if (!(palavra[0] == 'a' || palavra[0] == 'A'
    || palavra[0] == 'e' || palavra[0] == 'E'
    || palavra[0] == 'i' || palavra[0] == 'I'
    || palavra[0] == 'o' || palavra[0] == 'O'
    || palavra[0] == 'u' || palavra[0] == 'U')) {
        leftshift_array(palavra, tamanho);
        palavra[tamanho] = 'm';
        palavra[tamanho + 1] = 'a';
        palavra[tamanho + 2] = '\0';
        tamanho += 2;
    }
    return tamanho;
}

int regra_tres(char palavra[], int tamanho_original, int tamanho) {
    for (int i = 0; i < tamanho_original; i++) {
        palavra[tamanho + i] = 'a';
    }
    palavra[tamanho + tamanho_original] = '\0';

    return tamanho *= 2;

}

/*void apagar_parte(char palavra[], int i, int j) {
    int tamanho = (j - i) + 1;

    for (int k = 0; k < tamanho; k++) {
        palavra[i+k] = palavra[j+k+1];
    }
}*/

/*int apagar_num(char palavra[], int tamanho, int soma) {
    int i, j = 0;
    int numero;
    char str_numero[100];
    while (i<tamanho) {
        if (isdigit(palavra[i])){
            j = i;
            while (isdigit(palavra[j])) {
                str_numero[j-i] = palavra[j];
                j++;
            }
            //numero = atoi(str_numero);
            //apagar_parte(palavra, i, j);
        }
        i++;
    }
    return soma += numero;
}*/

/*int regra_quatro(char palavra[], int tamanho, int soma) {
    soma = apagar_num(palavra, tamanho, soma);
    return soma;
}*/

void aplicar_regras(char palavra[], int soma) {
    int tamanho_original = strlen(palavra);
    int tamanho = tamanho_original;
    //soma = regra_quatro(palavra, tamanho, soma);
    tamanho = regra_um(palavra, tamanho);
    tamanho = regra_dois(palavra, tamanho);
    tamanho = regra_tres(palavra, tamanho_original, tamanho);
}

int main() {
    char frase[100000][100];
    int i = 0;
    int soma = 0;
    while (true) {
        if (scanf("%s", frase[i]) != EOF) {
            i++;
        }
        else {
            break;
        }
    }
    for (int j = 0; j < i; j++) {
        int tamanho = strlen(frase[j]);
        aplicar_regras(frase[j], soma);
        printf("%s ", frase[j]);
    }

    return 0;
}