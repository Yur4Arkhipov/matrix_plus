#include "s21_matrix_oop.h"

#include "util.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw IncorrectMatrixSizeException("Matrix is not valid for create");
  }
  createMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    delete[] matrix_[0];
    delete[] matrix_;
  }
}

void S21Matrix::createMatrix() {
  std::unique_ptr<double*[]> pointers_array =
      std::make_unique<double*[]>(rows_);
  std::unique_ptr<double[]> values_array =
      std::make_unique<double[]>(rows_ * cols_);
  for (int i = 0; i < rows_; ++i) {
    pointers_array[i] = &values_array[cols_ * i];
  }
  values_array.release();
  matrix_ = pointers_array.release();
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = rows_ == other.rows_ && cols_ == other.cols_;

  for (int i = 0; i < rows_ && res; ++i) {
    for (int j = 0; j < cols_ && res; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        res = std::fabs(matrix_[i][j] - other.matrix_[i][j]) < 1e-7;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw DifferentMatrixSizeException(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw DifferentMatrixSizeException(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw MultiplicationSizeException(
        "Cols of first matrix must be same with rows other matrix");
  }

  S21Matrix new_matrix = S21Matrix(rows_, other.cols_);
  for (int i = 0; i < new_matrix.rows_; i++) {
    for (int j = 0; j < new_matrix.cols_; j++) {
      new_matrix.matrix_[i][j] = 0.0;
      for (int k = 0; k < this->cols_; k++) {
        new_matrix.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = new_matrix;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res = S21Matrix(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  int size = rows_;
  if (rows_ != cols_) {
    throw NonSquareMatrixException("Matrix is not square");
  }
  S21Matrix res = S21Matrix(rows_, cols_);
  if (size == 1) {
    res.matrix_[0][0] = 1;
  } else {
    S21Matrix minor = S21Matrix(rows_ - 1, cols_ - 1);
    this->getMinorMatrix(&minor, &res, size);
  }

  return res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw NonSquareMatrixException("Matrix is not square");
  }

  int size = rows_;

  if (size == 1) {
    return matrix_[0][0];
  }

  S21Matrix minor = S21Matrix(rows_ - 1, cols_ - 1);
  double determinant_sum = 0;

  for (int col = 0; col < size; col++) {
    this->shrMatrix(&minor, 0, col);

    double minor_det = minor.Determinant();
    if (col % 2 == 0) {
      determinant_sum += this->getMatrixValue(0, col) * minor_det;
    } else {
      determinant_sum -= this->getMatrixValue(0, col) * minor_det;
    }
  }
  return determinant_sum;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw NonSquareMatrixException("Matrix is not square");
  }

  int size = rows_;
  S21Matrix res = S21Matrix(rows_, cols_);
  S21Matrix complements = S21Matrix(rows_, cols_);
  S21Matrix transposed = S21Matrix(rows_, cols_);
  double det = this->Determinant();
  if (std::fabs(det) < 1e-7) {
    throw DeterminantIsZeroException("Determinant is so small or zero");
  }
  complements = this->CalcComplements();
  transposed = complements.Transpose();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      res.changeMatrixValue(i, j, transposed.getMatrixValue(i, j) / det);
    }
  }

  return res;
}

int S21Matrix::get_rows() const { return this->rows_; }

void S21Matrix::set_rows(int rows) {
  S21Matrix new_matrix = S21Matrix(rows, cols_);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < rows_) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      } else {
        new_matrix.matrix_[i][j] = 0.0;
      }
    }
  }
  *this = new_matrix;
}

int S21Matrix::get_cols() const { return this->cols_; }

void S21Matrix::set_cols(int cols) {
  S21Matrix new_matrix = S21Matrix(rows_, cols);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_) {
        new_matrix.matrix_[i][j] = matrix_[i][j];
      } else {
        new_matrix.matrix_[i][j] = 0.0;
      }
    }
  }

  *this = new_matrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res = S21Matrix(*this);
  res += other;
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res = S21Matrix(*this);
  res -= other;
  return res;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res = S21Matrix(*this);
  res *= num;
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res = S21Matrix(*this);
  res *= other;
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(S21Matrix other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

const S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

const S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

const S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

const S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("This value not allowed. Matrix out of range.");
  }
  return matrix_[i][j];
}