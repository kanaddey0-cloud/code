#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        sleep(10);

        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());

        printf("Parent process terminated\n");
        exit(0);
    }

    return 0;
}
