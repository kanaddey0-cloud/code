#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/socket.h>
#include <netdb.h>

#define PORT "27601"
#define IP "0.tcp.in.ngrok.io"

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // serv_addr.sin_family = AF_INET;
    // serv_addr.sin_port = htons(PORT);

    // inet_pton(AF_INET, IP, &serv_addr.sin_addr);  // IP -> binary bit’s (New)

    // // Connect to Server
    // if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    //     perror("connect failed");
    //     return 1;
    // }

struct addrinfo hints, *res;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;

if (getaddrinfo(IP, PORT, &hints, &res) != 0) {
    perror("getaddrinfo");
    return 1;
}
if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
    perror("connect failed");
    freeaddrinfo(res);
    return 1;
}
freeaddrinfo(res);

    // Send Message
    send(sock, "Hello TCP Server", 16, 0);     printf("Message Sent\n");

    // Receive Reply
    recv(sock, buffer, 1024, 0);               printf("Server Reply: %s\n", buffer);

    close(sock);
    return 0;
}
