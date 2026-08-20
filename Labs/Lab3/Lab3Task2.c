#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    int p_pid = fork();

    if (p_pid == 0) {

        printf("Child Process Started...\n");

        execl("./Lab3Task1", "Lab3Task1", NULL);

        printf("Exec Failed!\n");
        exit(1);
    }

    else {

        wait(NULL);

        printf("\nParent Process:\n");
        printf("Child has finished running the Guessing Game.\n");
        printf("Program Finished.\n");
    }

    return 0;
}
