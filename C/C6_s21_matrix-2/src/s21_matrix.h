#ifndef C6_S21_MATRIX_1_S21_MATRIX_H
#define C6_S21_MATRIX_1_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void matrix_minores(int row, int column, matrix_t *M, matrix_t *result);

void matrix_minor(int row, int column, matrix_t *M, matrix_t *result);
int correct_matrix(matrix_t *matrix);
double determinant_matrix(matrix_t *A);

#endif  // C6_S21_MATRIX_1_S21_MATRIX_H