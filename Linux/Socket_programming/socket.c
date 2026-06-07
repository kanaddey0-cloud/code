#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main()
{
    int sockfd;
    int opt = 1;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(
        sockfd,         // Socket on which the option will be set
        SOL_SOCKET,     // Level: socket-level options
        SO_REUSEADDR,   // Option name: allow reuse of local address/port
        &opt,           // Pointer to option value (1 = enable, 0 = disable)
        sizeof(opt)     // Size of the option value in bytes
    );
    printf("Socket Option SO_REUSEADDR Set Successfully\n");

    // Now Write Remaining SOCKET PROGRAMMING Code

    close(sockfd);
    return 0;
}