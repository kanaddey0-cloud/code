#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid, mypid, myppid;

    pid = getpid();

    printf("Before fork: Process id is %d\n", pid);
    printf("Called fork() system call\n");

    pid = fork();

    if (pid < 0)
    {
        perror("fork() failure");
        return 1;
    }

    if (pid == 0)
    {
        // Child Process

        printf("This is child process and pid = %d\n", pid);

        mypid = getpid();
        myppid = getppid();

        printf("Process id is %d and PPID is %d\n", mypid, myppid);
    }
    else
    {
        // Parent Process

        sleep(2);

        printf("This is parent process\n");

        mypid = getpid();
        myppid = getppid();

        printf("Process id is %d and PPID is %d\n", mypid, myppid);

        printf("Newly created process id or child pid is %d\n", pid);
    }

    return 0;
}
