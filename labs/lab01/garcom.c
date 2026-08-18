#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int l, c, q = 0;
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &l, &c);
        if (l > c) {
            q += c;
        }
    }
    printf("%d\n", q);
    return 0;
}