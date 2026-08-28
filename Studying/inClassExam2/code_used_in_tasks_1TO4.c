#include <stdio.h>
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
    add();
    sub();
    mul();
    divide();
    return 0;
}
