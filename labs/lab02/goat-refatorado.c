#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Observações: fiz tamanho ser retornado para não ter que usar strlen() várias vezes

int regra_um(char palavra[], int tamanho) {
    if (tolower(palavra[0]) == 'a'
    || tolower(palavra[0]) == 'e'
    || tolower(palavra[0]) == 'i'
    || tolower(palavra[0]) == 'o'
    || tolower(palavra[0]) == 'u') {
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
    if (!(tolower(palavra[0]) == 'a'
    || tolower(palavra[0]) == 'e'
    || tolower(palavra[0]) == 'i'
    || tolower(palavra[0]) == 'o'
    || tolower(palavra[0]) == 'u')) {
        leftshift_array(palavra, tamanho);
        palavra[tamanho] = 'm';
        palavra[tamanho + 1] = 'a';
        palavra[tamanho + 2] = '\0';
        tamanho += 2;
    }
    return tamanho;
}

int regra_tres(char palavra[], int tamanho_0, int tamanho) {
    for (int i = 0; i < tamanho_0; i++) {
        palavra[tamanho + i] = 'a';
    }
    palavra[tamanho + tamanho_0] = '\0';

    return tamanho + tamanho_0;

}

int apagar_parte(char palavra[], int i, int j, int tamanho) {
    int tamanho_apagar = (j - i) + 1;

    for (int k = 0; k < tamanho - (j + 1); k++) {
        palavra[i+k] = palavra[j+1+k];
    }
    
    tamanho -= tamanho_apagar;

    palavra[tamanho] = '\0';

    return tamanho;
}

int regra_quatro(char palavra[], int tamanho, int *soma) {
    int i = 0;
    int j = 0;
    while (i < tamanho) {
        if (isdigit(palavra[i])) {
            char str_numero[15];

            j = i;
            while (j < tamanho && isdigit(palavra[j])) {
                str_numero[j - i] = palavra[j];
                j++;
            }

            str_numero[j - i] = '\0';
            *soma += atoi(str_numero);
            j--;

            tamanho = apagar_parte(palavra, i, j, tamanho);

            continue;

        } else if (ispunct(palavra[i])) {
            j = i;
            while (j < tamanho && ispunct(palavra[j])) {
                j++;
            }
            j--;
            tamanho = apagar_parte(palavra, i, j, tamanho);

            continue;
        }
        i++;
    }

    return tamanho;
}

int aplicar_regras(char palavra[], int soma, int *tamanho) {
    
    *tamanho = regra_quatro(palavra, *tamanho, &soma);
    int tamanho_0 = *tamanho;

    if (*tamanho == 0) { // otimização caso apague
        return soma;
    }

    *tamanho = regra_um(palavra, *tamanho);
    *tamanho = regra_dois(palavra, *tamanho);
    *tamanho = regra_tres(palavra, tamanho_0, *tamanho);
    
    return soma;
}

int adicionar_palavra(char frase[], char palavra[], int tamanho_frase, int tamanho_palavra) {
    for (int i = 0; i < tamanho_palavra; i++) {
        frase[tamanho_frase + i] = palavra[i];
    }

    frase[tamanho_frase + tamanho_palavra] = ' ';

    tamanho_frase += tamanho_palavra + 1;

    return tamanho_frase;
}

int main() {
    char frase[200000];
    char palavra_atual[100];
    int i = 0;
    int soma = 0;
    char c;
    bool linha_acabou = false;
    int tamanho_frase = 0;
    
    while (scanf("%s", palavra_atual) == 1) {
        int tamanho_palavra = strlen(palavra_atual);
        soma = aplicar_regras(palavra_atual, soma, &tamanho_palavra);

        if (tamanho_palavra > 0) {
            tamanho_frase = adicionar_palavra(frase, palavra_atual, tamanho_frase, tamanho_palavra);
        }

        while ((c = getchar()) != EOF) {
            if (c == '\n') {
                linha_acabou = true;
                break;
            } else if (!isspace(c)) {
                ungetc(c, stdin);
                break;
            }
        }

        if (linha_acabou) {
            if (soma == 1) {
                printf("1 goat says: ");
            } else {
                printf("%d goats say: ", soma);
            }
            frase[tamanho_frase] = '\0';
            printf("%s\n", frase);

            soma = 0;
            linha_acabou = false;
            tamanho_frase = 0;
        }
    }


    if (soma == 1) {
        printf("1 goat says: ");
    } else {
        printf("%d goats say: ", soma);
    }
    frase[tamanho_frase] = '\0';
    printf("%s\n", frase);


    return 0;
}