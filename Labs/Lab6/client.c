#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

void error(const char *msg){
perror(msg); 
exit(0); 
}

void *client_guess(void *arg){

  printf("[+]Connected to the server from client side.\n");

  bzero(buffer, 1024);
  strcpy(buffer, "HELLO, THIS IS CLIENT.");
  write(sockFD,buffer,strlen(buffer));
  bzero(buffer, 1024);
  read(sockFD,buffer,sizeof(buffer));
  printf("From Server: %s\n", buffer);

  while(1){
    // bzero(buffer, 1024);
    // read(sockFD, buffer, sizeof(buffer));
    // printf("From Server: %s\n", buffer);
    

    int guess;
    printf("Enter your guess: ");
    scanf("%d", &guess);
    char sendbuf[32];
    snprintf(sendbuf, sizeof(sendbuf), "%d", guess);
    write(sockFD, sendbuf, strlen(sendbuf) + 1);

   bzero(buffer, 1024);
   read(sockFD,buffer,sizeof(buffer));
   printf("From Server: %s\n", buffer);

  }

  
}

int main(int argc, char **argv){

  pthread_t thread_id;
  // char *ip = "127.0.0.1"; // this is used if you need to connect to a specific IP which should be passed to inet_addr(ip) 
   if(argc != 2){
    printf("You need to provide a port number in the program argument\n");
    exit(0);
  }
  int port = atoi(argv[1]);
  printf("Port: %d\n", port);

  int sockFD;
  struct sockaddr_in addr;
  char buffer[1024];
  
  sockFD = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFD < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created successfully from Client Side.\n");
  
/* This is used if you need to connect to a specific hostname
  struct hostent *server;
  server = gethostbyname("suhaib-VMware-Virtual-Platform");//argv[1]
   if (server == NULL){
	fprintf(stderr,"ERROR, no such host");
	exit(0);
   }
*/

memset(&addr, '\0', sizeof(addr));//fill the struct addr with null using memory set function to Avoid garbage values, you can use bzero also
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr =INADDR_ANY;// inet_addr(ip);
//bcopy((char *)server->h_addr,(char *)&addr.sin_addr.s_addr,server->h_length);  //This is used if you need to connect to a specific hostname
while(1){}
if(connect(sockFD, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
  error("ERROR connecting from client side");
  

  
}
  

  close(sockFD);
  printf("[-]Disconnected from the server.\n");

  return 0;

}
