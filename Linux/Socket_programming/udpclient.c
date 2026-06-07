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

void takeInput(struct Student *sd) {
    printf("Enter name: ");         scanf("%s", sd->name);
    printf("Enter CS marks: ");     scanf("%d", &sd->cs);
    printf("Enter IT marks: ");     scanf("%d", &sd->it);
    printf("Enter ECE marks: ");    scanf("%d", &sd->ece);
    printf("Enter MEC marks: ");    scanf("%d", &sd->mec);
    printf("Enter CE marks: ");     scanf("%d", &sd->ce);
}

int main()
{
    int sockfd;
    struct Student sd;
    struct Result rd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8080);

    takeInput(&sd);

    sendto(sockfd, &sd, sizeof(sd), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    recvfrom(sockfd, &rd, sizeof(rd), 0, NULL, NULL);

        printf("\n--- RESULT FROM SERVER ---\n");
        printf("Name       : %s\n", rd.name);
        printf("Total      : %d\n", rd.total);
        printf("Percentage : %.2f\n", rd.percentage);

    close(sockfd);
    return 0;
}
