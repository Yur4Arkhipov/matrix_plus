#include "util.h"

#include "s21_matrix_oop.h"

void S21Matrix::getMinorMatrix(S21Matrix* minor, S21Matrix* result,
                               int size) const {
  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++) {
      this->shrMatrix(minor, row, col);

      double minor_det = minor->Determinant();
      if ((row + col) % 2 == 1 && minor_det != 0) {
        minor_det *= -1;
      }
      result->changeMatrixValue(row, col, minor_det);
    }
  }
}

void S21Matrix::shrMatrix(S21Matrix* minor, int row_to_skip,
                          int col_to_skip) const {
  int minor_row = 0;
  for (int row = 0; row < this->get_rows(); row++) {
    if (row == row_to_skip) continue;

    int minor_col = 0;
    for (int col = 0; col < this->get_cols(); col++) {
      if (col == col_to_skip) continue;
      minor->changeMatrixValue(minor_row, minor_col,
                               this->getMatrixValue(row, col));
      minor_col++;
    }
    minor_row++;
  }
}

void S21Matrix::changeMatrixValue(int row, int col, double newValue) {
  this->matrix_[row][col] = newValue;
}

double S21Matrix::getMatrixValue(int row, int col) const {
  return matrix_[row][col];
}

// Exception for incorrect matrix size
IncorrectMatrixSizeException::IncorrectMatrixSizeException(
    const std::string& message)
    : message{message} {}
const char* IncorrectMatrixSizeException::what() const noexcept {
  return message.c_str();
}

// Exception for different matrix size
DifferentMatrixSizeException::DifferentMatrixSizeException(
    const std::string& message)
    : message{message} {}
const char* DifferentMatrixSizeException::what() const noexcept {
  return message.c_str();
}

// Exception for different matrix-1 cols and matrix-2 rows for multiplication
MultiplicationSizeException::MultiplicationSizeException(
    const std::string& message)
    : message{message} {}
const char* MultiplicationSizeException::what() const noexcept {
  return message.c_str();
}

// Exception if find non-square matrix
NonSquareMatrixException::NonSquareMatrixException(const std::string& message)
    : message{message} {}
const char* NonSquareMatrixException::what() const noexcept {
  return message.c_str();
}

// Exceprion if determinant is zero
DeterminantIsZeroException::DeterminantIsZeroException(
    const std::string& message)
    : message{message} {}
const char* DeterminantIsZeroException::what() const noexcept {
  return message.c_str();
}