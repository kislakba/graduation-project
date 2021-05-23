#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <complex.h>

int main(){
    
    float complex temp = 3 + 4*I;
    float complex temp1 = 3 + 4*I;
    float complex tempMult = temp * temp1;
    printf("%d. iteration of DFT = %.3f %+.3fi\n", 1, creal(tempMult), cimag(tempMult));

}