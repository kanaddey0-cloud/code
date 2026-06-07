#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("PID of Test1.c = %d\n", getpid());

    pid_t p;
    p = fork();

    if (p == -1)
    {
        printf("There is an error while calling fork()\n");
    }

    if (p == 0)
    {
        printf("child process is running\n");
        printf("Now we will call Test2.c from child\n");

        char *args[] = {"./Test2", "C", "Programming", NULL};

        execv("./Test2", args);
    }
    else
    {
        printf("Now parent process is running\n");
    }

    return 0;
}
