#include <stdio.h>

int main() {
    int a = 5, b = 3, sum;

    asm (
        "addl %%ebx, %%eax;"
        : "=a"(sum)          // output
        : "a"(a), "b"(b)    // input
    );

    printf("Sum = %d\n", sum);

    return 0;
}