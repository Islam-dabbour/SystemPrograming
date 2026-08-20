#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

struct player {
    int numberOfAttempts;
    double timeTaken;
};

struct player players[10];

void initializePlayers(struct player *players, int n) {

    for (int i = 0; i < n; i++) {
        players[i].numberOfAttempts = 0;
        players[i].timeTaken = 0.0;
    }
}

void playGame(struct player *p, int target, int id, int fd[2]) {
    srand(time(NULL));
    struct timeval start, end; 
    int guess = 0;
    int tries = 0;

    gettimeofday(&start, NULL); 

    while (guess != target) {
        guess = ((rand() ^ getpid()) % 100) + 1;
        tries++;
        //usleep(10000);
    }

    gettimeofday(&end, NULL); 

    double timeTaken =(end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;

    p->numberOfAttempts = tries;
    p->timeTaken = timeTaken;
    
    close(fd[0]);

    write(fd[1],p,sizeof(struct player));

    // printf("Player %d: Attempts = %d, Time = %.2f seconds\n",
    //            getpid(),
    //            tries,
    //            timeTaken);
    exit(0);
}

void printResults(struct player *players, int n) {

    printf("\nPlayer Results:\n");

    for (int i = 0; i < n; i++) {
        printf("Player %d: Attempts = %d, Time = %.2f seconds\n",
               i + 1,
               players[i].numberOfAttempts,
               players[i].timeTaken);
    }
}

int main() {
    int fd[2];
    pipe(fd);
    srand(time(NULL));

    int max = 10;
    int min = 3;

    int numberOfPlayers =
        (rand() % (max - min + 1)) + min;

    int targetNumber =
        (rand() % 100) + 1;

    printf("Target Number: %d\n", targetNumber);
    printf("Number Of Players: %d\n", numberOfPlayers);

    initializePlayers(players, numberOfPlayers);
    int x = 0;
    for (int i = 0; i < numberOfPlayers; i++) {

        int pid = fork();

        if(pid == 0){
            playGame(&players[i], targetNumber, i + 1,fd);
        }else{
            x = 1;
            continue;
        }
        
    }

    for(int i = 0; i < numberOfPlayers; i++){
        wait(NULL);
        close(fd[1]);

        read(fd[0],&players[i],sizeof(struct player));
    }

    printf("All Players Have Finished");
    /*if(x == 1){
            printResults(players, numberOfPlayers);
        }*/

    printResults(players, numberOfPlayers);
    

    return 0;
}