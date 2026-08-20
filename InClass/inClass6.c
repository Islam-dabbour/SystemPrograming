// calculate avg + max in seperate threads 
#include <stdio.h>
#include <pthread.h>



int arr[10];

void *sum (void *args){
	int sum = 0;
	
	for(int j = 0;j<10; j++){
		sum  = sum + arr[j];
	}
	
	printf("sum: %d \n",sum);
}

void *avg (void *args){
	double avg = 0.0;
	int sum = 0;
	
	for(int j = 0;j<10;j++){
		
		sum  = sum + arr[j];
		
	}	
	
	avg = sum / 10;
	
	printf("avg: %f \n",avg);
}

int main(){

	for(int j = 0; j<10;j++){
		scanf("%d",&arr[j]);
	}

	pthread_t calcSum, calcAvg;
	
	int i = 1;
	
	pthread_create(&calcSum, NULL, sum, &i);
	
	i++;
	
	pthread_create(&calcAvg, NULL, avg, &i);
	
	pthread_join(calcSum, NULL);
	
	pthread_join(calcAvg, NULL);
	
	
	

	return 0;
}
