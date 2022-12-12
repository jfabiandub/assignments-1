#include <stdio.h>
#include <stdlib.h>

int main() {
  int nrows, ncols;
  printf("Please enter #rows: ");
  scanf(" %d", &nrows);

  printf("Please enter #cols: ");
  scanf(" %d", &ncols);

  int* M = malloc(sizeof(int) * ncols * nrows);

  int val;
  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      printf("Enter a value for m[%d][%d]: ", i, j);
      scanf(" %d", &val);
      M[i*ncols + j] = val;
    }
  }

  for (int i = 0; i < nrows; i++) {
    for (int j = 0; j < ncols; j++) {
      int val = M[i*ncols + j];
      printf("%d ", val);
    }
    printf("\n");
  }
  
  free(M);
  return 0;
}