#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int p1, p2, p3;
    
    p1 = rand() % 6;

    do {
        p2 = rand() % 6;
    } while (p2 == p1);

    do {
        p3 = rand() % 6;
    } while (p3 == p1 || p3 == p2);

    char P[6][12] = {"Cauê", "Coca", "Eduardo", "Gustavo", "Luis", "Yuji"};
    
    printf("Grupo sorteado:\n");
    printf("%s, ", P[p1]);
    printf("%s, ", P[p2]);
    printf("%s\n", P[p3]);
    
    return 0;
}