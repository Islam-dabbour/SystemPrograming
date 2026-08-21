#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>

struct player {
    int numberOfAttempts;
    double timeTaken;
};

struct thread_data{
    int id;
    int target;
};

struct player *players;
struct thread_data *passedData;
pthread_mutex_t lock;

void initializePlayers(struct player *players, int n) {

    for (int i = 0; i < n; i++) {
        players[i].numberOfAttempts = 0;
        players[i].timeTaken = 0.0;
    }
}

// void playGame(struct player *p, int target, int id, int fd[2]) {

//     int file = open("result.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
//     if (file == -1) {
//         perror("open result.txt");
//         exit(EXIT_FAILURE);
//     }

//     srand(time(NULL));
//     struct timeval start, end; 
//     int guess = 0;
//     int tries = 0;

//     gettimeofday(&start, NULL); 

//     while (guess != target) {
//         guess = ((rand() ^ getpid()) % 100) + 1;
//         tries++;
//         //usleep(10000);
//     }

//     gettimeofday(&end, NULL); 

//     double timeTaken =(end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;

//     p->numberOfAttempts = tries;
//     p->timeTaken = timeTaken;
    
//     char result[128];
//     int resultLength = snprintf(result, sizeof result,
//                                 "Player %d: Attempts = %d, Time = %.6f seconds\n",
//                                 id, p->numberOfAttempts, p->timeTaken);
//     write(file, result, resultLength);
//     close(file);

//     close(fd[0]);
//     write(fd[1],p,sizeof(struct player));

//     // printf("Player %d: Attempts = %d, Time = %.2f seconds\n",
//     //            getpid(),
//     //            tries,
//     //            timeTaken);
//     exit(0);
// }

void *playGame(void *arg){
    //printf("d\n");

    struct thread_data *data = (struct thread_data *) (arg);

    unsigned int randomSeed = (unsigned int)time(NULL) ^
                              ((unsigned int)(data->id + 1) * 2654435761u);
    struct timeval start, end; 
    int guess = 0;
    int tries = 0;

    gettimeofday(&start, NULL); 
    int target = data->target;

    while (guess != target) {
        guess = (rand_r(&randomSeed) % 100) + 1;
        tries++;
        usleep(10000);
    }
    //printf("d\n");
    gettimeofday(&end, NULL); 

    double timeTaken =(end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;
    //printf("d\n");
    pthread_mutex_lock(&lock);
    players[data->id].numberOfAttempts = tries;
    players[data->id].timeTaken = timeTaken;
    pthread_mutex_unlock(&lock);
    
    // char result[128];
    // int resultLength = snprintf(result, sizeof result,
    //                             "Player %d: Attempts = %d, Time = %.6f seconds\n",
    //                             id, p->numberOfAttempts, p->timeTaken);
    // write(file, result, resultLength);
    // close(file);

    // close(fd[0]);
    // write(fd[1],p,sizeof(struct player));

    // printf("Player %d: Attempts = %d, Time = %.2f seconds\n",
    //            getpid(),
    //            tries,
    //            timeTaken);

    printf("Player: %d finished! Attempts: %d, Time: %f\n",data->id,tries,timeTaken);
    return NULL;

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

void printFinalWinner(int numberOfPlayers){
    int winnersArr[numberOfPlayers];

    for (int i = 0; i < numberOfPlayers; i++) {
        winnersArr[i] = i;
    }

    // Sort player indexes by completion time, then by attempts.
    for (int i = 0; i < numberOfPlayers - 1; i++) {
        for (int j = i + 1; j < numberOfPlayers; j++) {
            int first = winnersArr[i];
            int second = winnersArr[j];
            int shouldSwap = players[second].timeTaken < players[first].timeTaken ||
                             (players[second].timeTaken == players[first].timeTaken &&
                              players[second].numberOfAttempts <
                              players[first].numberOfAttempts);

            if (shouldSwap) {
                winnersArr[i] = second;
                winnersArr[j] = first;
            }
        }
    }

    printf("\nWinner Order:\n");
    for (int i = 0; i < numberOfPlayers; i++) {
        int player = winnersArr[i];
        printf("%d. Player %d: Attempts = %d, Time = %.2f seconds\n",
               i + 1,
               player + 1,
               players[player].numberOfAttempts,
               players[player].timeTaken);
    }
}

int main() {

    players = calloc(10, sizeof(*players));
    
    //int fd[2];
    //pipe(fd);
    srand(time(NULL));

    int max = 10;
    int min = 3;

    // int numberOfPlayers =
    //     (rand() % (max - min + 1)) + min;

    // int targetNumber =
    //     (rand() % 100) + 1;
    int *numberOfPlayers = malloc(sizeof(int));
    int *targetNumber = malloc(sizeof(int));
   
    *numberOfPlayers = (rand() % (max - min + 1)) + min;
    *targetNumber = (rand() % 100) + 1;

    passedData = calloc(*numberOfPlayers, sizeof(*passedData));


    pthread_t playersThreads[*numberOfPlayers];

    printf("Target Number: %d\n", *targetNumber);
    printf("Number Of Players: %d\n", *numberOfPlayers);

    pthread_mutex_init(&lock, NULL);
    initializePlayers(players, *numberOfPlayers);
    // for (int i = 0; i < *numberOfPlayers; i++) {

    //     // int pid = fork();

    //     // if(pid == 0){
    //     //     playGame(&players[i], *targetNumber, i + 1,fd);
    //     // }else{
    //     //     x = 1;
    //     //     continue;
    //     // }
        
    // }

    for ( int i = 0; i < *numberOfPlayers; i++){
        //printf("d\n");
        passedData[i].id = i;
        passedData[i].target = *targetNumber;
        pthread_create(&playersThreads[i], NULL, playGame, &passedData[i]);
    }
    for (int i = 0; i < *numberOfPlayers; i++){
        pthread_join(playersThreads[i], NULL);

    }
    // for(int i = 0; i < *numberOfPlayers; i++){
    //     wait(NULL);
    //     close(fd[1]);

    //     read(fd[0],&players[i],sizeof(struct player));
    // }

    printf("All Players Have Finished\n");
    /*if(x == 1){
            printResults(players, numberOfPlayers);
        }*/

    printResults(players, *numberOfPlayers);
    printFinalWinner(*numberOfPlayers);
    

    free(players);
    free(passedData);
    free(targetNumber);
    free(numberOfPlayers);
    pthread_mutex_destroy(&lock);
    return 0;
}