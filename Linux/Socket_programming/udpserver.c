#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

struct Student {
    char name[50];
    int cs, it, ece, mec, ce;
};

struct Result {
    char name[50];
    int total;
    float percentage;
};

int main()
{
    int sockfd;
    struct Student sd;
    struct Result rd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("UDP Server Waiting...\n");

    len = sizeof(cliaddr);
    recvfrom(sockfd, &sd, sizeof(sd), 0, (struct sockaddr *)&cliaddr, &len);
//     OS fills cliaddr with the sender's address.
//        Client IP   = 192.168.0.50
//        Client Port = 54321

        printf("\nMarks Received by: %s\n", sd.name);
        printf("CS  : %d\n", sd.cs);
        printf("IT  : %d\n", sd.it);
        printf("ECE : %d\n", sd.ece);
        printf("MEC : %d\n", sd.mec);
        printf("CE  : %d\n", sd.ce);

    // calculate
    rd.total = sd.cs + sd.it + sd.ece + sd.mec + sd.ce;
    rd.percentage = (rd.total / 500.0) * 100;
    strcpy(rd.name, sd.name);

    sendto(sockfd, &rd, sizeof(rd), 0, (struct sockaddr *)&cliaddr, len);
//     How does the server know where to send the reply? From cliaddr.

    printf("Result sent to client %s.\n", sd.name);

    close(sockfd);
    return 0;
}
