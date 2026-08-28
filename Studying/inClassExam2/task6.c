#include <stdio.h>
#include <unistd.h>

float num1, num2;
float add(float a, float b)
{
    return a + b;
}

float sub(float a, float b)
{
    return a - b;
}

float mul(float a, float b)
{
    return a * b;
}

float divide(float a, float b)
{
    if (b != 0)
        return a / b;
    else
        return 0;
}

int main()
{
    
    printf("Enter tow number: ");
    scanf("%f%f", &num1, &num2);
    
    
    
    
    
     int pid1 = fork();

    if (pid1 == 0){

        printf("\nAddition: %.2f\n", add(num1, num2));

    }else {

        int pid2 = fork();

        if(pid2 == 0){

            printf("Subtraction: %.2f\n", sub(num1, num2));

        }else{

            int pid3 = fork();

            if(pid3 == 0){

                printf("Multiplication: %.2f\n", mul(num1, num2));

            }else{

                int pid4 = fork();

                if(pid4 == 0){

                   printf("Division: %.2f\n", divide(num1, num2));

                }
            }
        }
    }

    return 0;
}
