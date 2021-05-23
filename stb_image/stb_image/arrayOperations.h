#ifndef __ARRAYOPERATIONS_H__
  #define __ARRAYOPERATIONS_H__
  #include <stdio.h>
  #include <complex.h>
  #include <stdlib.h>
  #include <math.h>

  float complex *create1DComplexArray(int n);
  double complex *create1DDoubleComplexArray(int n);
  float complex *create1DFloatComplexArray(int n);
  float complex **create2DComplexArray(int N, int M);
  double *create1DDoubleArray(int n);
  float *create1DFloatArray(int n);
  double **create2DDoubleArray(int n, int m);
  void printComplexArray(float complex *T, int n);
  void printDoubleComplexArray(double complex *T, int n);
  void printFloatComplexArray(float complex *T, int n);
  void printDoubleArray(double *T, int n);
  void printFloatArray(float *T, int n);
  void printImage(unsigned char *T, int n);
  void printImageFloat(float *T, int n);
  float *findABS(float complex *complexValues, int size);
  float *findABSLast(float complex *complexValues, int size);
  float findMax(float *T, int size);

#endif