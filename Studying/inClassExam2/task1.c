#include <stdio.h>
#include <unistd.h>

float num1, num2;

void add()
{
    printf("Addition: %.2f\n", num1 + num2);
}

void sub()
{
    printf("Subtraction: %.2f\n", num1 - num2);
}

void mul()
{
    printf("Multiplication: %.2f\n", num1 * num2);
}

void divide()
{
    if (num2 != 0)
        printf("Division: %.2f\n", num1 / num2);
}

int main()
{
    printf("Enter tow number: ");
    scanf("%f%f", &num1, &num2);
    // add();
    // sub();
    // mul();
    // divide();

    int pid1 = fork();

    if (pid1 == 0){

        add();

    }else {

        int pid2 = fork();

        if(pid2 == 0){

            sub();

        }else{

            int pid3 = fork();

            if(pid3 == 0){

                mul();

            }else{

                int pid4 = fork();

                if(pid4 == 0){

                    divide();

                }
            }
        }
    }
    return 0;
}
