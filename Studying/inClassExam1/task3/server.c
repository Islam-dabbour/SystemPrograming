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
	clilen = sizeof(cli_addr);
   	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	//the senario
	printf("Charger Server is ON. . . .\n");
    int id = 0;
    read(newsockfd,&id,sizeof(id));
    int charge = 0;
    //printf("Mobile %d: \n",id);
    while (charge <=100){

        printf("Mobile %d: %3d%% \n",id, charge);
        fflush(stdout);
        //printf("testing 2 ... \n");
        sleep(1);
        charge += 20;
    }
    //printf("testing 3 ... \n");
    printf("Mobile %d: Fully charged! \n",id);
    bzero(buffer, 1024);
    strcpy(buffer, "Mobile Fully charged! \n");
    write(newsockfd,&buffer,sizeof(buffer));
	close(newsockfd);
	
	close(sockfd);


 }
