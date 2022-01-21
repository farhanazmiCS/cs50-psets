#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Checks program to ensure only ONE argument is inputted.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Declaring variables
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = NULL;

    // initiating jpeg count to zero
    int jpegCount = 0;

    // unsigned char variable represents a single byte.
    // tried using typedef uint8_t buffer[512] but compiler did not understand "buffer"
    unsigned char buffer[512];

    // 8 bytes (1 byte per char) ensures that enough bytes are used to store the names of the photos
    char jpegName[8];

    // If the file cannot be found --> NULL, print "File not found".
    if (input_file == NULL)
    {
        printf("File not found.\n");
        return 1;
    }

    // Reading one item every 512 byte buffer from the input file until end of file
    while (fread(buffer, sizeof(buffer), 1, input_file) == 1)
    {
        // If the following conditions are met,
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpegCount > 0)
            {
                fclose(output_file);
            }
            // Prints the name of the jpeg to a string
            sprintf(jpegName, "%03i.jpg", jpegCount);
            // Open image file jpegName
            output_file = fopen(jpegName, "w");
            // Writing the image file
            fwrite(buffer, sizeof(buffer), 1, output_file);
            // Adds to the counter
            jpegCount++;
        }
        else if (jpegCount > 0)
        {
            fwrite(buffer, sizeof(buffer), 1, output_file);
        }
    }
    if (input_file == NULL)
    {
        fclose(input_file);
    }
    if (output_file == NULL)
    {
        fclose(output_file);
    }
    return 0;
}
