#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid;

    char write_msg[] = "Hello MCA Students";
    char read_msg[100];
    char buffer[200];

    // STEP 1 : Create Pipe
    if (pipe(fd) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }

    printf("Pipe created successfully\n");

    // STEP 2 : Create Child Process
    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    // CHILD PROCESS
    else if (pid == 0)
    {
        close(fd[1]);

        read(fd[0], read_msg, sizeof(read_msg));
        printf("\nChild Process\n");
        printf("Child received message: %s\n", read_msg);

        close(fd[0]);
    }

    // PARENT PROCESS
    else
    {
        close(fd[0]);

        write(fd[1], write_msg, strlen(write_msg) + 1);
        printf("\nParent Process\n");
        printf("Parent sent message: %s\n", write_msg);

        close(fd[1]);
    }

    return 0;
}
