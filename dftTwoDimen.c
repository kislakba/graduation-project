#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654
#define MASTER 0
double complex *create1DComplexArray(int n) {
     double complex *T = (double complex *)malloc(n * sizeof(double complex));
     return T;
}
double *create1DDoubleArray(int n) {
     double *T = (double *)malloc(n * sizeof(double ));
     return T;
}
void printComplexArray(double complex *T, int n) {
     int i;
     for (i = 0; i < n; i++)
          printf("%d. iteration of DFT = %.3f %+.3fi\n", i + 1, creal(T[i]), cimag(T[i]));

     puts("");
}
void printDoubleArray(double *T, int n) {
     int i;
     for (i = 0; i < n; i++)
          printf(" %.3f\t", T[i]);

     puts("");
}
void print2DArray(float *T, int n1, int n2 ){
  for(int i = 0; i<n1; i++){
    for (int j = 0; j < n2; j++) {
      printf("%.3f \t", T[(i*n2) + j]);
    }
    printf("\n" );
  }
}
void print2DComplexArray(float *T, int n1, int n2 ){
  for(int i = 0; i<n1; i++){
    for (int j = 0; j < n2; j++) {
          printf("%d. iteration of DFT = %.3f %+.3fi\n", i + 1, creal(T[i]), cimag(T[i]));
    }
    printf("\n" );
  }
}
double r2()
{
    return (double)rand() / (double)RAND_MAX ;
}
void fillArrayWithRandomSinus(double *T, int n) {
     int i;
     double multp = 0.2;
     double val = PI / 180;
     for (i = 0; i < n; i++)
          T[i]=4*sin(9*(i * multp)) + 14*sin(3 * (i * multp)) - 7*sin(10 * (i * multp));

     }
double complex *dft(double *points, int size){

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
double complex *dft(double *points, int size){

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
double complex *dft2D(double *points, int size){

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
void plotDouble(char* str, double *points, int size){
  // open persistent gnuplot window
  FILE* gnuplot_pipe = fopen (str, "w");
  for(size_t i=0; i<size; ++i){
    fprintf(gnuplot_pipe, "%zu %f  \n", i, points[i]);
  }
  fprintf(gnuplot_pipe, "e\n");
  // refresh can probably be omitted
  fprintf(gnuplot_pipe, "refresh\n");
  fflush(gnuplot_pipe);
  fclose(gnuplot_pipe);
}
void plotComplex( double complex *points, int size){
  // open persistent gnuplot window
  FILE* gnuplot_pipe = fopen ("dataComplex.dat", "w");
  for(size_t i=0; i<size; ++i){
    fprintf(gnuplot_pipe, "%f %f  \n", creal(points[i]), cimag(points[i]));
  }
  fprintf(gnuplot_pipe, "e\n");
  // refresh can probably be omitted
  fprintf(gnuplot_pipe, "refresh\n");
  fflush(gnuplot_pipe);
  fclose(gnuplot_pipe);
}
double *findABS(double complex *complexValues, int size){
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
  double *points = create1DDoubleArray(10000);
  fillArrayWithRandomSinus(points, 10000);
  printDoubleArray(points, 10000);
  double complex *res = dft(points, 10000);
  printComplexArray(res, 10000);
  plotDouble("randValues.dat",points,10000);
  double *absVals = findABS(res,10000);
  printDoubleArray(absVals,10000);
  plotDouble("absvalues.dat",absVals,10000);

  return 0;
}
