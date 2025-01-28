#include "helpers.h"
#include <stdio.h>
#include <math.h>

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
            image[i][j].rgbtBlue = round((red +blue + green) /3.0);
            image[i][j].rgbtRed = round((red +blue + green) /3.0);
            image[i][j].rgbtGreen = round((red +blue + green) /3.0);

            if(j==0)
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

    for (int i = 0; i<height; i++)
    {
        int start = 0;
        int end = width-1;
        while(start < end)
        {
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;

            start++;
            end--;

            if(start==0)
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
    for (int i = 1; i < height-1; i++)
        {
            for (int j = 1; j < width-1; j++)
            {
                // if (i == 0 || j == 0 || j == width-1 || i == height -1)
                // {
                    BYTE red = (image[i-1][j-1].rgbtRed+image[i][j-1].rgbtRed+image[i+1][j-1].rgbtRed+image[i-1][j].rgbtRed+image[i][j].rgbtRed+image[i+1][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed)/9;
                    BYTE blue = (image[i-1][j-1].rgbtBlue+image[i][j-1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i][j].rgbtBlue+image[i+1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue)/9;
                    BYTE green =  (image[i-1][j-1].rgbtGreen+image[i][j-1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i][j].rgbtGreen+image[i+1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen)/9;

                    temp[i][j].rgbtRed = red ;
                    temp[i][j].rgbtBlue = blue ;
                    temp[i][j].rgbtGreen = green;
                //}

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
        RGBTRIPLE temp[height][width];
        for (int i = 1; i < height-1; i++)
        {
            for (int j = 1; j < width-1; j++)
            {
                // if (i == 0 || j == 0 || j == width-1 || i == height -1)
                // {
                    //BYTE red = (

                    int redgx =
                         (image[i-1][j-1].rgbtRed * -1)
                        +(image[i][j-1].rgbtRed * -2)
                        +(image[i+1][j-1].rgbtRed * -1)
                        +(image[i-1][j].rgbtRed * 0)
                        +(image[i][j].rgbtRed * 0)
                        +(image[i+1][j].rgbtRed * 0)
                        +(image[i-1][j+1].rgbtRed * 1)
                        +(image[i][j+1].rgbtRed * 2)
                        +(image[i+1][j+1].rgbtRed * 1)
                        ;

                    int redgy =
                         (image[i-1][j-1].rgbtRed * -1)
                        +(image[i][j-1].rgbtRed * 0)
                        +(image[i+1][j-1].rgbtRed * 1)
                        +(image[i-1][j].rgbtRed * -2)
                        +(image[i][j].rgbtRed * 0)
                        +(image[i+1][j].rgbtRed * 2)
                        +(image[i-1][j+1].rgbtRed * -1)
                        +(image[i][j+1].rgbtRed * 0)
                        +(image[i+1][j+1].rgbtRed * 1)
                        ;

                    BYTE red = sqrt((redgx*redgx) + (redgy*redgy));
                    red = round(red);
                    if (red > 255)
                    {
                        red = 255;
                    }else if (red<0)
                    {
                        red = 0;
                    }


                    int bluegx =
                         (image[i-1][j-1].rgbtBlue * -1)
                        +(image[i][j-1].rgbtBlue * -2)
                        +(image[i+1][j-1].rgbtBlue * -1)
                        +(image[i-1][j].rgbtBlue * 0)
                        +(image[i][j].rgbtBlue * 0)
                        +(image[i+1][j].rgbtBlue * 0)
                        +(image[i-1][j+1].rgbtBlue * 1)
                        +(image[i][j+1].rgbtBlue * 2)
                        +(image[i+1][j+1].rgbtBlue * 1)
                        ;

                    int bluegy =
                         (image[i-1][j-1].rgbtBlue * -1)
                        +(image[i][j-1].rgbtBlue * 0)
                        +(image[i+1][j-1].rgbtBlue * 1)
                        +(image[i-1][j].rgbtBlue * -2)
                        +(image[i][j].rgbtBlue * 0)
                        +(image[i+1][j].rgbtBlue * 2)
                        +(image[i-1][j+1].rgbtBlue * -1)
                        +(image[i][j+1].rgbtBlue * 0)
                        +(image[i+1][j+1].rgbtBlue * 1)
                        ;

                    BYTE blue = sqrt((bluegx*bluegx) + (bluegy *bluegy));
                    blue = round(blue);
                    if (blue > 255)
                    {
                        blue = 255;
                    }else if (red<0)
                    {
                        blue = 0;
                    }


                    int greengx =
                         (image[i-1][j-1].rgbtGreen * -1)
                        +(image[i][j-1].rgbtGreen * -2)
                        +(image[i+1][j-1].rgbtGreen * -1)
                        +(image[i-1][j].rgbtGreen * 0)
                        +(image[i][j].rgbtGreen * 0)
                        +(image[i+1][j].rgbtGreen * 0)
                        +(image[i-1][j+1].rgbtGreen * 1)
                        +(image[i][j+1].rgbtGreen * 2)
                        +(image[i+1][j+1].rgbtGreen * 1)
                        ;

                    int greengy =
                         (image[i-1][j-1].rgbtGreen * -1)
                        +(image[i][j-1].rgbtGreen * 0)
                        +(image[i+1][j-1].rgbtGreen * 1)
                        +(image[i-1][j].rgbtGreen * -2)
                        +(image[i][j].rgbtGreen * 0)
                        +(image[i+1][j].rgbtGreen * 2)
                        +(image[i-1][j+1].rgbtGreen * -1)
                        +(image[i][j+1].rgbtGreen * 0)
                        +(image[i+1][j+1].rgbtGreen * 1)
                        ;

                    BYTE green =sqrt( (greengx*greengx) + (greengy*greengy));
                    green = round(green);
                    if (green > 255)
                    {
                        green = 255;
                    }else if (green<0)
                    {
                        green = 0;
                    }

                    //BYTE blue = (image[i-1][j-1].rgbtBlue+image[i][j-1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i][j].rgbtBlue+image[i+1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue)/9;
                    //BYTE green =  (image[i-1][j-1].rgbtGreen+image[i][j-1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i][j].rgbtGreen+image[i+1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen)/9;

                    temp[i][j].rgbtRed = red ;
                    temp[i][j].rgbtBlue = blue ;
                    temp[i][j].rgbtGreen = green;
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
