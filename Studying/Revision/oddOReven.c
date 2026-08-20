#include <stdio.h>



int main() {
    

    int numberEnterd;

    printf("Enter your number to be tested: ");
    scanf("%d",&numberEnterd);

    if(numberEnterd / 2 > 0){
        printf("The number is odd");

    }else {
        printf("The numebr is even");
    }

    return 0;
}