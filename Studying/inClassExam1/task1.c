#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void charge_mobile(int id){

    int charge = 0;
    //printf("Mobile %d: \n",id);
    while (charge <=100){

        printf("Mobile %d: %3d%% \n",id, charge);
        fflush(stdout);
        //printf("testing 2 ... \n");
        sleep(1);
        charge += 20;
    }
    //printf("testing 3 ... \n");
    printf("Mobile %d: Fully charged! \n",id);
    
}

int main(){

    int n;
    printf("Enter the number of mobiles: ");
    scanf("%d",&n);

    for(int i = 1;i<=n;i++){

        int pid = fork();

        if(pid == 0){
            charge_mobile(i);
            _exit(0);
        }else{
            continue;
        }
        
    }

    for(int i = 0;i <n;i++){
        wait(NULL);
    }

    return 0;
}