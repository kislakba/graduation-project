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
               temp = cosarg + sinarg * I;
               result[k] += temp;
          }
     }
     return result;
}
double complex *twoDimenDft(unsigned char *points, int height, int width)
{
     double complex *result = create1DComplexArray(height * width);
     double complex temp;
     int ii, jj;
     double argX, argY;
     double cosarg, sinarg;
     int row, rowOut;
     for (int i = 0; i < height; i++)
     {
          for (int j = 0; j < width; j++)
          {
               float ak = 0;
               float bk = 0;
               for (ii = 0; ii < height; i++)
               {
                    row = (int)(ii / height);
                    for (jj = 0; jj < width; jj++)
                    {
                         float x = -2.0 * PI * i * ii / (float)width;
                         float y = -2.0 * PI * j * jj / (float)height;
                         ak += ((double)points[(ii * width) + jj] / 255) * cos(x + y);
                         bk += ((double)points[(ii * width) + jj] / 255) * 1.0 * sin(x + y);
                    }
               }
               rowOut = (int)(i / height);
               temp = ak + bk * I;
               result[(i * rowOut) + j] += temp;
          }
     }

     return result;
}
double *findABS(double complex *complexValues, int size)
{
     double *result = create1DDoubleArray(size);
     double x, y, temp_res;
     for (int i = 0; i < size; i++)
     {
          x = creal(complexValues[i]);
          y = cimag(complexValues[i]);
          temp_res = sqrt((x * x) + (y * y)) / (size / 2);
          result[i] = temp_res;
     }
     return result;
}
double *findABS2D(double complex *complexValues, int height, int width)
{
     double *result = create1DDoubleArray(height * width);
     double x, y, temp_res;
     int row;
     int size = height * width;
     for (int j = 0; j < height; j++)
     {
          for (int i = 0; i < width; i++)
          {
               x = creal(complexValues[(j * width) + i]);
               y = cimag(complexValues[(j * width) + i]);
               temp_res = sqrt((x * x) + (y * y)) / (size / 2);
               result[(j * width) + i] = temp_res;
          }
     }

     return result;
}
int main(void)
{
     int width, height, channels;
     unsigned char *img = stbi_load("stopSign_gray.jpg", &width, &height, &channels, 0);
     if (img == NULL)
     {
          printf("an error occured while loading image \n");
          return 0;
     }
     printf("Loaded image has \t width = %d \t height = %d \t channels = %d \n", width, height, channels);

     stbi_image_free(img);
     return 0;
}