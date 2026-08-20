#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

struct player{
	
	int playerID;
	int numberOfAttempts;
	double timeTaken;
	int PlayerProcessID;
	
};

int main(){
	int fd[2];
	pipe(fd);
	srand(time(NULL));
	int numberOfPlayers;
	int randNum;
	
	int file = open("result.txt", O_WRONLY | O_CREAT, 0644);
	
	if(file< 0) {
		printf("Error\n");
	}
	
	printf("Enter The Number Of Players:");
	scanf("%d",&numberOfPlayers);
	
	printf("\nEnter The Target Numebr:");
	scanf("%d",&randNum);
	
	struct player players[numberOfPlayers];
	
	 for (int i = 0; i < numberOfPlayers; i++) {
    		//sprintf(players[i].name, "Player%d", i + 1);
    		players[i].playerID = 0;
    		players[i].PlayerProcessID = 0;
    		players[i].numberOfAttempts = 0;
    		players[i].timeTaken = 0.0;
										}
	
	printf("\nNumber Of Players: %d \n",numberOfPlayers);
	printf("Guessing Numebr : %d \n",randNum);
	
	 
										
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
    			
    			//printf("Player %d finished in %f sec \n",i,timeTaken);
    			//printf("Player %d PID %d\n",i,getpid());
    			//printf("Player %d Attempts: %d \n",i,numberOfAttempts);
    			
    			
    			
    			players[i].numberOfAttempts = numberOfAttempts;
    			players[i].timeTaken = timeTaken;
    			players[i].PlayerProcessID = getpid();
    			players[i].playerID = i;
    			
    			
    			//write(file,"Player %d | Attempts: %d | Time: %f sec \n",i,numberOfAttempts,timeTaken);
    			
    			char text[200];
    			
		int file2 = dup(file);
		
		int n = sprintf(text,"Player %d | Attempts: %d | Time: %f sec \n",i,numberOfAttempts, timeTaken);

		write(file2, text, n);
    			
    			close(fd[0]);
    			write(fd[1], &players[i], sizeof(players));
    			
    			exit(0);
		}
		
	
	}
	
	int winnerAttemp = 100;
	int winnerIndex = 0;
	
	printf("Print The data using pipe\n");
	for (int i = 0; i < numberOfPlayers; i++) {
		wait(NULL);
		//struct player playersR;
		close(fd[1]);
		read(fd[0], &players[i], sizeof(players)); 
		
		printf(">> PLayer %d finished!\n",players[i].playerID);
		printf("Attempts: %d\n",players[i].numberOfAttempts);
		printf("Time: %f\n",players[i].timeTaken);
		
		if(players[i].numberOfAttempts < 100) {
			winnerIndex = i;
			winnerAttemp = players[i].numberOfAttempts;
		}
    	
		}
		
		
	printf("\nPrint The data after reading from the file\n");
	
	char c;
	while(read(file, &c, 1)> 0){
		
		printf("%c",c);	
		
	}
	
	close(file);
		
	printf("All players have finished.\n");
	printf("=============\n");
	printf("Winner PLayer %d finished!\n",players[winnerIndex].playerID);
	printf("Attempts: %d\n",players[winnerIndex].numberOfAttempts);
	printf("Time: %f\n",players[winnerIndex].timeTaken);
	printf("=============\n");

	return 0;
}
