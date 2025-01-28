#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = round((red + blue + green) / 3.0);
            image[i][j].rgbtRed = round((red + blue + green) / 3.0);
            image[i][j].rgbtGreen = round((red + blue + green) / 3.0);

            if (j == 0)
            {
                printf("%i ", image[i][j].rgbtBlue);
                printf("%i ", image[i][j].rgbtRed);
                printf("%i ", image[i][j].rgbtGreen);
            }
        }
        printf("\n");
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //?reversing every row to reflect the image
    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int end = width - 1;
        while (start < end)
        {
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;

            start++;
            end--;

            if (start == 0)
            {
                printf("%i ", image[i][start].rgbtBlue);
                printf("%i ", image[i][start].rgbtRed);
                printf("%i ", image[i][start].rgbtGreen);
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if (i == 0 || j == 0 || j == width-1 || i == height -1)
            // {
            //? checking the neighboring pixels and avoiding if they are out of bond
            //? increasing the count if valid to take correct average
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0; // Keep track of valid pixels

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    // Check if current pixel is within bounds
                    if (currentX >= 0 && currentX < height && currentY >= 0 && currentY < width)
                    {
                        sumRed += image[currentX][currentY].rgbtRed;
                        sumGreen += image[currentX][currentY].rgbtGreen;
                        sumBlue += image[currentX][currentY].rgbtBlue;
                        count++;
                    }
                }
            }

            temp[i][j].rgbtRed = round((float) sumRed / count);
            temp[i][j].rgbtBlue = round((float) sumBlue / count);
            temp[i][j].rgbtGreen = round((float) sumGreen / count);

            printf("%i ", image[i][j].rgbtBlue);
            printf("%i ", image[i][j].rgbtRed);
            printf("%i ", image[i][j].rgbtGreen);
        }
        printf("\n");
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxkernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int gykernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    //?doing the similar to blur but this time neighboring pixels are multiplied using
    //?gx and gy kernel and getting the value according to the gx^2 and gy^2
    //? remember to user multiplication and getting squire root method trying this ^
    //? didnt work
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int redgx = 0;
            int redgy = 0;
            int bluegx = 0;
            int bluegy =0;
            int greengx = 0;
            int greengy = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;


                    if (currentX >= 0 && currentX < height && currentY >= 0 && currentY < width)
                    {
                        redgx += image[currentX][currentY].rgbtRed * gxkernel[x + 1][y + 1];
                        bluegx += image[currentX][currentY].rgbtBlue * gxkernel[x + 1][y + 1];
                        greengx += image[currentX][currentY].rgbtGreen * gxkernel[x + 1][y + 1];

                        redgy += image[currentX][currentY].rgbtRed * gykernel[x + 1][y + 1];
                        bluegy += image[currentX][currentY].rgbtBlue * gykernel[x + 1][y + 1];
                        greengy += image[currentX][currentY].rgbtGreen * gykernel[x + 1][y + 1];
                    }
                }
            }

            int red = round(sqrt(redgx * redgx + redgy * redgy));
            int blue = round(sqrt(bluegx * bluegx + bluegy * bluegy));
            int green = round(sqrt(greengx * greengx + greengy * greengy));

            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;

            // if (i == 0 || j == 0 || j == width-1 || i == height -1)
            // {
            // BYTE red = (

            // int redgx =
            //      (image[i-1][j-1].rgbtRed * -1)
            //     +(image[i][j-1].rgbtRed * -2)
            //     +(image[i+1][j-1].rgbtRed * -1)
            //     +(image[i-1][j].rgbtRed * 0)
            //     +(image[i][j].rgbtRed * 0)
            //     +(image[i+1][j].rgbtRed * 0)
            //     +(image[i-1][j+1].rgbtRed * 1)
            //     +(image[i][j+1].rgbtRed * 2)
            //     +(image[i+1][j+1].rgbtRed * 1)
            //     ;

            // int redgy =
            //      (image[i-1][j-1].rgbtRed * -1)
            //     +(image[i][j-1].rgbtRed * 0)
            //     +(image[i+1][j-1].rgbtRed * 1)
            //     +(image[i-1][j].rgbtRed * -2)
            //     +(image[i][j].rgbtRed * 0)
            //     +(image[i+1][j].rgbtRed * 2)
            //     +(image[i-1][j+1].rgbtRed * -1)
            //     +(image[i][j+1].rgbtRed * 0)
            //     +(image[i+1][j+1].rgbtRed * 1)
            //     ;

            // BYTE red = sqrt((redgx*redgx) + (redgy*redgy));
            // red = round(red);
            // if (red > 255)
            // {
            //     red = 255;
            // }else if (red<0)
            // {
            //     red = 0;
            // }

            // int bluegx =
            //      (image[i-1][j-1].rgbtBlue * -1)
            //     +(image[i][j-1].rgbtBlue * -2)
            //     +(image[i+1][j-1].rgbtBlue * -1)
            //     +(image[i-1][j].rgbtBlue * 0)
            //     +(image[i][j].rgbtBlue * 0)
            //     +(image[i+1][j].rgbtBlue * 0)
            //     +(image[i-1][j+1].rgbtBlue * 1)
            //     +(image[i][j+1].rgbtBlue * 2)
            //     +(image[i+1][j+1].rgbtBlue * 1)
            //     ;

            // int bluegy =
            //      (image[i-1][j-1].rgbtBlue * -1)
            //     +(image[i][j-1].rgbtBlue * 0)
            //     +(image[i+1][j-1].rgbtBlue * 1)
            //     +(image[i-1][j].rgbtBlue * -2)
            //     +(image[i][j].rgbtBlue * 0)
            //     +(image[i+1][j].rgbtBlue * 2)
            //     +(image[i-1][j+1].rgbtBlue * -1)
            //     +(image[i][j+1].rgbtBlue * 0)
            //     +(image[i+1][j+1].rgbtBlue * 1)
            //     ;

            // BYTE blue = sqrt((bluegx*bluegx) + (bluegy *bluegy));
            // blue = round(blue);
            // if (blue > 255)
            // {
            //     blue = 255;
            // }else if (red<0)
            // {
            //     blue = 0;
            // }

            // int greengx =
            //      (image[i-1][j-1].rgbtGreen * -1)
            //     +(image[i][j-1].rgbtGreen * -2)
            //     +(image[i+1][j-1].rgbtGreen * -1)
            //     +(image[i-1][j].rgbtGreen * 0)
            //     +(image[i][j].rgbtGreen * 0)
            //     +(image[i+1][j].rgbtGreen * 0)
            //     +(image[i-1][j+1].rgbtGreen * 1)
            //     +(image[i][j+1].rgbtGreen * 2)
            //     +(image[i+1][j+1].rgbtGreen * 1)
            //     ;

            // int greengy =
            //      (image[i-1][j-1].rgbtGreen * -1)
            //     +(image[i][j-1].rgbtGreen * 0)
            //     +(image[i+1][j-1].rgbtGreen * 1)
            //     +(image[i-1][j].rgbtGreen * -2)
            //     +(image[i][j].rgbtGreen * 0)
            //     +(image[i+1][j].rgbtGreen * 2)
            //     +(image[i-1][j+1].rgbtGreen * -1)
            //     +(image[i][j+1].rgbtGreen * 0)
            //     +(image[i+1][j+1].rgbtGreen * 1)
            //     ;

            // BYTE green =sqrt( (greengx*greengx) + (greengy*greengy));
            // green = round(green);
            // if (green > 255)
            // {
            //     green = 255;
            // }else if (green<0)
            // {
            //     green = 0;
            // }

            // //BYTE blue =
            // (image[i-1][j-1].rgbtBlue+image[i][j-1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i][j].rgbtBlue+image[i+1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue)/9;
            // //BYTE green =
            // (image[i-1][j-1].rgbtGreen+image[i][j-1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i][j].rgbtGreen+image[i+1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen)/9;

            // temp[i][j].rgbtRed = red ;
            // temp[i][j].rgbtBlue = blue ;
            // temp[i][j].rgbtGreen = green;
            //}

            printf("%i ", temp[i][j].rgbtBlue);
            printf("%i ", temp[i][j].rgbtRed);
            printf("%i ", temp[i][j].rgbtGreen);
        }
        printf("\n");
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
