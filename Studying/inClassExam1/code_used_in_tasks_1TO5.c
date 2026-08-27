#include <stdio.h>
#include <unistd.h>

void charge_mobile(int id){

    int charge = 0;
    while (charge <=100){

        printf("\rMobile %d: %3d%%",id, charge);
        sleep(1);
        charge += 20;
    }

    printf("\rMobile %d: Fully charged! \n",id);
}

int main(){

    int n;
    printf("Enter the number of mobiles: ");
    scanf("%d",&n);

    for(int i = 1;i<=n;i++){
        charge_mobile(i);
    }

    return 0;
}