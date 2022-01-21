#include <stdio.h>
#include <ctype.h> // For check key validation
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check for number of arguments
    if (argc != 2)
    {
        printf("./substitution KEY\n");
        return 1;
    }

    // Declaring a new variable called KEY and mapping it into argv[1]
    string KEY = argv[1];

    // Check if KEY only contains 26 characters
    if (strlen(KEY) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if KEY characters only contains letters
    for (int check = 0; check < strlen(KEY); check++)
    {
        if (!isalpha(KEY[check]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check if KEY characters contains duplicate letters.
    // https://www.javatpoint.com/program-to-find-the-duplicate-characters-in-a-string
    for (int cursor = 0; cursor < strlen(KEY); cursor++)
    {
        int count_key = 1;
        for (int check = cursor + 1; check < strlen(KEY); check++)
        {
            if (tolower(KEY[cursor]) == tolower(KEY[check]))
            {
                count_key++;
                if (count_key > 1)
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }

    // Retrieve plaintext from user
    string PLAIN = get_string("plaintext: ");
    printf("ciphertext: ");

    // Uppercase "database"
    string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Lowercase "database"
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (int cursor_plain = 0; cursor_plain < strlen(PLAIN); cursor_plain++)
    {
        for (int cursor_alpha = 0; cursor_alpha < strlen(ALPHABET); cursor_alpha++)
        {
            if (PLAIN[cursor_plain] == ALPHABET[cursor_alpha])
            {
                for (int cursor_key = 0; cursor_key < strlen(KEY); cursor_key++)
                {
                    if (cursor_alpha == cursor_key)
                    {
                        printf("%c", toupper(KEY[cursor_key]));
                    }
                }
            }
            else if (PLAIN[cursor_plain] == alphabet[cursor_alpha])
            {
                for (int cursor_key = 0; cursor_key < strlen(KEY); cursor_key++)
                {
                    if (cursor_alpha == cursor_key)
                    {
                        printf("%c", tolower(KEY[cursor_key]));
                    }
                }
            }
        }
        if (isspace(PLAIN[cursor_plain]))
        {
            printf(" ");
        }
        else if (isdigit(PLAIN[cursor_plain]))
        {
            printf("%c", PLAIN[cursor_plain]);
        }
        else if (PLAIN[cursor_plain] == ',' || PLAIN[cursor_plain] == '.' || PLAIN[cursor_plain] == '!')
        {
            printf("%c", PLAIN[cursor_plain]);
        }
    }
    printf("\n");
    return 0;
}