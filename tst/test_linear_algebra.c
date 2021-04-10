#include "../src/custom_math.h"
#include "../src/linear_algebra.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#define EPSILON 0.001

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

/*
 * Name lies slightly. Doesn't actually assert anything, mostly just used as
 * scratch area to test some math.
 */
int main(int argc, char *argv[]) {
  test_45_degree_rotation();
  test_30_degree_rotation();
  translate_rotate_matrix();
}