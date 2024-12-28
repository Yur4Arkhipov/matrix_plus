#ifndef TESTS_H
#define TESTS_H

#define TEST_SIZE 625

#define OK 0
#define CALCULATION_ERROR 1

struct TestMatrix {
  int rows;
  int cols;
  int start;
};

struct TestMatrixCode {
  TestMatrix matrix;
  int code;
};

struct Dataset {
  TestMatrix a;
  TestMatrix b;

  int eq_result;

  TestMatrixCode sum_result;
  TestMatrixCode sub_result;

  double mult_number;
  TestMatrix mult_number_result;
  TestMatrixCode mult_matrix_result;

  TestMatrix transpose_result;

  TestMatrixCode calc_complements_result;
  int determinant_code;
  double determinant_result;
  TestMatrixCode inverse_result;
};

extern const double dataset_values[];
extern const Dataset dataset_tests[];

#endif
