#include "arrayOperations.h"

float complex *create1DComplexArray(int n)
{
     float complex *T = (float complex *)malloc(n * sizeof(float complex));
     return T;
}

float complex **create2DComplexArray(int N, int M)
{
     float complex **T = (float complex **)malloc(N * sizeof(float complex *));
     for (int i = 0; i < N; i++)
          T[i] = malloc(M * sizeof(float complex));
     return T;
}

double *create1DDoubleArray(int n)
{
     double *T = (double *)malloc(n * sizeof(double));
     return T;
}

float *create1DFloatArray(int n)
{
     float *T = (float *)malloc(n * sizeof(float));
     return T;
}

double **create2DDoubleArray(int n, int m)
{
     double **T = (double **)malloc(n * sizeof(double *));
     for (int i = 0; i < n; i++)
          T[i] = malloc(m * sizeof(double));
     return T;
}

void printComplexArray(float complex *T, int n)
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

void printImage(unsigned char *T, int n)
{
     int i;
     float x;
     unsigned char temp;
     for (i = 0; i < n; i++)
     {
          printf("img[%d] \t %d \n", i, T[i]);
     }
     puts("");
}

void printImageFloat(float *T, int n)
{
     int i;
     for (i = 0; i < n; i++)
     {
          printf("float[%d] \t %f \n", i, T[i]);
     }
     puts("");
}

float *findABS(float complex *complexValues, int size)
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

float *findABSLast(float complex *complexValues, int size)
{
     float *result = create1DFloatArray(size);
     float x, y, temp_res;
     for (int i = 0; i < size; i++)
     {
          x = creal(complexValues[i]);
          y = cimag(complexValues[i]);
          temp_res = sqrt((x * x) + (y * y));
          if(temp_res > 1.0)
          {
               result[i] = 1;
          } 
          else 
          {
               result[i] = temp_res;
          }

     }
     return result;
}

float findMax(float *T, int size)
{
     float maximumVal = 0.0;
     for (int i = 0; i < size; i++)
     {
          if (T[i] > maximumVal)
               maximumVal = T[i];
     }
     return maximumVal;
}