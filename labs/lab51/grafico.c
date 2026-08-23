#include <stdio.h>

int main() {
    int A, B;
    char S;
    
    while (scanf(" (%d,%d,%c)", &A, &B, &S) != EOF) {
        char G[B+1];
        for (int i = 0; i<B; i++) {
            G[i] = S;
        }
        G[B] = '\0';

        printf("%4d |%s %d\n", A, G, B);
    }
    return 0;
}