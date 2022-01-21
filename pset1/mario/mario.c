#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Nested for loops to print hashes
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < height; column++)
        {
            if (column < height - row - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        // For reverse hashes
        for (int col_rev = 0; col_rev < height; col_rev++)
        {
            if (row > col_rev - 1)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}