#ifndef __IMAGEOPERATIONS_H__
  #define __IMAGEOPERATIONS_H__
  #include <stdio.h>
  #include <complex.h>
  #include <stdlib.h>
  #include <math.h>
  #include <stdint.h>
  #include "arrayOperations.h"


  unsigned char *changePhotoToChar(float *photo, int width, int height);
  unsigned char *changePhotoToCharWithLogTransform(float *photo, int width, int height, float max);
  float *logTransform(float *photo, int width, int height, float max);
  unsigned char *convertToGray(unsigned char *img, int width, int height, int channels);
  float *convertBetweenZeroAndOne(unsigned char *img, int width, int height);

#endif