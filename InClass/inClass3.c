#include <stdio.h>
#include <unistd.h>


int main(){
	
	int num1 = 10, num2 = 20;
	int fd1[2];
	int fd2[2];
	
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
 	
 		close(fd1[0]);
 		int div = num2 / num1, mult = num1 * num2; 
 		
 		if(write(fd1[1], &div, sizeof(int) == -1) {
 			return 5; 
 		}
 		close(fd1[1]);
 		
 		
 		
 		
 	}

 return 0;
}
