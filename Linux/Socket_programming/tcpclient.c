#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);  // IP -> binary bit’s

    // Connect to Server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Send Message
    send(sock, "Hello TCP Server", 12, 0);     printf("Message Sent\n");

    // Receive Reply
    recv(sock, buffer, 1024, 0);               printf("Server Reply: %s\n", buffer);

    close(sock);
    return 0;
}
