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
	char buffer[1024];
	struct sockaddr_in serv_addr, cli_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	portno = 1200;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =  htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
    printf("The Server is running ...\n");
	clilen = sizeof(cli_addr);
   	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	//the senario
    printf("The two numbers from the client are: ");
    float num1,num2;
    read(newsockfd,&num1,sizeof(num1));
    read(newsockfd,&num2,sizeof(num2));

    printf("%f %f\n",num1,num2);

    // multipication 
    float mult = num1 * num2;

    // sum 

    float sum = num1 + num2;

    printf("the oeprations finished sending to the client ... \n");

    write(newsockfd,&mult,sizeof(mult));
    write(newsockfd,&sum,sizeof(sum));


	close(newsockfd);
	
	close(sockfd);


 }