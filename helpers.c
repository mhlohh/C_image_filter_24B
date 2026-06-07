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
            //edge case top left corner
            if(i == 0 && j ==0)
            {
                image[i][j].rgbtRed = round((copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed)/3.0);
                image[i][j].rgbtGreen = round((copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen)/3.0);
                image[i][j].rgbtBlue = round((copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue)/3.0);
            }
            //top side
            if(i == 0 && j > 0 && j < width-1)
            {
                image[i][j].rgbtRed =   round((copy[i][j-1].rgbtRed +      copy[i+1][j-1].rgbtRed +     copy[i+1][j].rgbtRed +   copy[i+1][j+1].rgbtRed +     copy[i][j+1].rgbtRed)/5.0);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen +    copy[i+1][j-1].rgbtGreen +   copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen +   copy[i][j+1].rgbtGreen)/5.0);
                image[i][j].rgbtBlue =  round((copy[i][j-1].rgbtBlue +   copy[i+1][j-1].rgbtBlue +       copy[i+1][j].rgbtBlue +  copy[i+1][j+1].rgbtBlue +    copy[i][j+1].rgbtBlue )/5.0);
            }
            //right corner
            if(i == 0 && j == width-1)
            {
                 image[i][j].rgbtRed = round((copy[i][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i-1][j-1].rgbtRed)/3.0);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen)/3.0);
                image[i][j].rgbtBlue = round((copy[i][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue)/3.0);
            }
            //Inside the border
            if((i > 0 && j > 0) && (i < height - 2) && (j < width - 2))
            {
                image[i][j].rgbtRed =   round((copy[i-1][j-1].rgbtRed +      copy[i-1][j].rgbtRed +     copy[i-1][j+1].rgbtRed +   copy[i][j+1].rgbtRed +     copy[i+1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i][j-1].rgbtRed)/8.0);
                image[i][j].rgbtGreen = round((copy[i-1][j-1].rgbtGreen +    copy[i-1][j].rgbtGreen +   copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen +   copy[i+1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen)/8.0);
                image[i][j].rgbtBlue =  round((copy[i-1][j-1].rgbtBlue +   copy[i-1][j].rgbtBlue +       copy[i-1][j+1].rgbtBlue +  copy[i][j+1].rgbtBlue +    copy[i+1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j-1].rgbtBlue)/8.0);
            }
            //right side
            if(j == width-1 && i < height-2 && i > 0)
            {
                image[i][j].rgbtRed =   round((copy[i-1][j].rgbtRed +      copy[i-1][j-1].rgbtRed +     copy[i][j-1].rgbtRed +   copy[i+1][j-1].rgbtRed +     copy[i+1][j].rgbtRed)/5.0);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen +    copy[i-1][j-1].rgbtGreen +   copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen +   copy[i+1][j].rgbtGreen)/5.0);
                image[i][j].rgbtBlue =  round((copy[i-1][j].rgbtBlue +   copy[i-1][j-1].rgbtBlue +       copy[i][j-1].rgbtBlue +  copy[i+1][j-1].rgbtBlue +    copy[i+1][j].rgbtBlue )/5.0);
            }
            //bottom right corner
            if (i == height-1 && j == width-1)
            {
                image[i][j].rgbtRed =    round((copy[i-1][j].rgbtRed +   copy[i-1][j-1].rgbtRed +   copy[i+1][j-1].rgbtRed)/3.0);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen)/3.0);
                image[i][j].rgbtBlue =  round((copy[i-1][j].rgbtBlue +  copy[i-1][j-1].rgbtBlue +  copy[i+1][j-1].rgbtBlue)/3.0);
            }
            //bottom side
            if (i == height-1 && j < width-2 && j > 0)
            {
                image[i][j].rgbtRed =   round((copy[i][j-1].rgbtRed +      copy[i-1][j-1].rgbtRed +     copy[i-1][j].rgbtRed +   copy[i-1][j+1].rgbtRed +     copy[i+1][j+1].rgbtRed)/5.0);
                image[i][j].rgbtGreen = round((copy[i][j-1].rgbtGreen +    copy[i-1][j-1].rgbtGreen +   copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen +   copy[i+1][j+1].rgbtGreen)/5.0);
                image[i][j].rgbtBlue =  round((copy[i][j-1].rgbtBlue +   copy[i-1][j-1].rgbtBlue +       copy[i-1][j].rgbtBlue +  copy[i-1][j+1].rgbtBlue +    copy[i+1][j+1].rgbtBlue )/5.0);
            }
            //left bottom corner
            if (i == height-1 && j == 0)
            {
                image[i][j].rgbtRed =    round((copy[i-1][j].rgbtRed +   copy[i-1][j+1].rgbtRed +   copy[i][j+1].rgbtRed)/3.0);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen)/3.0);
                image[i][j].rgbtBlue =  round((copy[i-1][j].rgbtBlue +  copy[i-1][j+1].rgbtBlue +  copy[i][j+1].rgbtBlue)/3.0);
            }
            //left side
            if (j == 0 && i < height -2 && i > 0)
            {
                image[i][j].rgbtRed =   round((copy[i-1][j].rgbtRed +       copy[i-1][j+1].rgbtRed +     copy[i][j+1].rgbtRed +   copy[i+1][j+1].rgbtRed +     copy[i+1][j].rgbtRed)/5.0);
                image[i][j].rgbtGreen = round((copy[i-1][j].rgbtGreen +     copy[i-1][j+1].rgbtGreen +   copy[i][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen +   copy[i+1][j].rgbtGreen)/5.0);
                image[i][j].rgbtBlue =  round((copy[i-1][j].rgbtBlue +      copy[i-1][j+1].rgbtBlue +    copy[i][j+1].rgbtBlue +  copy[i+1][j+1].rgbtBlue +    copy[i+1][j].rgbtBlue )/5.0);
            }
        }
    }
}
