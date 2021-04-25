#ifndef __DFT2D_H__
  #define __DFT2D_H__
  #include <stdio.h>
  #include <complex.h>
  #include <stdlib.h>
  #include <math.h>
  #include <stdint.h>
  #include "arrayOperations.h"
  #define PI 3.141592654

  float *twoDimenDft(float *points, int height, int width);
  float *twoDimenReverseDft(float *points, int height, int width);
  float *fftShift(float *Image, int height, int width);
  float *fftReverseShift(float *Image, int height, int width);
  float complex *dft(double *points, int size);

#endif