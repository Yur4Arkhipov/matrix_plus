#include "tests.h"

#include <gtest/gtest.h>

#include <cmath>
#include <optional>

#include "../s21_matrix_oop.h"
#include "../util.h"

S21Matrix get_matrix(TestMatrix A) {
  S21Matrix m(A.rows, A.cols);
  int idx = A.start;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      m(i, j) = dataset_values[idx];
      idx++;
    }
  }
  return m;
}

std::optional<S21Matrix> get_matrix_opt(TestMatrixCode A) {
  std::optional<S21Matrix> result;
  if (!A.code) {
    result = get_matrix(A.matrix);
  }
  return result;
}

void run_test_eq(const S21Matrix& A, const S21Matrix& B, const Dataset& test) {
  EXPECT_EQ(A == B, test.eq_result);
}

void run_test_sum(const S21Matrix& A, const S21Matrix& B, const Dataset& test) {
  std::optional<S21Matrix> result_test = get_matrix_opt(test.sum_result);
  if (result_test.has_value()) {
    EXPECT_EQ(A + B, result_test);
  } else {
    EXPECT_THROW(A + B, DifferentMatrixSizeException);
  }
}

void run_test_sub(const S21Matrix& A, const S21Matrix& B, const Dataset& test) {
  std::optional<S21Matrix> result_test = get_matrix_opt(test.sub_result);
  if (result_test.has_value()) {
    EXPECT_EQ(A - B, result_test);
  } else {
    EXPECT_THROW(A - B, DifferentMatrixSizeException);
  }
}

void run_test_mult_number(const S21Matrix& A, const Dataset& test) {
  S21Matrix result_test = get_matrix(test.mult_number_result);
  EXPECT_EQ(A * test.mult_number, result_test);
}

void run_test_mult_matrix(const S21Matrix& A, const S21Matrix& B,
                          const Dataset& test) {
  std::optional<S21Matrix> result_test =
      get_matrix_opt(test.mult_matrix_result);
  if (result_test.has_value()) {
    EXPECT_EQ(A * B, result_test);
  } else {
    EXPECT_THROW(A * B, MultiplicationSizeException);
  }
}

void run_test_transpose(const S21Matrix& A, const Dataset& test) {
  S21Matrix result_test = get_matrix(test.transpose_result);
  EXPECT_EQ(A.Transpose(), result_test);
}

void run_test_calc_complements(const S21Matrix& A, const Dataset& test) {
  std::optional<S21Matrix> result_test =
      get_matrix_opt(test.calc_complements_result);
  if (result_test.has_value()) {
    EXPECT_EQ(A.CalcComplements(), result_test);
  } else {
    EXPECT_THROW(A.CalcComplements(), NonSquareMatrixException);
  }
}

void run_test_determinant(const S21Matrix& A, const Dataset& test) {
  double result_test = test.determinant_result;
  int result_code = test.determinant_code;
  if (!result_code) {
    EXPECT_TRUE(std::fabs(A.Determinant() - result_test) <= 1e-7);
  } else {
    EXPECT_THROW(A.Determinant(), NonSquareMatrixException);
  }
}

void run_test_inverse(const S21Matrix& A, const Dataset& test) {
  std::optional<S21Matrix> result_test = get_matrix_opt(test.inverse_result);
  if (result_test.has_value()) {
    EXPECT_EQ(A.InverseMatrix(), result_test);
  } else {
    EXPECT_THROW(A.InverseMatrix(), NonSquareMatrixException);
  }
}

class GeneratedTests : public ::testing::TestWithParam<int> {};

TEST_P(GeneratedTests, Eq) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  S21Matrix B = get_matrix(dataset_tests[idx].b);
  run_test_eq(A, B, dataset_tests[idx]);
}

TEST_P(GeneratedTests, Sum) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  S21Matrix B = get_matrix(dataset_tests[idx].b);
  run_test_sum(A, B, dataset_tests[idx]);
}

TEST_P(GeneratedTests, Sub) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  S21Matrix B = get_matrix(dataset_tests[idx].b);
  run_test_sub(A, B, dataset_tests[idx]);
}

TEST_P(GeneratedTests, MultNumber) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  run_test_mult_number(A, dataset_tests[idx]);
}

TEST_P(GeneratedTests, MultMatrix) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  S21Matrix B = get_matrix(dataset_tests[idx].b);
  run_test_mult_matrix(A, B, dataset_tests[idx]);
}

TEST_P(GeneratedTests, Transpose) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  run_test_transpose(A, dataset_tests[idx]);
}

TEST_P(GeneratedTests, CalcComplements) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  run_test_calc_complements(A, dataset_tests[idx]);
}

TEST_P(GeneratedTests, Determinant) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  run_test_determinant(A, dataset_tests[idx]);
}

TEST_P(GeneratedTests, Inverse) {
  int idx = GetParam();
  S21Matrix A = get_matrix(dataset_tests[idx].a);
  run_test_inverse(A, dataset_tests[idx]);
}

INSTANTIATE_TEST_CASE_P(Tests, GeneratedTests, ::testing::Range(0, TEST_SIZE));

TEST(Tests, Resize) {
  S21Matrix m;
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m.get_cols(), 1);
  m.set_cols(2);
  EXPECT_DOUBLE_EQ(m(0, 1), 0.0);
  m.set_rows(2);
  EXPECT_DOUBLE_EQ(m(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST(Tests, OutOfRange) {
  S21Matrix m;
  EXPECT_THROW(m(1, 0), std::out_of_range);
  EXPECT_THROW(m(0, 1), std::out_of_range);
}

TEST(Tests, InvalidSize) {
  EXPECT_THROW(S21Matrix(0, 0), IncorrectMatrixSizeException);
}

TEST(Tests, InverseOfZero) {
  S21Matrix m;
  m(0, 0) = 0.0;
  EXPECT_THROW(m.InverseMatrix(), DeterminantIsZeroException);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}