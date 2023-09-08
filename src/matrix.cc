#include "matrix.h"

namespace custom {
Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!(rows_ > 0 && cols_ > 0)) {
    throw std::out_of_range("Incorrect rows or cols\n");
  }

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

Matrix::Matrix(const Matrix& o) : rows_(o.rows_), cols_(o.cols_) {
  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& o) noexcept : matrix_(nullptr) {
  std::swap(matrix_, o.matrix_);
  std::swap(rows_, o.rows_);
  std::swap(cols_, o.cols_);
}

Matrix::~Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

void Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::out_of_range("Incorrect rows or cols\n");
  }

  Matrix tmp(rows, cols_);
  for (int i = 0; i < std::min(rows, rows_); ++i)
    for (int j = 0; j < cols_; ++j) tmp.matrix_[i][j] = matrix_[i][j];
  *this = tmp;
}

void Matrix::SetColumns(int columns) {
  if (columns < 1) {
    throw std::out_of_range("Incorrect rows or cols\n");
  }

  Matrix tmp(rows_, columns);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < std::min(cols_, columns); ++j)
      tmp.matrix_[i][j] = matrix_[i][j];

  *this = tmp;
}

int Matrix::GetRows() const { return rows_; }

int Matrix::GetColumns() const { return cols_; }

bool Matrix::EqMatrix(const Matrix& other) const {
  if (cols_ != other.cols_ || rows_ != other.rows_) return false;

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      if (matrix_[i][j] != other.matrix_[i][j]) return false;

  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::SubMatrix(const Matrix& other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range("Incorrect input, check rows & cols in matrixes\n");

  for (int r = 0; r < other.rows_; ++r) {
    for (int c = 0; c < other.cols_; ++c) {
      double sum = 0;
      for (int counter_origin = 0; counter_origin < cols_; ++counter_origin)
        sum += matrix_[r][counter_origin] * other.matrix_[counter_origin][c];

      matrix_[r][c] = sum;
    }
  }
}

Matrix Matrix::Transpose() const {
  Matrix return_matrix(cols_, rows_);

  for (int r = 0; r < return_matrix.rows_; ++r) {
    for (int c = 0; c < return_matrix.cols_; ++c) {
      return_matrix.matrix_[r][c] = matrix_[c][r];
    }
  }

  return return_matrix;
}

double Matrix::Determinant() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix is not square!\n");
  if (cols_ == 1) return matrix_[0][0];
  if (cols_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

  double det = 0;
  for (int i = 0, firstRowOfMatrix = 0; i < rows_; ++i) {
    Matrix a = minorMatrix(firstRowOfMatrix, i);
    det += matrix_[0][i] * ((i & 1) ? -1 : 1) * a.Determinant();
  }
  return det;
}

Matrix Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::out_of_range("Matrix is not square!\n");

  Matrix return_matrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      return_matrix(i, j) = pow(-1, i + j) * minorMatrix(i, j).Determinant();

  return return_matrix;
}

Matrix Matrix::InverseMatrix() const {
  auto a = Determinant();
  if (a == 0) throw std::out_of_range("Det = 0!");
  return CalcComplements().Transpose() * (1 / (a));
}

Matrix Matrix::operator+(const Matrix& o) const {
  Matrix return_matrix(*this);
  return_matrix.SumMatrix(o);
  return return_matrix;
}

Matrix Matrix::operator-(const Matrix& o) const {
  Matrix return_matrix(*this);
  return_matrix.SubMatrix(o);
  return return_matrix;
}

Matrix Matrix::operator*(const Matrix& o) const {
  Matrix return_matrix(*this);
  return_matrix.MulMatrix(o);
  return return_matrix;
}

Matrix Matrix::operator*(const double num) const {
  Matrix return_matrix(*this);
  return_matrix.MulNumber(num);
  return return_matrix;
}

bool Matrix::operator==(const Matrix& o) const { return EqMatrix(o); }

Matrix& Matrix::operator=(const Matrix& o) {
  if (this == &o) return *this;
  this->~Matrix();

  rows_ = o.rows_;
  cols_ = o.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator+=(const Matrix& o) {
  SumMatrix(o);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& o) {
  SubMatrix(o);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& o) {
  MulMatrix(o);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& Matrix::operator()(int row, int col) {
  if (row > rows_ || col > cols_)
    throw std::out_of_range("Incorrect row or col\n");
  if (row < 0 || col < 0) throw std::out_of_range("Incorrect row or col\n");
  return matrix_[row][col];
}

const double& Matrix::operator()(int row, int col) const {
  if (row > rows_ || col > cols_)
    throw std::out_of_range("Incorrect row or col\n");
  if (row < 0 || col < 0) throw std::out_of_range("Incorrect row or col\n");
  return matrix_[row][col];
}

Matrix Matrix::minorMatrix(int extra_row, int extra_col) const {
  Matrix return_matrix(rows_ - 1, cols_ - 1);

  for (int i = 0, new_row = 0; new_row < return_matrix.rows_; ++i) {
    if (i == extra_row) continue;

    for (int j = 0, newCol = 0; newCol < return_matrix.cols_; ++j)
      if (j != extra_col)
        return_matrix.matrix_[new_row][newCol++] = matrix_[i][j];

    ++new_row;
  }
  return return_matrix;
}

};  // namespace custom
