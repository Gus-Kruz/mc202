#include <stdio.h>
#include <math.h>
int main(void) {
    int i = 13, j = -13;
    printf("0: >%010d< >%010d< \n", i, j);
    printf("-: >%-10d< >%-10d< \n", i, j);
    printf("+: >%+d< >%+d< \n", i, j);
    printf(" : >% d< >% d< \n", i, j);
    int k = printf(" : >%016lf< \n", M_PI);
    printf("k=%d\n",k);
    return 0;
}