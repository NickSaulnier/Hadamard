#ifndef HADAMARD_H_
#define HADAMARD_H_

int Check_Matrix_Orthogonality(int **matrix, int lenwidth);
/* This method takes a square matrix as input and determines whether its rows
   are all orthogonal with each other; that is, this function determines whether
   the input matrix is a Hadamard matrix.

Args:
  matrix (int **): A square matrix.
  lenwidth (int): The length of of the matrices sides.

Returns:
  (int): The program returns 0 if the matrix is found to be orthogonal and 1
    otherwise.

*/

int **Hadamard(int k);
/* This function computes a Hadamard matrix with 2^k dimensions.

Args:
  k (int): Each row of the matrix is a Walsh code of 2^k bits.

Returns:
  (int **): A hadamard matrix of 2^k dimensions.

*/

void Release_Matrix(int **matrix, int k);
/*  Free a 2D square matrix.

Args:
  k (int): The matrix had 2^k rows; rows are 2^k in length.

Returns:
  (void)

*/

#endif
