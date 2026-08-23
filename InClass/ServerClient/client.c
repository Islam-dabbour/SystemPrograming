#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    int number1, number2;
    int numbers[2];
    int result;

    portno = 1200;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    printf("This is the client window:\n");
    printf("Enter number 1: ");
    scanf("%d", &number1);

    printf("Enter number 2: ");
    scanf("%d", &number2);

    numbers[0] = number1;
    numbers[1] = number2;

    n = write(sockfd, numbers, sizeof(numbers));
    if (n < 0)
    {
        perror("write");
        close(sockfd);
        exit(1);
    }

    n = read(sockfd, &result, sizeof(result));
    if (n < 0)
    {
        perror("read");
        close(sockfd);
        exit(1);
    }

    printf("The result from the server is: %d\n", result);

    close(sockfd);
    return 0;
}
