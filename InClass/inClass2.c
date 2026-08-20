#include <stdio.h>
#include <unistd.h>

int main(){
	
	int p_pid = fork();
	
	if(p_pid > 0){
	printf("This is a test for the exec system call: \n");
	
	

	execl("/bin/ping","/bin/ping","-c","4","google.com",NULL);
	
	

	}else{
			char* args[]={"inClass2.o",NULL};
  			execv("inCLass2.o",args);
 			 printf("back to inClass2.c");

	}
	
	



	return 0;
}
