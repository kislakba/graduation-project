#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
double complex *create1DArray(int n){
  double complex *T = (double complex *)malloc(n * sizeof(double complex));
  return T;
}
void printArray(double complex *T, int n) {
     int i;
     for (i = 0; i < n; i++)
          printf("The sum: Z1 + Z2 = %.2f %+.2fi\n", creal(T[i]), cimag(T[i]));

     puts("");
}
int main(void){
  double complex z = 3.2 + 0.701 * I;
  double complex *R = create1DArray(5);
  R[0] = 3.2 + 0.701 * I;
  R[1] = 13.2 + 10.701 * I;
  R[2] = 23.2 + 20.701 * I;
  R[3] = 33.2 + 30.701 * I;
  R[4] = 43.2 + 40.701 * I;
  printArray(R, 5);
}
