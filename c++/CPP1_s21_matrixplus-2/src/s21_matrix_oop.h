#ifndef CPP_S21_MATRIX_H_
#define CPP_S21_MATRIX_H_

#include <algorithm>
#include <cmath>
#include <stdexcept>

#define epsilon 1e-07

class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;

 public:
  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);  // Конструктор копирования
  S21Matrix(S21Matrix &&other);  // Конструктор перемещения

  // Destructor
  ~S21Matrix();

  // Setters
  void SetRows(const int &rows);
  void SetCols(const int &cols);

  // Getters
  int GetRows() const noexcept;
  int GetCols() const noexcept;

  // Functions
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

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

  // Help_functions
  S21Matrix Minor(int row, int col) const;
  void Swap(int first, int second);
  void Gauss(int *factor);
  void AddRow(int first, int second, double factory);
};

#endif  // CPP_S21_MATRIX_H_