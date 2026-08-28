#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

void error(const char *msg){
perror(msg); 
exit(0); 
}

struct client_arg { int sock; };

void *client_handler(void *arg) {
  struct client_arg *c = arg;
  int client_sock = c->sock;
  free(c);

  char buffer[1024];
  int n;
  int targetNumber = (rand() % 100) + 1;
  int numberOfAttempts = 0;

  /* optional read of initial client message */
  bzero(buffer, 1024);
  n = read(client_sock, buffer, 1023);
  if (n > 0) {
    buffer[n] = '\0';
    printf("From Client: %s\n", buffer);
  }

  strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
  write(client_sock, buffer, strlen(buffer) + 1);

  while (1) {
    bzero(buffer, 1024);
    n = read(client_sock, buffer, 1023);
    if (n <= 0) break;
    buffer[n] = '\0';

    int guess = atoi(buffer);
    numberOfAttempts++;

    if (guess < targetNumber) {
      strcpy(buffer, "Your guess is too low. Try again.");
      printf("%d\n", guess);
      write(client_sock, buffer, strlen(buffer) + 1);
    } else if (guess > targetNumber) {
      strcpy(buffer, "Your guess is too high. Try again.");
      write(client_sock, buffer, strlen(buffer) + 1);
    } else {
      bzero(buffer, 1024);
      sprintf(buffer, "Congratulations! You've guessed the number %d in %d attempts.", targetNumber, numberOfAttempts);
      write(client_sock, buffer, strlen(buffer) + 1);
      break;
    }
  }

  close(client_sock);
  printf("[-]Client disconnected.\n");
  return NULL;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("You need to provide a port number in the program argument\n");
    exit(0);
  }

  srand(time(NULL));

  int port = atoi(argv[1]);
  printf("Port: %d\n", port);

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  int addr_size, n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0) {
    perror("[-] ERROR opening socket");
    exit(1);
  }
  printf("[+]TCP server socket created From Server Side.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0) {
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  while (1) {
    printf("Listening...\n");
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) error("ERROR on accept");

    printf("[+]Client connected.\n");

    struct client_arg *c = malloc(sizeof(*c));
    if (!c) {
      perror("malloc");
      close(client_sock);
      continue;
    }
    c->sock = client_sock;

    pthread_t tid;
    if (pthread_create(&tid, NULL, client_handler, c) != 0) {
      perror("pthread_create");
      close(client_sock);
      free(c);
      continue;
    }
    pthread_detach(tid);
  }

  close(server_sock);
  return 0;
}


