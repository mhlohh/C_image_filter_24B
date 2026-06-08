#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            //Red
            if (round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue) >= 255 )
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            }
            //Green
            if (round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue) >= 255 )
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            }
            //Blue
            if (round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue) >= 255 )
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            }




        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int image_index = width-1;
    width = width/2;
    for(int i=0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int buff = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][image_index-j].rgbtRed;
            image[i][image_index-j].rgbtRed = buff;
            buff = image[i][j].rgbtBlue ;
            image[i][j].rgbtBlue = image[i][image_index-j].rgbtBlue;
            image[i][image_index-j].rgbtBlue = buff;
            buff = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][image_index-j].rgbtGreen;
            image[i][image_index-j].rgbtGreen = buff;


        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for(int i = 0; i <height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int array[] = {-1,0,1},sum[] = {0,0,0},counter = 0;
            for (int k = 0; k < 3; k++)
            {
                for(int l = 0; l < 3; l++ )
                {
                    if((((array[k] + i) >= 0) &&((array[l] + j) >= 0)) && (((i + array[k]) < height)&&((j + array[l]) < width)))
                    {
                        sum[0] += copy[i+array[k]][j+array[l]].rgbtRed;
                        sum[1] += copy[i+array[k]][j+array[l]].rgbtGreen;
                        sum[2] += copy[i+array[k]][j+array[l]].rgbtBlue;
                        counter ++;
                    }
                }

                image[i][j].rgbtRed = round(sum[0]/(float)counter);
                image[i][j].rgbtGreen = round(sum[1]/(float)counter);
                image[i][j].rgbtBlue = round(sum[2]/(float)counter);
            }
        }
    }
}
