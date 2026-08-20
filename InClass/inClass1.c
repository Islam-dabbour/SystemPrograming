#include <stdio.h>
#include <unistd.h>


int main(){
	
	int num1 = 10, num2 = 20;
 	int p_pid = fork();
 	
 	
 	if(p_pid >0){
 		
 		int p_pid2 = fork();
 		
 		if(p_pid2>0){
 		printf("This is process 1\n");
 		printf("the sum is: %d \n",num1 + num2);
 		}else{
 		
 		printf("this is process 2\n");
 		printf("the sub is: %d \n",num2 - num1);
 		}
 	}else {
 		int p_pid3 = fork();
 		
 		if(p_pid3 >0){
 		printf("this is process 3\n");
 		printf("the multip is: %d \n",num1 * num2);
 		}else{
 		printf("this is process 4\n");
 		printf("the div is: %d \n",num2 / num1);
 		}
 	}

 return 0;
}
