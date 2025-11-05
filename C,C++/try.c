#include <stdio.h>
#include <string.h>

int main() {
    char s[] = "123456789";
    int n = strlen(s);

    for (int i = 0; i < n - 1; ++i) {
        // Print the left part of the pattern
        for (int j = 0; j <= i; ++j) {
            printf("%c", s[j]);
        }

        // Print the right part of the pattern in reverse
        for (int j = i - 1; j >= 0; --j) {
            printf("%c", s[j]);
        }

        // Move to the next line
        printf("\n");
    }

    return 0;
}
