#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
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
    if (!(palavra[0] == 'a' || palavra[0] == 'A'  // note a negação
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

int regra_tres(char palavra[], int tamanho_0, int tamanho) {
    for (int i = 0; i < tamanho_0; i++) {
        palavra[tamanho + i] = 'a';
    }
    palavra[tamanho + tamanho_0] = '\0';

    return tamanho *= 2;

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

int aplicar_regras(char palavra[], int soma) {
    int tamanho_0 = strlen(palavra);
    tamanho_0 = regra_quatro(palavra, tamanho_0, &soma);
    int tamanho = tamanho_0;
    if (tamanho == 0) { // otimização caso apague
        return soma;
    }

    tamanho = regra_um(palavra, tamanho);
    tamanho = regra_dois(palavra, tamanho);
    tamanho = regra_tres(palavra, tamanho_0, tamanho);
    
    return soma;
}

int main() {
    char frase[10000][100];
    int i = 0;
    int soma = 0;
    char c;
    bool linha_acabou = false;
    
    while (scanf("%s", frase[i]) == 1) {
        soma = aplicar_regras(frase[i], soma);
        i++;
        
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
                printf("1 goat says:");
            } else {
                printf("%d goats say:", soma);
            }

            for (int j = 0; j < i; j++) {
                if (frase[j][0] != '\0') {
                    printf(" %s", frase[j]);
                }
            }
            printf("\n");
            
            i = 0;
            soma = 0;
            linha_acabou = false;
        }
    }
    
    // caso que não tem quebra de linha no final do arquivo
    if (i > 0) {  
        if (soma == 1) {
            printf("1 goat says:");
        } else {
            printf("%d goats say:", soma);
        }

        for (int j = 0; j < i; j++) {
            if (frase[j][0] != '\0') {
                printf(" %s", frase[j]);
            }
        }
        printf("\n");
    }

    return 0;
}
