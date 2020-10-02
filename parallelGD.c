#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "mpi.h"

#define MASTER 0

float *create1DArray(int n) {
    float *T = (float *)malloc(n * sizeof(float));
    return T;
}

void fillArray(float *T, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++)
        T[i] = (float)(rand() % 10) / 10.0;
}

void printArray(float *T, int n) {
    for (int i = 0; i < n; i++)
	printf("%.3f ", T[i]);
    puts("");
}

float innerProd(float *u, float *v, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; i++)
	sum += u[i] * v[i];
    return sum;
}

float *mat_vec_mult(float *M, float *v, int n1, int n2) {
    float *r = create1DArray(n1);
    for (int i = 0; i < n1; i++)
	r[i] = innerProd(&M[i*n2], v, n2);
    return r;
}

float *vec_subt(float *u, float *v, int n) {
    float *r = create1DArray(n);
    for (int i = 0; i < n; i++)
	r[i] = u[i] - v[i];
    return r;
}

float *scalar_mult(float *u, float alpha, int n) {
    float *r = create1DArray(n);
    for (int i = 0; i < n; i++)
	r[i] = alpha * u[i];
    return r;
}

float l2Norm2(float *u, int n) {
    float l2 = 0.0;
    for (int i = 0; i < n; i++)
	l2 += u[i] * u[i];
    return l2;
}

int main(int argc, char *argv[]) {

int n1 = atoi(argv[1]);
int n2 = atoi(argv[2]);
float const ALPHA = atof(argv[3]);
int const NITERS = atoi(argv[4]);

int rank, size;

MPI_Init(NULL, NULL);

double t1 = MPI_Wtime();  // Start timer

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

int chunk1 = n1 / size;
int chunk2 = n2 / size;

float *A, *A_local, *A_T_local, *x, *x_local, *b, *b_local, *r_local, *y, *y_local, *u_local;

x = create1DArray(n2);

if (rank == MASTER) {
    A = create1DArray(n1 * n2);
    fillArray(A, n1 * n2);
    
    fillArray(x, n2);  // initial guess
    
    b = create1DArray(n1);
    fillArray(b, n1);
}

// Row type
MPI_Datatype rowType;
MPI_Type_contiguous(n2, MPI_FLOAT, &rowType);
MPI_Type_commit(&rowType);

// Column type
MPI_Datatype colType, newColType;
int count = n1, blocklength = 1, stride = n2;
MPI_Type_vector(count, blocklength, stride, MPI_FLOAT, &colType);
MPI_Type_commit(&colType);

MPI_Type_create_resized(colType, 0, 1*sizeof(float), &newColType);
MPI_Type_commit(&newColType);

for (int iter = 1; iter <= NITERS; iter++) { // start of iter.

// Broadcast x initial guess vector
MPI_Bcast(x, 1, rowType, MASTER, MPI_COMM_WORLD);

// Scatter b vector
b_local = create1DArray(chunk1);
MPI_Scatter(b, chunk1, MPI_FLOAT, b_local, chunk1, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

// Scatter A matrix
A_local = create1DArray(chunk1 * n2);
MPI_Scatter(A, chunk1, rowType, A_local, chunk1*n2, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

// A_local * x = r_local
r_local = create1DArray(chunk1);
r_local = mat_vec_mult(A_local, x, chunk1, n2);

// r_local - b_local = y_local
y_local = create1DArray(chunk1);
y_local = vec_subt(r_local, b_local, chunk1);

// Construct y from y_local's
y = create1DArray(n1);
MPI_Allgather(y_local, chunk1, MPI_FLOAT, y, chunk1, MPI_FLOAT, MPI_COMM_WORLD);

// Scatter columns of A, construct A_local^T's
A_T_local = create1DArray(chunk2 * n1);
MPI_Scatter(A, chunk2, newColType, A_T_local, chunk2 * n1, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

// A_local^T * y = u_local
u_local = create1DArray(chunk2);
u_local = mat_vec_mult(A_T_local, y, chunk2, n1);

// Scatter x, construct x_local's
x_local = create1DArray(chunk2);
MPI_Scatter(x, chunk2, MPI_FLOAT, x_local, chunk2, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

// x_local := x_local - ALPHA * u_local
x_local = vec_subt(x_local, scalar_mult(u_local, ALPHA, chunk2), chunk2);

// Gather x_local's to update x
MPI_Gather(x_local, chunk2, MPI_FLOAT, x, chunk2, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

// Parallel L-2 norm
float local_norm = l2Norm2(y_local, chunk1);
float global_norm = 0.0;
MPI_Reduce(&local_norm, &global_norm, 1, MPI_FLOAT, MPI_SUM, MASTER, MPI_COMM_WORLD);

if (rank == MASTER) {
    printf("%d. iteration completed!\n", iter);
    printf("Error = %.10f\n", global_norm);
} 

} // end of iteration

double t2 = MPI_Wtime();
if (rank == MASTER)
    printf("Time elapsed = %f sec.\n", t2 - t1);


MPI_Finalize();


}

