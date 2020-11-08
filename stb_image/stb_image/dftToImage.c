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
double *create1DDoubleArray(int n)
{
     double *T = (double *)malloc(n * sizeof(double ));
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
    return (double)rand() / (double)RAND_MAX ;
}
unsigned char *convertToGray(unsigned char *img, int width, int height, int channels)
{
    size_t img_size = width * height * channels;
    int gray_channels = channels == 4 ? 2 : 1;
    size_t gray_img_size = width * height * gray_channels;
    
    unsigned char *gray_img = malloc(gray_img_size);
    if(gray_img == NULL)
    {
        printf("an error occured while loading gray_image \n");
        return 0;
    }
    for (unsigned char *p = img, *pg = gray_img; p != img + img_size; p+=channels, pg +=gray_channels)
    {
        *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);
         if(channels == 4)
         {
            *(pg + 1) = *(p + 3);
         }
    }
    return gray_img;
}
double complex *dft(double *points, int size)
{
  double complex *result =create1DComplexArray(size);
  double complex temp;
  int n,k;
  double arg;
  double cosarg, sinarg;
  for (k = 0; k < size; k++) {
    result[k] = 0   + 0*I;
    arg = -2.0 * PI * k / (double)size;
    for (n = 0; n < size; n++) {
      cosarg = points[n]*cos(n * arg);
      sinarg = points[n]*sin(n * arg);
      temp = cosarg + sinarg * I;
      result[k] += temp;
    }
  }
  return result;
}
double *findABS(double complex *complexValues, int size)
{
  double *result =create1DDoubleArray(size);
  double x,y,temp_res;
  for (int i = 0; i < size; i++) {
    x=creal(complexValues[i]);
    y=cimag(complexValues[i]);
    temp_res = sqrt((x*x)+(y*y)) / (size/2);
    result[i]= temp_res;
  }
  return result;
}
int main(void) {

  return 0;
}