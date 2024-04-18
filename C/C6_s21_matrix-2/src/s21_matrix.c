#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 1;
  if ((rows < 1) || (columns < 1) || result == NULL) {
    res = 0;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL)
      res = 0;
    else
      for (int i = 0; i < rows; i++)
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }
  return (res ? 0 : 1);
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);
  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

int correct_matrix(matrix_t *A) {
  return A && (A->rows > 0) && A->columns > 0 && A->matrix;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;

  if (A->rows != B->rows || A->columns != B->columns) res = 0;

  if (!correct_matrix(A) || !correct_matrix(B)) res = 0;

  if (res)
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) res = 0;

  return SUCCESS ? res : FAILURE;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A) || !correct_matrix(B))
    res = 1;
  else if (A->rows != B->rows || A->columns != B->columns)
    res = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A) || !correct_matrix(B))
    res = 1;
  else if (A->rows != B->rows || A->columns != B->columns)
    res = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A))
    res = 1;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = number * A->matrix[i][j];
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A) || !correct_matrix(B))
    res = 1;
  else if (A->columns != B->rows)
    res = 2;
  else if (s21_create_matrix(A->rows, B->columns, result) != 0)
    res = 1;
  else
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++)
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A))
    res = 1;
  else if (s21_create_matrix(A->columns, A->rows, result) != 0)
    res = 1;
  else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A))
    res = 1;
  else if (A->rows != A->columns)
    res = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == 1)
      result->matrix[0][0] = A->matrix[0][0];
    else {
      int sign;
      matrix_t temp;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_minor(i, j, A, &temp);
          sign = ((i + j) % 2 == 0) ? 1 : -1;
          double temp_det = 0;
          s21_determinant(&temp, &temp_det);
          result->matrix[i][j] = temp_det * sign;
          s21_remove_matrix(&temp);
        }
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (!correct_matrix(A))
    res = 1;
  else if (A->rows != A->columns)
    res = 2;
  else
    *result = determinant_matrix(A);
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!correct_matrix(A))
    res = 1;
  else if (A->rows != A->columns)
    res = 2;
  else {
    double determinant = determinant_matrix(A);
    if (fabs(determinant) < 1e-7)
      res = 2;
    else {
      matrix_t comp, trans;
      s21_calc_complements(A, &comp);
      s21_transpose(&comp, &trans);
      s21_mult_number(&trans, 1 / determinant, result);
      s21_remove_matrix(&comp);
      s21_remove_matrix(&trans);
    }
  }
  return res;
}

double determinant_matrix(matrix_t *A) {
  double result = 0;
  if (A->rows == 1)
    result = A->matrix[0][0];
  else if (A->rows == 2)
    result = (A->matrix[0][0] * A->matrix[1][1]) -
             (A->matrix[0][1] * A->matrix[1][0]);
  else {
    int sign = 1;
    for (int i = 0; i < A->rows; i++) {
      matrix_t temp;
      matrix_minor(0, i, A, &temp);

      result += sign * A->matrix[0][i] * determinant_matrix(&temp);
      sign *= -1;

      s21_remove_matrix(&temp);
    }
  }
  return result;
}

void matrix_minor(int row, int column, matrix_t *M, matrix_t *result) {
  s21_create_matrix(M->rows - 1, M->columns - 1, result);
  int di = 0, dj = 0;
  for (int i = 0; i < result->rows; i++) {
    if (i == row) di = 1;
    dj = 0;
    for (int j = 0; j < result->columns; j++) {
      if (j == column) dj = 1;
      result->matrix[i][j] = M->matrix[i + di][j + dj];
    }
  }
}
