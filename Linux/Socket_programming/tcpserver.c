#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
// #define IPv4 "127.0.0.1"

int main()
{
    int server_fd, client_fd;
    char buffer[1024] = {0};
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create Socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");    exit(EXIT_FAILURE);
    }

    // Define Address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { perror("bind"); exit(EXIT_FAILURE); }
    
    if (listen(server_fd, 3) < 0) { perror("listen"); exit(EXIT_FAILURE); }      
    printf("Server waiting for connection...\n");

    size_t client_count = 0;
    while(1)
    {
        // Accept Client
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

        // Receive Message
        recv(client_fd, buffer, 1024, 0);               printf("\nClient %zu Message: %s\n", ++client_count, buffer);

        // Send Reply
        memset(buffer, 0, sizeof(buffer)); // 👈 CLEAN BUFFER
        sprintf(buffer, "You are TCP Client %zu", client_count);
        send(client_fd, buffer, strlen(buffer), 0);     printf("Reply Sent to Client %zu\n", client_count);

        close(client_fd);
    }
    close(server_fd);
    return 0;
}
