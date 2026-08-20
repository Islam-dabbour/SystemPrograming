#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void playGame(struct player *p, int target) {

    time_t start, end;
    int guess = 0;
    int tries = 0;

    start = time(NULL);

    while (guess != target) {
        guess = (rand() % 100) + 1;
        tries++;
    }

    end = time(NULL);

    double timeTaken = difftime(end, start);

    p->numberOfAttempts = tries;
    p->timeTaken = timeTaken;
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

    for (int i = 0; i < numberOfPlayers; i++) {
        playGame(&players[i], targetNumber);
    }

    printResults(players, numberOfPlayers);

    return 0;
}