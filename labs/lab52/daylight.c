#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int calcular_diferenca(char hora_f[], char min_f[], char seg_f[], char hora_i[], char min_i[], char seg_i[], bool solante) {
    int val_hf = atoi(hora_f);
    int val_mf = atoi(min_f);
    int val_sf = atoi(seg_f);

    int val_hi = atoi(hora_i);
    int val_mi = atoi(min_i);
    int val_si = atoi(seg_i);

    int diferenca;

    /*
    vamos dividir os casos 99:99:99 em três casos:
    - caso 1:
        somente o final é 99:99:99
    - caso 2:
        o final e o ínicio é 99:99:99
    - caso 3:
        somente o início é 99:99:99 
    */

    if ((val_hf == 99 && val_mf == 99 && val_sf == 99) && (val_hi != 99 && val_mi != 99 && val_si != 99)) {
        if (solante) {
            diferenca = 24 * 3600 - (3600 * val_hi + 60 * val_mi + val_si);
        }
        else {
            diferenca = 0;
        }
    } else if ((val_hf == 99 && val_mf == 99 && val_sf == 99) && (val_hi == 99 && val_mi == 99 && val_si == 99)) {
        if (solante) {
            diferenca = 24 * 3600;
        }
        else {
            diferenca = 0;
        }
    } else if ((val_hf != 99 && val_mf != 99 && val_sf != 99) && (val_hi == 99 && val_mi == 99 && val_si == 99)) {
        if (solante) {
            diferenca = val_hf * 3600 + val_mf * 60 + val_sf;
        }
        else {
            diferenca = 0;
        }
    } else {
        diferenca = (val_hf- val_hi) * 3600 + (val_mf - val_mi) * 60 + (val_sf - val_si);
        if (diferenca < 0) {
            diferenca = 24 * 3600 + diferenca;
        }
    }

    return diferenca;
}

int main() {
    char p_dia[2];
    char p_mes[2];
    char p_ano[4];

    char dia[2];
    char mes[2];
    char ano[4];

    char hora_i[2];
    char min_i[2];
    char seg_i[2];

    char hora_f[2];
    char min_f[2];
    char seg_f[2];

    int diferenca = 0;

    int dias_passados = 0;
    int mes_passados = 0;
    int anos_passados = 0;

    bool solante = false;

    scanf("%s/%s/%s", p_dia, p_mes, p_ano);

    scanf(" %s:%s:%s", hora_i, min_i, seg_i);
    scanf(" %s:%s:%s", hora_f, min_f, seg_f);
    
    diferenca += calcular_diferenca(hora_f, min_f, seg_f, hora_i, min_i, seg_i, solante);

    while (scanf(" %s/%s/%s", dia, mes, ano) == 3) {
        scanf(" %s:%s:%s", hora_i, min_i, seg_i);
        scanf(" %s:%s:%s", hora_f, min_f, seg_f);
        
        if(strcmp (hora_i, "99") != 0 && strcmp(hora_f, "99") != 0) {
            solante = false;
        } else if (solante && strcmp(hora_f, "99") != 0) {
            solante = false;
        } else if (strcmp(hora_i, "99") != 0 && strcmp(hora_f, "99") == 0) {
            solante = true;
        }

        diferenca += calcular_diferenca(hora_f, min_f, seg_f, hora_i, min_i, seg_i, solante);
    }

    while (diferenca >= 12 * 3600) {
        diferenca -= 12 * 3600;
        dias_passados++;
        if (dias_passados == 31) {
            mes_passados++;
            dias_passados = 0;
            if (mes_passados == 13) {
                anos_passados++;
                mes_passados = 0;
            }
        }
    }

}