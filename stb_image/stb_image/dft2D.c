#include "dft2D.h"

float *twoDimenDft(float *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float complex *resultForSecondDFT = create1DComplexArray(size);
     float complex temp;
     float *tempPhoto = create1DFloatArray(size);
     float *photo = create1DFloatArray(size);
     int n, k, i, row, col, place;
     double arg;
     double cosarg, sinarg;

     for (int i = 0; i < height; i++)
     {
          place = (i * width);
          for (k = 0; k < width; k++)
          {
               resultForFirstDFT[(i * width) + k] = 0 + 0 * I;
               arg = -2.0 * PI * k / (double)width;
               for (n = 0; n < width; n++)
               {
                    cosarg = points[place + n] * cos(n * arg);
                    sinarg = points[place + n] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForFirstDFT[(i * width) + k] += temp;
               }
          }
     }
     printf("birinci asama tamam \n");
     tempPhoto = findABSLast(resultForFirstDFT, size);
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               col = k / height;
               resultForSecondDFT[(k * width) + i] = 0 + 0 * I;
               arg = -2.0 * PI * k / (double)height;
               for (n = 0; n < height; n++)
               {
                    place = (n * width); // this because of : in second loop we do not know where we are, we are just mapping in width
                    cosarg = tempPhoto[place + i] * cos(n * arg);
                    sinarg = tempPhoto[place + i] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForSecondDFT[(k * width) + i] += temp;
               }
          }
     }
     printf("ikinci asama tamam \n");

     photo = findABSLast(resultForSecondDFT, size);
     printf("son asama tamam \n");
     return photo;
}

float *twoDimenReverseDft(float *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float complex *resultForSecondDFT = create1DComplexArray(size);
     float complex temp;
     float *tempPhoto = create1DFloatArray(size);
     float *photo = create1DFloatArray(size);
     int n, k, i, row, col, place;
     double arg;
     double cosarg, sinarg;

     for (int i = 0; i < height; i++)
     {
          place = (i * width);
          for (k = 0; k < width; k++)
          {
               resultForFirstDFT[(i * width) + k] = 0 + 0 * I;
               arg = 2.0 * PI * k / (double)width;
               for (n = 0; n < width; n++)
               {
                    cosarg = points[place + n] * cos(n * arg);
                    sinarg = points[place + n] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForFirstDFT[(i * width) + k] += temp;
               }
               
               resultForFirstDFT[(i * width) + k] /= width;

          }
     }
     printf("birinci asama tamam \n");
     tempPhoto = findABSLast(resultForFirstDFT, size);
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               col = k / height;
               resultForSecondDFT[(k * width) + i] = 0 + 0 * I;
               arg = 2.0 * PI * k / (double)height;
               for (n = 0; n < height; n++)
               {
                    place = (n * width); // this because of : in second loop we do not know where we are, we are just mapping in width
                    cosarg = tempPhoto[place + i] * cos(n * arg);
                    sinarg = tempPhoto[place + i] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForSecondDFT[(k * width) + i] += temp;
               }

               resultForSecondDFT[(k * width) + i]  /= height;
               
          }
     }
     printf("ikinci asama tamam \n");

     photo = findABSLast(resultForSecondDFT, size);
     return photo;
}

float *fftShift(float *Image, int height, int width)
{
     int halfOfHeight = height/2;
     int halfOfWidth = width/2;
     float *shiftedImage = create1DFloatArray(height * width);
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(halfOfHeight * width + halfOfWidth) + (i * width) + j] = Image[(i * width) + j];
          }
          
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(halfOfHeight * width) + (i * width) + j] = Image[halfOfWidth + (i * width) + j];
          }
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[halfOfWidth + (i * width) + j] = Image[(halfOfHeight * width) + (i * width) + j];
          }
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(i * width) + j] = Image[(halfOfHeight * width + halfOfWidth) + (i * width) + j];
          }
     }
     return shiftedImage;
}

float *fftReverseShift(float *Image, int height, int width)
{
     int halfOfHeight = height/2;
     int halfOfWidth = width/2;
     float *shiftedImage = create1DFloatArray(height * width);
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(i * width) + j] = Image[(halfOfHeight * width + halfOfWidth) + (i * width) + j];
          }
          
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[halfOfWidth + (i * width) + j] = Image[(halfOfHeight * width) + (i * width) + j] ;
          }
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(halfOfHeight * width) + (i * width) + j] = Image[halfOfWidth + (i * width) + j];
          }
     }
     for (int i = 0; i < halfOfHeight; i++)
     {
          for (int j = 0; j < halfOfWidth; j++)
          {
               shiftedImage[(halfOfHeight * width + halfOfWidth) + (i * width) + j] = Image[(i * width) + j];
          }
     }
     return shiftedImage;
}

float complex *dft(double *points, int size)
{
     float complex *result = create1DComplexArray(size);
     float complex temp;
     int n, k;
     double arg;
     double cosarg, sinarg;
     for (k = 0; k < size; k++)
     {
          result[k] = 0 + 0 * I;
          arg = -2.0 * PI * k / (double)size;
          for (n = 0; n < size; n++)
          {
               cosarg = points[n] * cos(n * arg);
               sinarg = points[n] * sin(n * arg);
               temp = cosarg + sinarg * I; //fourier donusumu alani
               result[k] += temp;
          }
     }
     return result;
}
