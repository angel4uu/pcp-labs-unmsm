#include <stdio.h>
#include <omp.h>

#define MAX 800

int main() {
  /** 
  Definición de las matrices: a, b, y c.
  */
  int a[MAX][MAX],
      b[MAX][MAX],
      c[MAX][MAX];
  int i,j,k,tid,nthreads;

  /** 
  Inicialización de las matrices a y b. a será la matriz identidad.
  */
#pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
{
  tid=omp_get_thread_num();
  #pragma omp for
  for (i = 0; i < MAX; i++){
    for (j = 0; j < MAX; j++) {
         a[i][j] = 0;
         b[i][j] = 100 + i;
    }
    a[i][i] = 1;
  }

  /**
  Multiplicación de las matrices
  */
#pragma omp for
  for (i = 0; i < MAX; i++){
    for (j = 0; j < MAX; j++) {
       c[i][j] = 0;
       for (k = 0; k < MAX; k++){
         c[i][j] += a[i][k] * b[k][j];
       }
    }
  }
}
  /**
  Impresión de la matriz C
  */
  for (i = 0; i < MAX; i++) {
    for (j = 0; j < MAX; j++)
      printf("%5d ", c[i][j]);
    printf("\n");
  }
  return 0;
}