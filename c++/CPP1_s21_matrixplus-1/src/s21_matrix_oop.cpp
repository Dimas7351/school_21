#include "s21_matrix_oop.h"

using namespace std;

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw invalid_argument("Wrong value of rows/columns");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double[rows * cols]{};
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_]{};
  copy(other.matrix_, other.matrix_ + cols_ * rows_, matrix_);
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

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row * cols_ + col];
}

void S21Matrix::SetRows(const int &rows) {
  if (rows < 1) {
    throw invalid_argument("Rows' amount must be greater 0");
  }

  S21Matrix tmp(rows, cols_);

  for (int i = 0; i < min(rows, rows_); i++) {
    for (int j = 0; j < cols_; j++) {
      tmp(i, j) = (*this)(i, j);
    }
  }
  rows_ = rows;
  *this = tmp;
}

void S21Matrix::SetCols(const int &cols) {
  if (cols < 1) {
    throw invalid_argument("Cols' amount must be greater 0");
  }

  S21Matrix temp(rows_, cols);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min(cols, cols_); j++) {
      temp(i, j) = (*this)(i, j);
    }
  }

  *this = move(temp);
}

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs((*this)(i, j) - other(i, j)) > epsilon) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("The sizes of the matrices should be the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw logic_error("The sizes of the matrices should be the same");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw logic_error(
        "Number of columns of the first matrix is not equal to number of rows "
        "of the second matrix");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) = (*this)(i, k) * other(k, j);
      }
    }
  }

  *this = move(result);
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
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


double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw logic_error("Matrix is not squared");
  }

  if (rows_ == 1) return (*this)(0, 0);

  if (rows_ == 2)
    return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));

  double ans = 0.0;
  int sign = 1;
    for (int i = 0; i < rows_; i++) {
      S21Matrix temp(*this);
      temp = (*this).Minor(0,i);

      ans += sign * (*this)(0,i) * temp.Determinant();
      sign *= -1;

    }
  return (fabs(ans) < epsilon) ? 0 : ans;
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

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw logic_error("Matrix is not squared");
  }

  double det = Determinant();
  if (fabs(det) < epsilon) {
    throw logic_error("Determinant is zero");
  }

  S21Matrix result = CalcComplements().Transpose();
  result *= (1 / det);

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
