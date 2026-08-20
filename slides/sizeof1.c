#include <stdio.h>

int main(void) {
    printf("char \t\t %ld\n", sizeof(char));
    printf("short int \t %ld\n", sizeof(short));
    printf("int \t\t %ld\n", sizeof(int));
    printf("long int \t %ld\n", sizeof(long));
    printf("long long int \t %ld\n", sizeof(long long));
    printf("float \t\t %ld\n", sizeof(float));
    printf("double \t\t %ld\n", sizeof(double));
    printf("long double \t %ld\n", sizeof(long double));
    printf("5+9 \t\t %ld\n", sizeof(5 + 9));
    printf("3*2.0 \t\t %ld\n", sizeof(3 * 2.0));
    float f;
    printf("f \t\t %ld\n", sizeof(f));
return 0;
}