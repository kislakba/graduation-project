#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define PI 3.141592654
#define MASTER 0

double complex *create1DComplexArray(int n)
{
     double complex *T = (double complex *)malloc(n * sizeof(double complex));
     return T;
}
double complex **create2DComplexArray(int N, int M)
{
     double complex **T = (double complex **)malloc(N * sizeof(double complex *));
     for (int i = 0; i < N; i++)
          T[i] = malloc(M * sizeof(double complex));
     return T;
}
double *create1DDoubleArray(int n)
{
     double *T = (double *)malloc(n * sizeof(double));
     return T;
}
double *create1DFloatArray(int n)
{
     float *T = (float *)malloc(n * sizeof(float));
     return T;
}
double *create2DDoubleArray(int n, int m)
{
     double **T = (double **)malloc(n * sizeof(double *));
     for (int i = 0; i < n; i++)
          T[i] = malloc(m * sizeof(double));
     return T;
}
void printComplexArray(double complex *T, int n)
{
     int i;
     for (i = 0; i < n; i++)
          printf("%d. iteration of DFT = %.3f %+.3fi\n", i + 1, creal(T[i]), cimag(T[i]));

     puts("");
}
void printFloatArray(float *T, int n)
{
     int i;
     for (i = 0; i < n; i++)
          printf(" %.3f\t", T[i]);

     puts("");
}
double r2()
{
     return (double)rand() / (double)RAND_MAX;
}
unsigned char *changePhotoToChar(float *photo, int width, int height, float max)
{
     unsigned char *return_photo = malloc(width * height);
     float c = 255 / log(1 + max); 
     for (int i = 0; i < width * height; i++)
     {
          return_photo[i] = (uint8_t)(c * log(1 + photo[i]));
     }
     return return_photo;
}
unsigned char *convertToGray(unsigned char *img, int width, int height, int channels)
{
     size_t img_size = width * height * channels;
     int gray_channels = channels == 4 ? 2 : 1;
     size_t gray_img_size = width * height * gray_channels;

     unsigned char *gray_img = malloc(gray_img_size);
     if (gray_img == NULL)
     {
          printf("an error occured while loading gray_image \n");
          return 0;
     }
     for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels)
     {
          *pg = (uint8_t)((0.2126 * (*p) + 0.7152 * (*(p + 1)) + 0.0722 * (*(p + 2))));
          if (channels == 4)
          {
               *(pg + 1) = *(p + 3);
          }
     }
     return gray_img;
}
double complex *dft(double *points, int size)
{
     double complex *result = create1DComplexArray(size);
     double complex temp;
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

float *findABS(double complex *complexValues, int size)
{
     float *result = create1DFloatArray(size);
     float x, y, temp_res;
     for (int i = 0; i < size; i++)
     {
          x = creal(complexValues[i]);
          y = cimag(complexValues[i]);
          temp_res = sqrt((x * x) + (y * y));
          result[i] = temp_res;
     }
     return result;
}
float *twoDimenDft(unsigned char *points, int height, int width)
{
     int size = height * width;
     double complex *resultForFirstDFT = create1DComplexArray(size);
     double complex *resultForSecondDFT = create1DComplexArray(size);
     double complex temp;
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
     tempPhoto = findABS(resultForFirstDFT, size);
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

     photo = findABS(resultForSecondDFT, size);
     return photo;
}
void printImage(unsigned char *T, int n)
{
     int i;
     float x;
     unsigned char temp;
     for (i = 0; i < n; i++)
     {
          x = (float)T[i];
          temp = (unsigned char)x;
          printf("%f \n", x);
          printf("%d \n", (unsigned)temp);
     }
     puts("");
}
void printImageFloat(float *T, int n)
{
     int i;
     for (i = 0; i < n; i++)
     {
          printf("%f \n", 255 /log(1 + T[i]));
          
     }
     puts("");
}
float findMax(float *T, int size){
     float maximumVal = 0.0;
     for (int i = 0; i < size; i++)
     {
          if(T[i] > maximumVal) maximumVal = T[i];
     }
     return maximumVal;
}
int main(void)
{
     unsigned char *grayPhoto;
     unsigned char *dftPhoto;

     int width, height, channels;
     unsigned char *img = stbi_load("berkayNormal.jpg", &width, &height, &channels, 0);
     if (img == NULL)
     {
          printf("an error occured while loading image \n");
          return 0;
     }
     printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels);
     int gray_channels = channels == 4 ? 2 : 1;
     grayPhoto = convertToGray(img, width, height, channels);
     float *grayDft = twoDimenDft(grayPhoto, height, width);
     float max = findMax(grayDft, height* width);
     dftPhoto = changePhotoToChar(grayDft, width, height,max);
     stbi_write_jpg("berkayFrekans.jpg", width, height, 1, dftPhoto, 100);
     free(grayPhoto);
     stbi_image_free(img);
     return 0;
}