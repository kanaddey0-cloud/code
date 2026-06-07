#include <stdio.h>
#include <stdlib.h> // atoi(); atof();
#include <unistd.h>

int main(int argc, char *argv[], int x)  //(number of arguments, array of strings)
{
    printf("Inside prog2.c program PID = %d\n", getpid());
    printf("Arguments received:\n");

    int i;
    for(i = 0; i < (argc-2); i++){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    printf("int  : %d", atoi(argv[i++]));     // strtoi(argv[i++])
    printf("float: %.3f\n", atof(argv[i]));   // strtoi(argv[i++])

    return 0;
}