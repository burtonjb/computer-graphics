#include "../src/custom_math.h"
#include "../src/linear_algebra.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 0.001

void assert_matrix_equals(Matrix3_double a, Matrix3_double b) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      assert(a[i][j] - b[i][j] < EPSILON);
    }
  }
}

void test_45_degree_rotation() {
  const double angle = M_PI / 4;
  Vector3_double v = {1, 1, 1};
  Vector3_double out = {0, 0, 0};
  Matrix3_double A = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};
  matrix_vector_multiply_d(&A, &v, &out);
  assert((0 - out[0]) < EPSILON);
  assert((1.414214 - out[1]) < EPSILON);
}

void test_30_degree_rotation() {
  const double angle = M_PI / 3;
  Vector3_double v = {10, 10, 1};
  Vector3_double out = {0, 0, 0};
  Matrix3_double A = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};
  matrix_vector_multiply_d(&A, &v, &out);
  assert((-3.660254 - out[0]) < EPSILON);
  assert((13.660254 - out[1] < EPSILON));
}

void translate_rotate_matrix() {
  const double angle = M_PI / 3;
  Vector3_double v = {10, 10, 1};
  Vector3_double v_out;

  Matrix3_double rotate = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

  Matrix3_double translate = {{1, 0, 10}, {0, 1, 10}, {0, 0, 1}};

  Matrix3_double out;

  matrix_multiply_d(&translate, &rotate, &out);

  matrix_vector_multiply_d(&out, &v, &v_out);

  assert((6.339746 - v_out[0]) < EPSILON);
  assert((23.660254 - v_out[1] < EPSILON));
}

test_inverting_matrix() {
  // invert identity
  Matrix3_double out = {{1, 1, 1},
                        {1, 1, 1},
                        {1, 1, 1}}; // value doesn't matter, its overwritten.
  Matrix3_double iden = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  int res = invert_matrix_d(&iden, &out);
  assert(0 == res);
  assert_matrix_equals(iden, out);

  // invert non-invertable matrix
  Matrix3_double no_inverse = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  res = invert_matrix_d(&no_inverse, &out);
  assert(1 == res);

  // invert invertable matrix
  Matrix3_double test_matrix = {{0, -3, -2}, {1, -4, -2}, {-3, 4, 1}};
  Matrix3_double expected = {{4, -5, -2}, {5, -6, -2}, {-8, 9, 3}};
  res = invert_matrix_d(&test_matrix, &out);
  assert(0 == res);
  assert_matrix_equals(out, expected);
}

test_compute_determinant() {
  double det;

  Matrix3_double iden = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  det = determinant_matrix_d(iden);
  assert(1 == det);

  Matrix3_double all_zero = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  assert(0 == determinant_matrix_d(&all_zero));

  Matrix3_double some_matrix = {{4, -3, 0}, {2, -1, 2}, {1, 5, 7}};
  assert(-32 == determinant_matrix_d(&some_matrix));
}

int main(int argc, char *argv[]) {
  test_45_degree_rotation();
  test_30_degree_rotation();
  translate_rotate_matrix();
  test_inverting_matrix();
  test_compute_determinant();
}
