#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int every_other_digit(long credit_card);
int number_of_digits(long credit_card);
bool isValidAmex(long credit_card, int numDigit);
bool isValidMasterCard(long credit_card, int numDigit);
bool isValidVisa(long credit_card, int numDigit);

int main(void)
{
    long credit_card;
    printf("Number: ");
    scanf("%ld", &credit_card);

    int sum_every_other_digit = every_other_digit(credit_card);
    int numDigits = number_of_digits(credit_card);
    bool amex = isValidAmex(credit_card, numDigits);
    bool master_card = isValidMasterCard(credit_card, numDigits);
    bool visa = isValidVisa(credit_card, numDigits);

    if (sum_every_other_digit % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (amex)
    {
        printf("AMEX\n");
    }
    else if (master_card)
    {
        printf("MASTERCARD\n");
    }
    else if (visa)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool isValidAmex(long credit_card, int numDigits)
{
    int first_two_digits = credit_card / pow(10, 13);
    if ((numDigits == 15) && ((first_two_digits == 34) || (first_two_digits == 37)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidMasterCard(long credit_card, int numDigits)
{
    int first_two_digits = credit_card / pow(10, 14);
    if ((numDigits == 16) && ((first_two_digits > 50) && (first_two_digits < 56)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValidVisa(long credit_card, int numDigits)
{
    if (numDigits == 13)
    {
        int first_digit = credit_card / pow(10, 12);
        if (first_digit == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (numDigits == 16)
    {
        int first_digit = credit_card / pow(10, 15);
        if (first_digit == 4)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int number_of_digits(long credit_card)
{
    int count = 0;
    while (credit_card > 0)
    {
        count++;
        credit_card = credit_card / 10;
    }
    return count;
}

int every_other_digit(long credit_card)
{
    int sum = 0;
    bool isAlternateDigit = false;
    while (credit_card > 0)
    {
        int last_digit = credit_card % 10;
        if (isAlternateDigit)
        {
            int multiplied_digit = last_digit * 2;
            if (multiplied_digit >= 10)
            {
                multiplied_digit = (multiplied_digit % 10) + (multiplied_digit / 10);
            }
            sum += multiplied_digit;
        }
        else
        {
            sum += last_digit;
        }

        isAlternateDigit = !isAlternateDigit;
        credit_card /= 10;
    }
    return sum;
}
