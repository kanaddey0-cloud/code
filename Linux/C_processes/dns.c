#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() 
{
    struct hostent *host;
    
    // Resolving the hostname "localhost"
    host = gethostbyname("localhost");
    
    if (host == NULL) 
    {
        printf("Host not found\n");
        return 1;
    }
    
    // Printing the official host name
    printf("Official Host Name: %s\n", host->h_name);
    
    // Converting the network byte order IP address to a readable string format
    printf("IP Address: %s\n", inet_ntoa(*(struct in_addr *)host->h_addr));
    
    return 0;
}