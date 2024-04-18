#ifndef MATRIX_CPP_LIBRARY_H
#define MATRIX_CPP_LIBRARY_H

#define EPS 1e-6

#include <stdlib.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace Matrix {
class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;

 public:
  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);

  // Destructor
  ~S21Matrix();

  // Operators
  double &operator()(int row, int col) const;
  bool operator==(const S21Matrix &other) noexcept;
  bool operator!=(const S21Matrix &other) noexcept;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);

  // Setters
  void SetCols(const int &cols);
  void SetRows(const int &rows);

  // Getters
  constexpr int GetCols() const noexcept { return cols_; };
  constexpr int GetRows() const noexcept { return rows_; };

  // Functions
  void SumMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  double Determinant() const;
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  // Helpers
  void Gauss(int *factor);
  S21Matrix Minor(int row, int col) const;
  void Swap(int first, int second);
  void AddRow(int first, int second, double factory);
};
}  // namespace Matrix

#endif  // MATRIX_CPP_LIBRARY_H
