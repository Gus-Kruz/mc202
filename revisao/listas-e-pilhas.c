/*59 - em um fila os dados são armazenados de tal que forma que o primeiro a entrar é o primeiro a sair enquanto na pilha são armazenadas de forma que o último a entrar é o primeiro a sair*/

/*60 - como está a fila:

saída: EASYQUESTION*/

/*61 - FILA: 19, 31, 7, 2, 19, 7, 2, 19

SAIDA: 13, 19, 23, 27, 13 */

//63

void jump(int vetor_circ[], int i, int k, int first, int tam_vet) {
    int aux = vetor_circ[first + i];

    for (int j = i - 1; j >= i-k; j--) {
        vetor_circ[(first + j + 1) % tam_vet] = vetor_circ[(first + j) % tam_vet]; 
    }

    vetor_circ[(first + i - k) % tam_vet] = aux;
}