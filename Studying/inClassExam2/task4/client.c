#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int main(int argc, char *argv[])
{ int sockfd, portno, n;
   struct sockaddr_in serv_addr;
  // struct hostent *server;
   char buffer[1024];
   portno = 1200;
   sockfd = socket(AF_INET, SOCK_STREAM, 0); 
   //server = gethostbyname(argv[1]);
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port = htons(portno);
 connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

 float num1, num2;     

 printf("Enter two numbers to send them to the server: ");
 scanf("%f",&num1);
 scanf("%f",&num2);

 write(sockfd,&num1,sizeof(num1));
 write(sockfd,&num2,sizeof(num2));

 float sum, mult;

 read(sockfd, &mult,sizeof(mult));
 read(sockfd,&sum,sizeof(sum));

 printf("The multipcation result: %f \n",mult);
 printf("The summation result: %f\n",sum);

    close(sockfd);
} 