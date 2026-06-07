#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    FILE *pipein_fd, *pipeout_fd;
    char readbuf[80];

    // Open first pipe for ls command
    pipein_fd = popen("ls", "r");

    if (pipein_fd == NULL)
    {
        perror("popen");
        exit(1);
    }

    // Open second pipe for sort command
    pipeout_fd = popen("sort", "w");

    if (pipeout_fd == NULL)
    {
        perror("popen");
        exit(1);
    }

    // Read output of ls and send to sort
    while (fgets(readbuf, 80, pipein_fd) != NULL)
    {
        fputs(readbuf, pipeout_fd);
    }

    // Close both pipes
    pclose(pipein_fd);
    pclose(pipeout_fd);

    return 0;
}
