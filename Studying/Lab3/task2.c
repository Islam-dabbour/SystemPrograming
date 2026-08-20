#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int pid = fork();

    if(pid == 0){
        char *args[] = {"task2.c", NULL};
        execv("task1",args);
    }else {
        wait(NULL);
        printf("The Lancher Finished");
    }

    return 0 ;
}