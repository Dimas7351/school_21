#include "s21_matrix_oop.h"

using namespace Matrix;
using namespace std;

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Wrong value of rows/columns");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double[rows * cols];
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_];
  copy_n(other.matrix_, rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (this != &other) {
    rows_ = exchange(other.rows_, 0);
    cols_ = exchange(other.cols_, 0);
    matrix_ = exchange(other.matrix_, nullptr);
  }
}

S21Matrix::~S21Matrix() {
  cols_ = 0;
  rows_ = 0;
  delete[] matrix_;
}

void S21Matrix::SetCols(const int &cols) {
  if (cols < 1) {
    throw invalid_argument("Cols must be greater 0");
  }

  S21Matrix temp(rows_, cols);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min(cols, cols_); j++) {
      temp(i, j) = (*this)(i, j);
    }
  }

  cols_ = cols;
  *this = temp;
}

void S21Matrix::SetRows(const int &rows) {
  if (rows < 1) {
    throw invalid_argument("Rows must be greater 0");
  }

  S21Matrix temp(rows, cols_);

  for (int i = 0; i < min(rows, rows_); i++) {
    for (int j = 0; j < cols_; j++) {
      temp(i, j) = (*this)(i, j);
    }
  }

  rows_ = rows;
  *this = temp;
}

double &S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0) {
    throw logic_error("Row and col must be greater 0");
  }

  if (row > rows_ || col > cols_) {
    throw logic_error(
        "Row and col must be smaller or equal matrix col and row");
  }

  return matrix_[row * cols_ + col];
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("The dimension of the matrices should be the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("The dimension of the matrices should be the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw logic_error(
        "Number of columns of the first matrix is not equal to number of rows "
        "of the second matrix");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) = (*this)(i, k) * other(k, j);
      }
    }
  }

  *this = move(result);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs((*this)(i, j) - other(i, j)) >= EPS) {
        return false;
      }
    }
  }

  return true;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) noexcept {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) noexcept {
  return !EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;

    delete[] matrix_;
    matrix_ = new double[other.rows_ * other.cols_];
    copy_n(other.matrix_, other.rows_ * other.cols_, matrix_);
  }

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
    swap(matrix_, other.matrix_);
  }

  return *this;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }

  return result;
}

S21Matrix S21Matrix::Minor(int row, int col) const {
  S21Matrix result(rows_ - 1, cols_ - 1);

  int di = 0, dj = 0;

  for (int i = 0; i < result.rows_; i++) {
    if (i == row) di = 1;
    dj = 0;

    for (int j = 0; j < result.cols_; j++) {
      if (j == col) dj = 1;
      result(i, j) = (*this)(i + di, j + dj);
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw logic_error("Matrix is not squared");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result(0, 0) = (*this)(0, 0);
    return result;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = Minor(i, j);
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      result(i, j) = minor.Determinant() * sign;
    }
  }

  return result;
}

void S21Matrix::Swap(int first, int second) {
  if (first >= rows_ || second >= rows_ || first < 0 || second < 0) {
    throw invalid_argument("Invalid rows argument");
  }

  for (int i = 0; i < cols_; i++) {
    swap((*this)(first, i), (*this)(second, i));
  }
}

void S21Matrix::AddRow(int first, int second, double factory) {
  if (first >= rows_ || second >= rows_ || first < 0 || second < 0) {
    throw invalid_argument("Invalid rows argument");
  }

  for (int i = 0; i < cols_; i++) {
    (*this)(second, i) += (*this)(first, i) * factory;
  }
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw logic_error("Matrix is not squared");
  }

  if (rows_ == 1) return (*this)(0, 0);

  if (rows_ == 2)
    return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));

  double ans = 1.0;
  int factory = 1;
  S21Matrix temp(*this);
  temp.Gauss(&factory);

  ans *= factory;

  for (int i = 0; i < rows_; i++) {
    ans *= temp(i, i);
  }

  return (fabs(ans) < EPS) ? 0 : ans;
}

void S21Matrix::Gauss(int *factor) {
  for (int i = 0; i < min(rows_, cols_); i++) {
    double elem = (*this)(i, i);
    int ind = i;

    for (int j = i + 1; j < rows_; j++) {
      if (fabs((*this)(j, i)) > fabs(elem)) {
        elem = (*this)(i, i);
        ind = j;
      }
    }

    if (fabs(elem) < EPS) continue;

    if (ind != i) {
      *factor *= -1;
      Swap(i, ind);
    }

    for (int j = i + 1; j < rows_; j++) {
      AddRow(i, j, (-1) * (*this)(j, i) / (*this)(i, i));
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw logic_error("Matrix is not squared");
  }

  double det = Determinant();
  if (fabs(det) < EPS) {
    throw logic_error("Determinant is zero");
  }

  S21Matrix result = CalcComplements().Transpose();
  result *= (1 / det);

  return result;
}