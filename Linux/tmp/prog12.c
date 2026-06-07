#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSTRS 5

int main()
{
    int cntr;
    FILE *pipe_fp;

    char *strings[MAXSTRS] =
    {
        "kolkata",
        "bombay",
        "delhi",
        "patna",
        "siliguri"
    };

    // Open pipe to sort command
    pipe_fp = popen("sort", "w");

    if (pipe_fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    printf("Strings before sorting:\n\n");

    for (cntr = 0; cntr < MAXSTRS; cntr++)
    {
        printf("%s\n", strings[cntr]);

        // Send strings to sort command
        fputs(strings[cntr], pipe_fp);
        fputc('\n', pipe_fp);
    }

    // Close pipe
    pclose(pipe_fp);

    return 0;
}
