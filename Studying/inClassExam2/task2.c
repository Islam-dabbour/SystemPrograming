#include <stdio.h>
#include <pthread.h>

float num1, num2;

void *add()
{
    printf("Addition: %.2f\n", num1 + num2);
}

void *sub()
{
    printf("Subtraction: %.2f\n", num1 - num2);
}

void *mul()
{
    printf("Multiplication: %.2f\n", num1 * num2);
}

void *divide()
{
    if (num2 != 0)
        printf("Division: %.2f\n", num1 / num2);
}

int main()
{
    printf("Enter tow number: ");
    scanf("%f%f", &num1, &num2);
    pthread_t threadIDs[4];

    pthread_create(&threadIDs[1],NULL,add,NULL);
    pthread_create(&threadIDs[2],NULL,sub,NULL);
    pthread_create(&threadIDs[3],NULL,mul,NULL);
    pthread_create(&threadIDs[4],NULL,divide,NULL);

    pthread_join(threadIDs[1],NULL);
    pthread_join(threadIDs[2],NULL);
    pthread_join(threadIDs[3],NULL);
    pthread_join(threadIDs[4],NULL);
    // add();
    // sub();
    // mul();
    // divide();
    return 0;
}
