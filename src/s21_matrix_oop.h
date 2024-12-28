#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <exception>
#include <iostream>
#include <memory>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void createMatrix();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;

  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(S21Matrix other);
  const S21Matrix& operator+=(const S21Matrix& other);
  const S21Matrix& operator-=(const S21Matrix& other);
  const S21Matrix& operator*=(const double num);
  const S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int i, int j) const;

  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);
  void changeMatrixValue(int row, int col, double newValue);
  double getMatrixValue(int row, int col) const;

  void shrMatrix(S21Matrix* minor, int row_to_skip, int col_to_skip) const;
  void getMinorMatrix(S21Matrix* minor, S21Matrix* result, int size) const;
};

#endif