#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidLuhnNumber(long number)
{
    int sum = 0;
    bool alternate = false;

    while (number > 0)
    {
        int digit = number % 10;

        if (alternate)
        {
            digit *= 2;

            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;
        alternate = !alternate;
        number /= 10;
    }

    return (sum % 10 == 0);
}

int main()
{
    long long number;

    printf("Enter a number: ");
    scanf("%lld", &number);

    if (isValidLuhnNumber(number))
    {
        printf("Valid Luhn number\n");
    }
    else
    {
        printf("Invalid Luhn number\n");
    }

    return 0;
}
// clang main.c -o main
// ./main
// 45320151128336