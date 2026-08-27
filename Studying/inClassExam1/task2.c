#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *charge_mobile(void *arg){

    int id = (int)(long)arg;
    printf("%d \n",id);

    
    int charge = 0;
    while (charge <=100){

        printf("Mobile %d: %3d%% \n",id, charge);
        sleep(1);
        charge += 20;
    }

    printf("Mobile %d: Fully charged! \n",id);
    return NULL;
}

int main(){

    int n;
    printf("Enter the number of mobiles: ");
    scanf("%d",&n);

    pthread_t threadID[n];

    for(int i = 0;i<n;i++){
        //charge_mobile(i);
        pthread_create(&threadID[i],NULL,charge_mobile,(void *)(long)(i + 1));

    }

    for(int i = 0; i <n;i++){
        pthread_join(threadID[i],NULL);
    }

    return 0;
}