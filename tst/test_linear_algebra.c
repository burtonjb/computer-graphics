#include "../src/custom_math.h"
#include "../src/linear_algebra.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_45_degree_rotation() {
  const double angle = M_PI / 4;
  Vector3_d v = {1, 1, 1};
  Vector3_d out = {0, 0, 0};
  Matrix3_d A = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};
  matrix_multiply_d(&A, &v, &out);
  printf("%f, %f\n", out[0], out[1]);
}

void test_30_degree_rotation() {
  const double angle = M_PI / 3;
  Vector3_d v = {10, 10, 1};
  Vector3_d out = {0, 0, 0};
  Matrix3_d A = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};
  matrix_multiply_d(&A, &v, &out);
  printf("%f, %f\n", out[0], out[1]);
}

void translate_rotate_matrix() {
  const double angle = M_PI / 3;
  Vector3_d v = {10, 10, 1};
  Vector3_d v_out;

  Matrix3_d rotate = {
      {cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

  Matrix3_d translate = {{1, 0, 10}, {0, 1, 10}, {0, 0, 1}};

  Matrix3_d out;

  create_new_matrix_d(&translate, &rotate, &out);

  print_matrix(&out);

  matrix_multiply_d(&out, &v, &v_out);
  printf("%f, %f\n", v_out[0], v_out[1]);
}

/*
 * Name lies slightly. Doesn't actually assert anything, mostly just used as scratch area to test some math.
 */
int main(int argc, char *argv[]) {
  test_45_degree_rotation();
  test_30_degree_rotation();
  translate_rotate_matrix();
}