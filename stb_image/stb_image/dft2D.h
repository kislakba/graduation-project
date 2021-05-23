#ifndef __DFT2D_H__
  #define __DFT2D_H__
  #include <stdio.h>
  #include <complex.h>
  #include <stdlib.h>
  #include <math.h>
  #include <stdint.h>
  #include "arrayOperations.h"
  #define PI 3.141592654

  float complex *twoDimenDft(float *points, int height, int width);
  float *twoDimenReverseDft(float complex *points, int height, int width);
  float *fftShift(float *Image, int height, int width);
  float *fftReverseShift(float *Image, int height, int width);
  double complex *dft(double *points, int size);
  float complex *fft(float *points, int size);
  float complex *fftComplex(float complex *points, int size, int inverse);
  float *inverseDft(double complex *points, int size);
  float complex *twoDimenFft(float *points, int height, int width);
  float *twoDimenInverseFft(float complex *points, int height, int width);

#endif