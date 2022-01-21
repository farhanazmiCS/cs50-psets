#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int add_together = 0;
    int digit = 0;

    // Input credit card number from user
    long credit_number = get_long("Number: ");
    long credit_number_copy = credit_number;

    // Get the last digit and add it into add_together
    int last_digit = credit_number % 10;
    add_together += last_digit;

    // Skip to the 2nd last digit
    credit_number /= 10;

    // Retrieve 2nd last digit
    digit = credit_number % 10; // 8

    // Multiply the digit by 2 --> 8 * 2 = 16
    int multiplier = digit * 2; // 16

    // Get the second digit of the multiplier --> multiplier %= 10 (6)
    int no_2_digit = multiplier % 10; // 6

    // Add the last digit into add_together. add_together value is now = 6.
    add_together += no_2_digit; // 6

    // Divide the multiplier by 10 to get first digit. 16 / 10 = 1
    int no_1_digit = multiplier / 10; // 1

    // Add the multiplier value into add_together --> add_together (6) = add_together (6) + multiplier (1)
    add_together += no_1_digit;

    while (credit_number / 10 != 0)
    {

        // Skip to "other" digit
        credit_number /= 10;
        // Add the "other" digit to add_together
        add_together += credit_number % 10;
        // Skip to main digit
        credit_number /= 10;
        // Retrieve the main digit, but DON'T ADD to add_together, e.g 8
        digit = credit_number % 10;
        // Multiplies the digit by 2. (16)
        multiplier = digit * 2;
        // Get the 2nd digit of the multiply. (16 --> 6)
        int second_digit = multiplier % 10;
        // Add the 2nd digit (6) to add_together
        add_together += second_digit;
        // Multiplier divided by 10. 16 / 10 => (1)
        multiplier /= 10;
        // Add the (1) to add_together.
        add_together += multiplier;
    }

    if (add_together % 10 == 0)
    {
        if (credit_number_copy / 1000000000000000 == 4 || credit_number_copy / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else if (credit_number_copy / 10000000000000 == 34 || credit_number_copy / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (credit_number_copy / 100000000000000 == 51 || credit_number_copy / 100000000000000 == 52
                 || credit_number_copy / 100000000000000 == 53 || credit_number_copy / 100000000000000 == 54
                 || credit_number_copy / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
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
