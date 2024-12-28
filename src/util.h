#ifndef UTIL_H
#define UTIL_H

#include "s21_matrix_oop.h"

class IncorrectMatrixSizeException : public std::exception {
 private:
  std::string message;

 public:
  IncorrectMatrixSizeException(const std::string& message);
  const char* what() const noexcept override;
};

class DifferentMatrixSizeException : public std::exception {
 private:
  std::string message;

 public:
  DifferentMatrixSizeException(const std::string& message);
  const char* what() const noexcept override;
};

class ZeroDeterminantException : public std::exception {
 private:
  std::string message;

 public:
  ZeroDeterminantException(const std::string& message);
  const char* what() const noexcept override;
};

class MultiplicationSizeException : public std::exception {
 private:
  std::string message;

 public:
  MultiplicationSizeException(const std::string& message);
  const char* what() const noexcept override;
};

class NonSquareMatrixException : public std::exception {
 private:
  std::string message;

 public:
  NonSquareMatrixException(const std::string& message);
  const char* what() const noexcept override;
};

class DeterminantIsZeroException : public std::exception {
 private:
  std::string message;

 public:
  DeterminantIsZeroException(const std::string& message);
  const char* what() const noexcept override;
};

#endif