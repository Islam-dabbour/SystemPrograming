#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, clilen, n;
    int numbers[2];
    int result;
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    portno = 1200;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
    
        printf("Server is waiting for a connection...\n");
        printf("Server is working ...\n");

        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("accept");
            //close(sockfd);
            exit(1);
        }

        n = read(newsockfd, numbers, sizeof(numbers));
        if (n < 0)
        {
            perror("read");
            close(newsockfd);
            //close(sockfd);
            exit(1);
        }

        result = numbers[0] + numbers[1];

        n = write(newsockfd, &result, sizeof(result));
        if (n < 0)
        {
            perror("write");
            close(newsockfd);
            //close(sockfd);
            exit(1);
        }

        printf("Server received %d and %d. Result = %d\n", numbers[0], numbers[1], result);

        close(newsockfd);

    }
    close(sockfd);
    return 0;
}