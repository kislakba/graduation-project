#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>

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
void printDoubleArray(double *T, int n)
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
float *convertToGray(float *img, int width, int height, int channels)
{
     size_t img_size = width * height * channels;
     int gray_channels = channels == 4 ? 2 : 1;
     size_t gray_img_size = width * height * gray_channels;

     float *gray_img = malloc(gray_img_size);
     if (gray_img == NULL)
     {
          printf("an error occured while loading gray_image \n");
          return 0;
     }
     for (float *p = img, *pg = gray_img; p != img + img_size; p += channels, pg += gray_channels)
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
          temp_res = sqrt((x * x) + (y * y)) / (size / 2);
          result[i] = temp_res;
     }
     return result;
}
float *twoDimenDft(float *points, int height, int width)
{
     int size = height * width;
     double complex *resultForFirstDFT = create1DComplexArray(size);
     double complex *resultForSecondDFT = create1DComplexArray(size);
     double complex temp;
     float *tempPhoto = create1DFloatArray(size);
     float *photo = create1DFloatArray(size);
     int n, k, row, col, place;
     double arg;
     double cosarg, sinarg;
     printf("birinci asama tamam \n");

     for (k = 0; k < size; k++)
     {
          printf("birinci asama tamam \n");

          row = k / width;
          resultForFirstDFT[k] = 0 + 0 * I;
          arg = -2.0 * PI * (k % width) / (double)size;
          for (n = 0; n < width; n++)
          {
               printf("birinci asama tamam \n");
               place = (row * width) + n; // this because of : in second loop we do not know where we are, we are just mapping in width
               cosarg = points[place] * cos(place * arg);
               sinarg = points[place] * sin(place * arg);
               temp = cosarg + sinarg * I; //fourier donusumu alani
               resultForFirstDFT[k] += temp;
          }
     }
     printf("birinci asama tamam \n");
     tempPhoto = findABS(resultForFirstDFT, size);
     for (k = 0; k < size; k++)
     {
          col = k / height;
          resultForSecondDFT[k] = 0 + 0 * I;
          arg = -2.0 * PI * (k % height) / (double)size;
          for (n = 0; n < width; n++)
          {
               place = (n * width) + col; // this because of : in second loop we do not know where we are, we are just mapping in width
               cosarg = tempPhoto[place] * cos(place * arg);
               sinarg = tempPhoto[place] * sin(place * arg);
               temp = cosarg + sinarg * I; //fourier donusumu alani
               resultForSecondDFT[k] += temp;
          }
     }
     printf("ikinci asama tamam \n");

     photo = findABS(resultForSecondDFT, size);
     return photo;
}
int main(void)
{
     float *grayPhoto;

     int width, height, channels;
     float *img = stbi_loadf("stopSign.jpeg", &width, &height, &channels, 0);
     if (img == NULL)
     {
          printf("an error occured while loading image \n");
          return 0;
     }
     printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels);
     int gray_channels = channels == 4 ? 2 : 1;
     grayPhoto = convertToGray(img, width, height, channels);
     stbi_write_jpg("deneme.jpg", width, height, gray_channels, grayPhoto, 100);
     free(grayPhoto);
     stbi_image_free(img);
     return 0;
}