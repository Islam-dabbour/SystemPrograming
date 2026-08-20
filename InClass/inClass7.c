// make an arrray and fill it randomly --> 10k 
// find the avg using thread 
// make sure to prevent race condition 1 and 2 
// the main thread find the max value of the arr
// whats the sutiable number of threads depending on the array size

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int arr[1000];

void * findAvg(void * NumberOf){
	int * numberOf = (int *) (NumberOf);
	int sum = 0;
	double avg;
	
	for(int i = 0;i<1000; i++){
	
	sum = arr[i] + sum;
	
	}
	
	avg = sum / *numberOf; 
	
	printf("avg: %f \n", avg);
	
}

int main(){

	int numberOf = 1000;
	for(int i = 0;i<1000;i++){
	
	
		arr[i] = i;
	}
	
	pthread_t th1;
	
	pthread_create(&th1, NULL, findAvg, &numberOf);
	
	pthread_join(th1, NULL);
	
	int max = 0;
	for(int i = 0; i<1000;i++){
	
		if(max < arr[i]){
			max = arr[i];
		}
	}
	
	printf("max value = %d",max);
	
	return 0; 
}
