#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Hadamard.h"

int main() {
  int i, d, orth;
  int **result = Hadamard(4);

  for (i = 0; i < pow(2, 4); i++) {
    for (d = 0; d < pow(2, 4); d++) {
      printf("%d ", result[i][d]);
    }
    printf("\n");
  }

  orth = Check_Matrix_Orthogonality(result, 8);
  printf("%d\n", orth);

  Release_Matrix(result, 4);

  return 0;
}

int Check_Matrix_Orthogonality(int **matrix, int lenwidth) {
  int i, d, cur_row = 0, sum = 0;

  while (cur_row < lenwidth) {
    for (i = 0; i < lenwidth; i++) {
      if (i != cur_row) {
        for (d = 0; d < lenwidth; d++) {
          sum += (matrix[cur_row][d] * matrix[i][d]);
        }
      }
      if ((sum / lenwidth) != 0)
        return 1;
      sum = 0;
      cur_row++;
    }
  }

  return 0;
}

int **Hadamard(int k) {
  int i, d, o, p, H, cur_exp = 2, lenwidth = 2, prev_lw;
  int **odd_matrix, **even_matrix, **temp_matrix;

  H = pow(2, k);

  temp_matrix = (int **) malloc(2 * sizeof(int *));
  for (i = 0; i < 2; i++)
    temp_matrix[i] = (int *) malloc(2 * sizeof(int));

  odd_matrix = (int **) malloc(2 * sizeof(int *));
  for (i = 0; i < 2; i++)
    odd_matrix[i] = (int *) malloc(2 * sizeof(int));

  even_matrix = (int **) malloc(2 * sizeof(int *));
  for (i = 0; i < 2; i++)
    even_matrix[i] = (int *) malloc(2 * sizeof(int));

  odd_matrix[0][0] = 1;
  odd_matrix[0][1] = 1;
  odd_matrix[1][0] = 1;
  odd_matrix[1][1] = -1;

  while (lenwidth < H) {
    lenwidth = pow(2, cur_exp);
    prev_lw = lenwidth / 2;
    if (cur_exp % 2 == 0) {
      temp_matrix = (int **) realloc(even_matrix, lenwidth * sizeof(int *));
      if (temp_matrix == NULL) {
        printf("realloc() fail\n");
        Release_Matrix(temp_matrix, k);
        exit(0);
      }
      else {
        even_matrix = temp_matrix;

        // Compute top-left block matrix
        for (i = 0; i < prev_lw; i++) {
          even_matrix[i] = (int *) malloc(lenwidth * sizeof(int));
          for (d = 0; d < prev_lw; d++) {
            even_matrix[i][d] = odd_matrix[i][d];
          }
        }

        // Compute top-right block matrix
        for (i = 0, o = 0; i < prev_lw; i++, o++) {
          for (d = prev_lw, p = 0; d < lenwidth; d++, p++) {
            even_matrix[i][d] = odd_matrix[o][p];
          }
        }

        // Compute bottom-left block matrix
        for (i = prev_lw, o = 0; i < lenwidth; i++, o++) {
          even_matrix[i] = (int *) malloc(lenwidth * sizeof(int));
          for (d = 0; d < prev_lw; d++) {
            even_matrix[i][d] = odd_matrix[o][d];
          }
        }

        // Compute bottom-right block matrix
        for (i = prev_lw, o = 0; i < lenwidth; i++, o++) {
          for (d = prev_lw, p = 0; d < lenwidth; d++, p++) {
            even_matrix[i][d] = -1 * odd_matrix[o][p];
          }
        }
      }
    }
    else {
      temp_matrix = (int **) realloc(odd_matrix, lenwidth * sizeof(int *));
      if (temp_matrix == NULL) {
        printf("realloc() fail\n");
        Release_Matrix(temp_matrix, k);
        exit(0);
      }
      else {
        odd_matrix = temp_matrix;

        // Compute top-left block matrix
        for (i = 0; i < prev_lw; i++) {
          odd_matrix[i] = (int *) malloc(lenwidth * sizeof(int));
          for (d = 0; d < prev_lw; d++) {
            odd_matrix[i][d] = even_matrix[i][d];
          }
        }

        // Compute top-right block matrix
        for (i = 0, o = 0; i < prev_lw; i++, o++) {
          for (d = prev_lw, p = 0; d < lenwidth; d++, p++) {
            odd_matrix[i][d] = even_matrix[o][p];
          }
        }

        // Compute bottom-left block matrix
        for (i = prev_lw, o = 0; i < lenwidth; i++, o++) {
          odd_matrix[i] = (int *) malloc(lenwidth * sizeof(int));
          for (d = 0; d < prev_lw; d++) {
            odd_matrix[i][d] = even_matrix[o][d];
          }
        }

        // Compute bottom-right block matrix
        for (i = prev_lw, o = 0; i < lenwidth; i++, o++) {
          for (d = prev_lw, p = 0; d < lenwidth; d++, p++) {
            odd_matrix[i][d] = -1 * even_matrix[o][p];
          }
        }
      }
    }

    cur_exp++;
  }

  if (k % 2 == 0) {
    return even_matrix;
  }

  return odd_matrix;
}

void Release_Matrix(int **matrix, int k) {
  for (int i = 0; i < pow(2, k); i++) {
    free(matrix[i]);
  }
  free(matrix);

  return;
}
