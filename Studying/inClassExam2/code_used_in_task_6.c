#include <stdio.h>

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
    float num1, num2;
    printf("Enter tow number: ");
    scanf("%f%f", &num1, &num2);
    printf("\nAddition: %.2f\n", add(num1, num2));
    printf("Subtraction: %.2f\n", sub(num1, num2));
    printf("Multiplication: %.2f\n", mul(num1, num2));
    printf("Division: %.2f\n", divide(num1, num2));
    return 0;
}
