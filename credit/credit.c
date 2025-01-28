#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long n;
    int length;
    char buffer[16];
    int counter = 0;
    int multi_add = 0;
    int added_add = 0;
    int sum = 0;

    do
    {
        n = get_long("Please enter your credit card number:");

        if (n < 0)
        {
            n = -n;
        }

        if (n == 0)
        {
            length = 1;
        }
        else
        {
            length = log10(n) + 1;
        }
        if (length < 13 || length > 16)
        {
            printf("INVALID\n");
            return 0;
        }
    }
    while (length < 13 || length > 16);

    sprintf(buffer, "%ld", n);
    size_t length_buffer = strlen(buffer);

    for (int i = length_buffer - 1; i >= 0; i--)
    {
        int digit = buffer[i] - '0';

        if (counter % 2 == 1)
        {
            int multiplied_value = digit * 2;

            if (multiplied_value > 9)
            {
                multi_add += (multiplied_value / 10) + (multiplied_value % 10);
            }
            else
            {
                multi_add += multiplied_value;
            }
        }
        else
        {
            added_add = digit + added_add;
        }

        counter++;
    }

    sum = multi_add + added_add;
    if (sum % 10 == 0)
    {
        while (n >= 100)
        {
            n /= 10;
        }
        if ((n == 34 || n == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if ((n == 51 | n == 52 | n == 53 | n == 54 | n == 55) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (n / 10 == 4 && (length == 13 || length == 16))
        {

            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
