#include "helpers.h"
#include <math.h> // for using "round" function

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // going through each pixel through rows and columns using nested for loops
        {
            // formula for greyscale. Average of each colour.
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00;
            // round the value to an integer figure.
            int rgbtAvg = round(average);
            image[i][j].rgbtRed = rgbtAvg;
            image[i][j].rgbtGreen = rgbtAvg;
            image[i][j].rgbtBlue = rgbtAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189);
            int sepiaGreen = round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168);
            int sepiaBlue = round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131);

            // check function to see if colour value is greater than 255. If greater, set to 255, max value.
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                // else, value is computed with the formula above.
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; // declaration of variable
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // storing image[i][j] into temporary location called temp[i][j].
            temp[i][j] = image[i][j];
            // image[i][width - j - 1] to take the original place of image[i][j]
            image[i][j] = image[i][width - j - 1];
            // value inside of temp[i][j], which is basically image[i][j], to go to the original place of image[i][width - j - 1].
            image[i][width - j - 1] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width]; // copy original image colour data
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imagecopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagecopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner
            if (i == 0 && j == 0)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i][j + 1].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j +
                                    1].rgbtRed) / 4.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;
                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i][j + 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j
                                      + 1].rgbtGreen) / 4.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;
                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i][j + 1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j +
                                     1].rgbtBlue) / 4.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // Bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i][j - 1].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j -
                                    1].rgbtRed) / 4.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;
                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i][j - 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j
                                      - 1].rgbtGreen) / 4.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;
                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i][j - 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j -
                                     1].rgbtBlue) / 4.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // Top right corner
            else if (i == 0 && j == width - 1)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i][j - 1].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j -
                                    1].rgbtRed) / 4.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;
                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i][j - 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j
                                      - 1].rgbtGreen) / 4.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;
                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i][j - 1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j -
                                     1].rgbtBlue) / 4.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // Bottom left corner
            else if (i == height - 1 && j == 0)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i][j + 1].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j +
                                    1].rgbtRed) / 4.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;
                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i][j + 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j
                                      + 1].rgbtGreen) / 4.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;
                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i][j + 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j +
                                     1].rgbtBlue) / 4.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // Left edge
            else if (i > 0 && i < height - 1 && j == 0)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j + 1].rgbtRed + imagecopy[i][j +
                                    1].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j + 1].rgbtRed) / 6.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;

                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j + 1].rgbtGreen + imagecopy[i][j
                                      + 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j + 1].rgbtGreen) / 6.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;

                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j + 1].rgbtBlue + imagecopy[i][j +
                                     1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j + 1].rgbtBlue) / 6.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // right edge
            else if (i > 0 && j == width - 1 && i < height - 1)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed + imagecopy[i][j -
                                    1].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i - 1][j - 1].rgbtRed) / 6.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;

                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen + imagecopy[i][j
                                      - 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i - 1][j - 1].rgbtGreen) / 6.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;

                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue + imagecopy[i][j -
                                     1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i - 1][j - 1].rgbtBlue) / 6.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // bottom edge
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j + 1].rgbtRed + imagecopy[i][j +
                                    1].rgbtRed + imagecopy[i][j - 1].rgbtRed + imagecopy[i - 1][j - 1].rgbtRed) / 6.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;

                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j + 1].rgbtGreen + imagecopy[i][j
                                      + 1].rgbtGreen + imagecopy[i][j - 1].rgbtGreen + imagecopy[i - 1][j - 1].rgbtGreen) / 6.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;

                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j + 1].rgbtBlue + imagecopy[i][j +
                                     1].rgbtBlue + imagecopy[i][j - 1].rgbtBlue + imagecopy[i - 1][j - 1].rgbtBlue) / 6.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // top edge
            else if (i == 0 && j > 0 && j < width - 1)
            {
                float averageRed = (imagecopy[i][j].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed + imagecopy[i][j +
                                    1].rgbtRed + imagecopy[i + 1][j + 1].rgbtRed + imagecopy[i][j - 1].rgbtRed) / 6.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;

                float averageGreen = (imagecopy[i][j].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen + imagecopy[i][j
                                      + 1].rgbtGreen + imagecopy[i + 1][j + 1].rgbtGreen + imagecopy[i][j - 1].rgbtGreen) / 6.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;

                float averageBlue = (imagecopy[i][j].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue + imagecopy[i][j +
                                     1].rgbtBlue + imagecopy[i + 1][j + 1].rgbtBlue + imagecopy[i][j - 1].rgbtBlue) / 6.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
            // centre
            else
            {
                float averageRed = (imagecopy[i - 1][j - 1].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j + 1].rgbtRed + imagecopy[i][j
                                    - 1].rgbtRed + imagecopy[i][j].rgbtRed + imagecopy[i][j + 1].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed + imagecopy[i + 1][j].rgbtRed
                                    + imagecopy[i + 1][j + 1].rgbtRed) / 9.0;
                int avgRed = round(averageRed);
                image[i][j].rgbtRed = avgRed;
                float averageGreen = (imagecopy[i - 1][j - 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j + 1].rgbtGreen +
                                      imagecopy[i][j - 1].rgbtGreen + imagecopy[i][j].rgbtGreen + imagecopy[i][j + 1].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen +
                                      imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j + 1].rgbtGreen) / 9.0;
                int avgGreen = round(averageGreen);
                image[i][j].rgbtGreen = avgGreen;
                float averageBlue = (imagecopy[i - 1][j - 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j + 1].rgbtBlue +
                                     imagecopy[i][j - 1].rgbtBlue + imagecopy[i][j].rgbtBlue + imagecopy[i][j + 1].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue +
                                     imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j + 1].rgbtBlue) / 9.0;
                int avgBlue = round(averageBlue);
                image[i][j].rgbtBlue = avgBlue;
            }
        }
    }
    return;
}
