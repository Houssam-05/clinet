#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 8080

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

    int socketfd, portNumber, n;
    struct sockaddr_in server_address;
    struct hostent *server;

    char buffer[256];

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (connect(socketfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        error("Connection Failed !!");
    }

    int number1, number2, choice, result;

    // Reading Server String
S:
    bzero(buffer, 256);
    number1 = read(socketfd, buffer, 256);
    if (number1 < 0)
    {
        error("Error reading From Socket");
    }

    printf("Server - %s\n", buffer);
    scanf("%d", &number1);
    write(socketfd, &number1, sizeof(int));

    bzero(buffer, 256);
    number2 = read(socketfd, buffer, 256);
    if (number2 < 0)
    {
        error("Error reading From Socket");
    }

    printf("Server - %s\n", buffer);
    scanf("%d", &number2);
    write(socketfd, &number2, sizeof(int));

    bzero(buffer, 256);
    choice = read(socketfd, buffer, 256);
    if (choice < 0)
    {
        error("Error reading From Socket");
    }

    printf("Server - %s\n", buffer);
    scanf("%d", &choice);
    write(socketfd, &choice, sizeof(int));

    if (choice == 5)
    {
        goto Q;
    }

    read(socketfd, &result, sizeof(int));
    printf("Server : The result is : %d\n", result);

    if (choice != 5)
    {
        goto S;
    }

Q:
    printf("You Have Selected to exit\nExit Successfully");
    close(socketfd);
    return 0;
}
