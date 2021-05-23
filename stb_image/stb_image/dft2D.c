#include "dft2D.h"

float complex *twoDimenDft(float *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float complex *resultForSecondDFT = create1DComplexArray(size);
     float complex temp;
     float *tempPhoto = create1DFloatArray(size);
     float *photo = create1DFloatArray(size);
     int n, k, i, row, col, place;
     float arg;
     float cosarg, sinarg;
     float complex cosargC, sinargC;

     for (int i = 0; i < height; i++)
     {
          place = (i * width);
          for (k = 0; k < width; k++)
          {
               resultForFirstDFT[(i * width) + k] = 0 + 0 * I;
               arg = -2.0 * PI * k / (float)width;
               for (n = 0; n < width; n++)
               {
                    cosarg = points[place + n] * cos(n * arg);
                    sinarg = points[place + n] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForFirstDFT[(i * width) + k] += temp;
               }
          }
     }
     printFloatComplexArray(resultForFirstDFT, 25);
     printf("birinci asama tamam \n");
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               col = k / height;
               resultForSecondDFT[(k * width) + i] = 0 + 0 * I;
               arg = -2.0 * PI * k / (float)height;
               for (n = 0; n < height; n++)
               {
                    place = (n * width); // this because of : in second loop we do not know where we are, we are just mapping in width
                    cosargC = resultForFirstDFT[place + i] * cos(n * arg);
                    //printf("%f \t", cosarg);
                   // printf("%.3f %+.3fi\n", creal(resultForFirstDFT[place + i] * cos(n * arg)), cimag(resultForFirstDFT[place + i] * cos(n * arg)));
                    sinargC = resultForFirstDFT[place + i] * sin(n * arg);
                    temp = cosargC + sinargC * I; //fourier donusumu alani
                    resultForSecondDFT[(k * width) + i] += temp;
               }
          }
     }
     printf("ikinci asama tamam \n");
     printf("son asama tamam \n");
     return resultForSecondDFT;
}

float *twoDimenReverseDft(float complex *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float *resultForSecondDFT = create1DFloatArray(size);
     float complex temp;
     float *tempPhoto = create1DFloatArray(size);
     float *photo = create1DFloatArray(size);
     int n, k, i, row, col, place;
     float arg;
     float complex cosarg, sinarg;

     for (int i = 0; i < height; i++)
     {
          place = (i * width);
          for (k = 0; k < width; k++)
          {
               resultForFirstDFT[(i * width) + k] = 0 + 0 * I;
               arg = 2.0 * PI * k / (float)width;
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
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               col = k / height;
               resultForSecondDFT[(k * width) + i] = 0;
               arg = 2.0 * PI * k / (float)height;
               for (n = 0; n < height; n++)
               {
                    place = (n * width); // this because of : in second loop we do not know where we are, we are just mapping in width
                    cosarg = resultForFirstDFT[place + i] * cos(n * arg);
                    sinarg = resultForFirstDFT[place + i] * sin(n * arg);
                    temp = cosarg + sinarg * I; //fourier donusumu alani
                    resultForSecondDFT[(k * width) + i] += creal(temp);
               }
               resultForSecondDFT[(k * width) + i] /= height;
          }
     }
     printf("ikinci asama tamam \n");
     printf("son asama tamam \n");
     return resultForSecondDFT;
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
     printf("shifted \n");

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

double complex *dft(double *points, int size)
{
     double complex *result = create1DDoubleComplexArray(size);
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

float *inverseDft(double complex *points, int size)
{
     float *result = create1DDoubleArray(size);
     float complex temp;
     int n, k;
     float arg;
     float complex cosarg, sinarg;
     for (k = 0; k < size; k++)
     {
          result[k] = 0 + 0 * I;
          arg = 2.0 * PI * k / (double)size;
          for (n = 0; n < size; n++)
          {
               cosarg = points[n] * cos(n * arg);
               sinarg = points[n] * sin(n * arg);
               temp = cosarg + sinarg * I; //fourier donusumu alani
               result[k] += creal(temp);
          }
          result[k] /= size;
     }
     return result;
}

/* 
   fft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute fft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute fft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = -sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
float complex *fft(float *points, int size)
{
     if(size == 1) return points;

     float *Xodd = create1DDoubleArray(size/2);
     float *Xeven = create1DDoubleArray(size/2);
     float complex *Fodd = create1DDoubleComplexArray(size/2);
     float complex *Feven = create1DDoubleComplexArray(size/2);
     for (size_t i = 0; i != size/2; i++)
     {
          Xeven[i] = points[2*i];
          Xodd[i] = points[2*i + 1];
     }
     Fodd = fft(Xodd, size/2);
     Feven = fft(Xeven, size/2);
     float complex *freqbins = create1DDoubleComplexArray(size);
     float arg;
     float complex expcmpx;
     arg = -2.0 * PI / (float)size;
     for (size_t k = 0; k != size/2; k++)
     {
          expcmpx = cos(k * arg) + sin(k * arg) * I;
          freqbins[k] = Feven[k] + expcmpx * Fodd[k];
          freqbins[k + size / 2] = Feven[k] - expcmpx * Fodd[k];
     }
     return freqbins;
}

float complex *fftComplex(float complex *points, int size, int inverse)
{
     if(size == 1) return points;

     float complex *Xodd = create1DFloatComplexArray(size/2);
     float complex *Xeven = create1DFloatComplexArray(size/2);
     float complex *Fodd = create1DFloatComplexArray(size/2);
     float complex *Feven = create1DFloatComplexArray(size/2);
     for (size_t i = 0; i != size/2; i++)
     {
          Xeven[i] = points[2*i];
          Xodd[i] = points[2*i + 1];
     }
     Fodd = fftComplex(Xodd, size/2, inverse);
     Feven = fftComplex(Xeven, size/2, inverse);
     float complex *freqbins = create1DFloatComplexArray(size);
     float arg;
     float complex expcmpx;
     arg = -2.0 * PI / (float)size;
     if (inverse == 1) arg *= -1;
     for (size_t k = 0; k != size/2; k++)
     {
          expcmpx = cos(k * arg) + sin(k * arg) * I;
          freqbins[k] = Feven[k] + expcmpx * Fodd[k];
          freqbins[k + size / 2] = Feven[k] - expcmpx * Fodd[k];
     }
     return freqbins;
}

float complex *twoDimenFft(float *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float complex *resultForSecondDFT = create1DComplexArray(size);
     float complex temp;
     int n, k, i, row, col, place;
     float *tempPoints = create1DFloatArray(width);
     float complex *tempFFT = create1DFloatComplexArray(width);
     float complex *tempPointsComplex = create1DFloatComplexArray(height);

     for (int i = 0; i < height; i++)
     {
          for (k = 0; k < width; k++)
          {
               tempPoints[k] = points[(i * width) + k];
          }
          tempFFT = fft(tempPoints, width);
          for (n = 0; n < width; n++)
          {
               resultForFirstDFT[(i * width) + n] = tempFFT[n];
          }
     }
     printFloatComplexArray(resultForFirstDFT, 25);
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               tempPointsComplex[k] = resultForFirstDFT[(width * k) + i];
          }
          tempFFT = fftComplex(tempPointsComplex, height, 0);
          for (n = 0; n < height; n++)
          {
               resultForSecondDFT[(width * n) + i] = tempFFT[n];
          }
     }
     printf("ikinci asama tamam \n");
     printf("son asama tamam \n");
     return resultForSecondDFT;
}

float *twoDimenInverseFft(float complex *points, int height, int width)
{
     int size = height * width;
     float complex *resultForFirstDFT = create1DComplexArray(size);
     float *resultForSecondDFT = create1DFloatArray(size);
     float complex temp;
     int n, k, i, row, col, place;
     float complex *tempPoints = create1DFloatComplexArray(width);
     float complex *tempFFT = create1DFloatComplexArray(width);
     float complex *tempPointsComplex = create1DFloatComplexArray(height);

     for (int i = 0; i < height; i++)
     {
          for (k = 0; k < width; k++)
          {
               tempPoints[k] = points[(i * width) + k];
          }
          tempFFT = fftComplex(tempPoints, width, 1);
          for (n = 0; n < width; n++)
          {
               resultForFirstDFT[(i * width) + n] = tempFFT[n] / width;
          }
     }
     printFloatComplexArray(resultForFirstDFT, 25);
     for (i = 0; i < width; i++)
     {
          for (k = 0; k < height; k++)
          {
               tempPointsComplex[k] = resultForFirstDFT[(width * k) + i];
          }
          tempFFT = fftComplex(tempPointsComplex, height, 1);
          for (n = 0; n < height; n++)
          {
               resultForSecondDFT[(width * n) + i] = creal(tempFFT[n] / height);
          }
     }
     printf("ikinci asama tamam \n");
     printf("son asama tamam \n");
     return resultForSecondDFT;
}