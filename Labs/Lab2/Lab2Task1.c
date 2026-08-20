#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

struct player{
	
	char name[100];
	int numberOfAttempts;
	double timeTaken;
	int PlayerProcessID;
	
};

int main(){
	srand(time(NULL));
	int numberOfPlayers = (rand() % (10 - 3 + 1)) + 3;
	int randNum = (rand() % (100 - 1 + 1)) + 1;
	
	struct player players[numberOfPlayers];
	
	printf("Number Of Players: %d \n",numberOfPlayers);
	printf("Guessing Numebr : %d \n",randNum);
	
	 for (int i = 0; i < numberOfPlayers; i++) {
    		sprintf(players[i].name, "Player%d", i + 1);
    		players[i].PlayerProcessID = 0;
    		players[i].numberOfAttempts = 0;
    		players[i].timeTaken = 0.0;
										}
										
	for (int i = 0; i < numberOfPlayers; i++) {
	
		int p_pid = fork();
		
		if( p_pid == 0 ){
			srand(time(NULL) ^ getpid());
			int numberOfAttempts = 0;
			double timeTaken = 0.0;
			//time_t start, end;
			struct timeval start, end; 
    			int guess = 0;
    			int max = 100, min = 1;
    			gettimeofday(&start, NULL); 
    			while(guess != randNum){
        			numberOfAttempts++;
        			guess = (rand() % (max - min + 1)) + min;
        			usleep(10000);
    				}
    			gettimeofday(&end, NULL);

    			timeTaken = (end.tv_sec - start.tv_sec) +(end.tv_usec - start.tv_usec) / 1000000.0;
    			
    			printf("Player %d finished in %f sec \n",i,timeTaken);
    			printf("Player %d PID %d\n",i,getpid());
    			printf("Player %d Attempts: %d \n",i,numberOfAttempts);
    			
    			exit(0);
		}
		
	
	}
	
	for (int i = 0; i < numberOfPlayers; i++) {
    		wait(NULL);
		}
		
	printf("All players have finished.\n");
	

	return 0;
}
