#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

void set_matrix(matrix_t *A, double in_matrix[][10]) {
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) A->matrix[i][j] = in_matrix[i][j];
}

START_TEST(CREATTest01) {
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(3, 4, &matrix), 0);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(CREATTest02) {
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(0, 4, &matrix), 1);
}
END_TEST

START_TEST(CREATTest03) {
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(3, -2, &matrix), 1);
}
END_TEST

START_TEST(CREATTest04) {
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(0, 0, &matrix), 1);
}
END_TEST

START_TEST(EQUALTest01) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix2), 0);

  double in_mat1[10][10] = {{1.5123456, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  double in_mat2[10][10] = {{1.5123456, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(EQUALTest02) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 0.512344578, 4.5}, {4.5, 5.5, 8.5}};
  double in_mat2[10][10] = {{1.5, 0.512345578, 4.5}, {4.5, 5.5, 8.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(EQUALTest03) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 3, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  double in_mat2[10][10] = {{1.5, 0.5, 4.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(EQUALTest04) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(1, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 1, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}};
  double in_mat2[10][10] = {{1.5}, {0.5}, {4.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(EQUALTest05) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix2), 0);

  double in_mat1[10][10] = {{1.5}};
  double in_mat2[10][10] = {{1.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(EQUALTest06) {
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(10, 15, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(10, 15, &matrix2), 0);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(SUMTest01) {
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{3.0, 6.5, 6.5}, {3.5, 8, 16}, {6.5, 10, 11}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_sum_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(SUMTest02) {
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_sum_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(SUBTest01) {
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{0.0, -1.5, 2.5}, {2.5, 2, -4}, {-2.5, 4, 7}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_sub_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(SUBTest02) {
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_sub_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(MULTNTest01) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_etalon[10][10] = {{3.0, 5.0, 9.0}, {6, 10, 12}, {4, 14, 18}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_number(&matrix1, 2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(MULTNTest02) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_etalon[10][10] = {{0.0, 0.0, 0.0}, {0, 0, 0}, {0, 0, 0}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_number(&matrix1, 0, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(MULTMTest01) {
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{23.75, 27, 37}, {34, 45, 68}, {47, 56, 92}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(MULTMTest02) {
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(5, 2, &etalon), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_mat2[10][10] = {{1.5, 4}, {0.5, 3}, {4.5, 3}};
  double in_etalon[10][10] = {
      {23.75, 27}, {34, 45}, {0, 79}, {37, 49}, {18, 54}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(MULTMTest03) {
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(2, 2, &matrix2), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_mat2[10][10] = {{1.5, 4}, {0.5, 3}, {4.5, 3}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(TRANSTest01) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 5, &etalon), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_etalon[10][10] = {
      {1.5, 3, 13, 1, 6}, {2.5, 5, 15, 8, 9}, {4.5, 6, -6, 7, 1}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_transpose(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(TRANSTest02) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 1, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 5, &etalon), 0);

  double in_mat1[10][10] = {{1.5}, {3}, {13}, {1}, {6}};
  double in_etalon[10][10] = {{1.5, 3, 13, 1, 6}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_transpose(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(DETERTest01) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 8},
                            {3, 5, 6, -2, 0},
                            {13, 15, -6, 2, 9},
                            {1, 8, 7, 12, -23},
                            {6, 9, 1, 10, 0}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 20006;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest02) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 0;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest03) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}};

  set_matrix(&matrix1, in_mat1);

  double result;
  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 2);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest04) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(2, 2, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2}, {4, 5}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -3;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest05) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix1), 0);

  double in_mat1[10][10] = {{666}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 666;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest06) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 0},
                            {3, 0, 6, -2, 0},
                            {13, 15, -6, 0, 9},
                            {1, 0, 7, 12, -23},
                            {6, 9, 1, 0, 0}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -33416;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest07) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(6, 6, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 0, 8}, {3, 0, 6, -2, 0, 7},
                            {13, 15, -6, 0, 9, 5},    {1, 0, 7, 12, -23, 3},
                            {6, 9, 1, 0, 0, 2},       {4, 7, -3, -2, 4, 8}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -344160;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(DETERTest08) {
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(4, 4, &matrix1), 0);

  double in_mat1[10][10] = {
      {1, 2, 3, 4}, {4, 0, 0, 3}, {0, 3, 3, 1}, {0, 7, 2, 6}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 199;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, 1E-7);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(COMPLTest01) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double in_etalon[10][10] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_calc_complements(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(COMPLTest02) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double in_etalon[10][10] = {{-1, 38, -27}, {1, -41, 29}, {-1, 34, -24}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_calc_complements(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(COMPLTest03) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(5, 5, &etalon), 0);

  double in_mat1[10][10] = {{1, 0, 3, 7, 9},
                            {4, 6, 2, 3, 7},
                            {5, -2, -3, 6, 2},
                            {1, 1, 0, 7, 8},
                            {-5, 4, 8, 7, 2}};

  double in_etalon[10][10] = {{1427, -2556, 2781, -985, 1003},
                              {1161, 1240, 411, -351, 7},
                              {1481, -284, 309, 1213, -1211},
                              {-2924, 1726, -3680, 884, 864},
                              {-270, 542, 458, 912, -832}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_calc_complements(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(COMPLTest04) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(5, 5, &etalon), 0);

  double in_mat1[10][10] = {{1, 0, 0, 0, 0},
                            {0, 2, 0, 0, 0},
                            {0, 0, 3, 0, 0},
                            {0, 0, 0, 4, 0},
                            {0, 0, 0, 0, 5}};

  double in_etalon[10][10] = {{120, 0, 0, 0, 0},
                              {0, 60, 0, 0, 0},
                              {0, 0, 40, 0, 0},
                              {0, 0, 0, 30, 0},
                              {0, 0, 0, 0, 24}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_calc_complements(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(INVERSTest01) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double in_etalon[10][10] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(INVERSTest02) {
  matrix_t matrix1, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  set_matrix(&matrix1, in_mat1);
  ck_assert_uint_eq(s21_inverse_matrix(&matrix1, &result), 2);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(INVERSTest03) {
  matrix_t matrix1, result;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}};
  set_matrix(&matrix1, in_mat1);
  ck_assert_uint_eq(s21_inverse_matrix(&matrix1, &result), 2);

  s21_remove_matrix(&matrix1);
}
END_TEST

START_TEST(INVERSTest04) {
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(4, 4, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(4, 4, &etalon), 0);

  double in_mat1[10][10] = {
      {1, 2, 3, 4}, {4, 0, 0, 3}, {0, 3, 3, 1}, {0, 7, 2, 6}};
  double in_etalon[10][10] = {
      {-45.0 / 199.0, 61.0 / 199.0, 51.0 / 199.0, -9.0 / 199.0},
      {-64.0 / 199.0, 16.0 / 199.0, 46.0 / 199.0, 27.0 / 199.0},
      {44.0 / 199.0, -11.0 / 199.0, 43.0 / 199.0, -31.0 / 199.0},
      {60.0 / 199.0, -15.0 / 199.0, -68.0 / 199.0, 12.0 / 199.0}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_inverse_matrix(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

int main() {
  int number_failed;
  Suite *my_suite = suite_create("Test_matrix");
  TCase *MatrixTest = tcase_create("MATRIX");
  SRunner *sr = srunner_create(my_suite);

  suite_add_tcase(my_suite, MatrixTest);
  tcase_add_test(MatrixTest, CREATTest01);
  tcase_add_test(MatrixTest, CREATTest02);
  tcase_add_test(MatrixTest, CREATTest03);
  tcase_add_test(MatrixTest, CREATTest04);

  tcase_add_test(MatrixTest, EQUALTest01);
  tcase_add_test(MatrixTest, EQUALTest02);
  tcase_add_test(MatrixTest, EQUALTest03);
  tcase_add_test(MatrixTest, EQUALTest04);
  tcase_add_test(MatrixTest, EQUALTest05);
  tcase_add_test(MatrixTest, EQUALTest06);

  tcase_add_test(MatrixTest, SUMTest01);
  tcase_add_test(MatrixTest, SUMTest02);

  tcase_add_test(MatrixTest, SUBTest01);
  tcase_add_test(MatrixTest, SUBTest02);

  tcase_add_test(MatrixTest, MULTNTest01);
  tcase_add_test(MatrixTest, MULTNTest02);

  tcase_add_test(MatrixTest, MULTMTest01);
  tcase_add_test(MatrixTest, MULTMTest02);
  tcase_add_test(MatrixTest, MULTMTest03);

  tcase_add_test(MatrixTest, TRANSTest01);
  tcase_add_test(MatrixTest, TRANSTest02);

  tcase_add_test(MatrixTest, DETERTest01);
  tcase_add_test(MatrixTest, DETERTest02);
  tcase_add_test(MatrixTest, DETERTest03);
  tcase_add_test(MatrixTest, DETERTest04);
  tcase_add_test(MatrixTest, DETERTest05);
  tcase_add_test(MatrixTest, DETERTest06);
  tcase_add_test(MatrixTest, DETERTest07);
  tcase_add_test(MatrixTest, DETERTest08);

  tcase_add_test(MatrixTest, COMPLTest01);
  tcase_add_test(MatrixTest, COMPLTest02);
  tcase_add_test(MatrixTest, COMPLTest03);
  tcase_add_test(MatrixTest, COMPLTest04);

  tcase_add_test(MatrixTest, INVERSTest01);
  tcase_add_test(MatrixTest, INVERSTest02);
  tcase_add_test(MatrixTest, INVERSTest03);
  tcase_add_test(MatrixTest, INVERSTest04);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}