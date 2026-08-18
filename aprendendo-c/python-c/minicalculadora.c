#include <stdio.h>
#include <stdbool.h>

int main() {
    float operando1, operando2;
    float resultado;
    char operador;
    bool operante = true;
    while (operante == true){
        printf("Digite a operação ou encerre com x / 0:\n");
        scanf("%f %c %f", &operando1, &operador, &operando2);
        switch (operador) {

            case '+':
                resultado = operando1 + operando2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case '-': 
                resultado = operando1 - operando2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case '*':
                resultado = operando1 * operando2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case '/': 
                resultado = operando1 / operando2;
                if (operando2 == 0) {
                    operante = false;
                    break;
                }
                printf("Resultado: %.2f\n", resultado);
                break;
        }
    }
}