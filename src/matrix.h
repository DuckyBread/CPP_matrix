#ifndef _CPP_MATRIX_MATRIX_H_
#define _CPP_MATRIX_MATRIX_H_

#include <math.h>
#include <stdio.h>

#include <exception>
#include <iostream>

namespace custom {
class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& o);
  Matrix(Matrix&& o) noexcept;
  ~Matrix();

  Matrix& operator=(const Matrix& o);
  bool operator==(const Matrix& o) const;
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;
  Matrix& operator+=(const Matrix& o);
  Matrix& operator-=(const Matrix& o);
  Matrix operator-(const Matrix& o) const;
  Matrix operator+(const Matrix& o) const;
  Matrix operator*(const Matrix& o) const;
  Matrix operator*(const double num) const;
  Matrix& operator*=(const Matrix& o);
  Matrix& operator*=(const double num);

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;
  void SetRows(int rows);
  void SetColumns(int columns);
  int GetRows() const;
  int GetColumns() const;

 private:
  Matrix minorMatrix(int extraRow, int extraCol) const;

  int rows_;
  int cols_;
  double** matrix_;
};
};  // namespace custom

#endif  // CPP_MATRIX_MATRIX_H_
