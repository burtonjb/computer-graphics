#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "custom_math.h"
#include "linear_algebra.h"

#define CONST_UNIT_VECTOR(type)                                                \
  static const Vector3_##type UNIT_VECTOR_##type = {1, 1, 1};
#define CONST_IDENTITY_MATRIX(type)                                            \
  static const Matrix3_##type IDENTITY_MATRIX_##type = {                       \
      {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

#define UNIT_VECTOR_FACTORY(type)                                              \
  Vector3_##type *unit_vector_##type() {                                       \
    Vector3_##type *out = malloc(sizeof(Vector3_##type));                      \
    memcpy(out, &UNIT_VECTOR_##type, sizeof(Vector3_##type));                  \
    return out;                                                                \
  }

#define IDENTITY_MATRIX_FACTOR(type)                                           \
  Matrix3_##type *identity_matrix_##type() {                                   \
    Matrix3_##type *out = malloc(sizeof(Matrix3_##type));                      \
    memcpy(out, &IDENTITY_MATRIX_##type, sizeof(Matrix3_##type));              \
    return out;                                                                \
  }

#define SET_VECTOR_VALUE(type)                                                 \
  void set_vector_value_##type(Vector3_##type *v, const size_t index,          \
                               const type value) {                             \
    (*v)[index] = value;                                                       \
  }
#define SET_MATRIX_VALUE(type)                                                 \
  void set_matrix_value_##type(Matrix3_##type *m, const size_t x,              \
                               const size_t y, const type value) {             \
    (*m)[x][y] = value;                                                        \
  }

CONST_UNIT_VECTOR(uint8_t)
CONST_IDENTITY_MATRIX(uint8_t)
CONST_UNIT_VECTOR(double)
CONST_IDENTITY_MATRIX(double)

UNIT_VECTOR_FACTORY(uint8_t)
IDENTITY_MATRIX_FACTOR(uint8_t)
UNIT_VECTOR_FACTORY(double)
IDENTITY_MATRIX_FACTOR(double)

SET_VECTOR_VALUE(uint8_t)
SET_MATRIX_VALUE(uint8_t)
SET_VECTOR_VALUE(double)
SET_MATRIX_VALUE(double)

void matrix_vector_multiply_uint8(const Matrix3_uint8_t *A,
                                  const Vector3_uint8_t *v,
                                  Vector3_uint8_t *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j, but clamps the values as this is
    // going to be used for pixel operations
    (*out)[i] = clamp_add(clamp_add(clamp_multi((*A)[i][0], (*v)[0]),
                                    clamp_multi((*A)[i][1], (*v)[1])),
                          clamp_multi((*A)[i][2], (*v)[2]));
  }
}

void matrix_vector_multiply_d(const Matrix3_double *A, const Vector3_double *v,
                              Vector3_double *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j
    (*out)[i] = ((*A)[i][0] * (*v)[0]) + ((*A)[i][1] * (*v)[1]) +
                ((*A)[i][2] * (*v)[2]);
  }
}

void matrix_multiply_d(const Matrix3_double *A, const Matrix3_double *B,
                       Matrix3_double *out) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      (*out)[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        // o[i][j] = sum(A[i][k]*B[k][j]) for k = 1 to n
        (*out)[i][j] += (*A)[i][k] * (*B)[k][j];
      }
    }
  }
}

double determinant_matrix_d(const Matrix3_double *A) {
  double d1 = (*A)[0][0] * ((*A)[1][1] * (*A)[2][2] - (*A)[2][1] * (*A)[1][2]);
  double d2 = (*A)[1][0] * ((*A)[0][1] * (*A)[2][2] - (*A)[0][2] * (*A)[2][1]);
  double d3 = (*A)[2][0] * ((*A)[0][1] * (*A)[1][2] - (*A)[1][1] * (*A)[0][2]);
  return d1 - d2 + d3;
}

int invert_matrix_d(const Matrix3_double *in, Matrix3_double *out) {
  // stolen from
  // https://en.wikipedia.org/wiki/Invertible_matrix#Inversion_of_3_%C3%97_3_matrices

  double det = determinant_matrix_d(*in);

  if (det == 0) {
    return 1;
  }

  double a = (*in)[0][0];
  double b = (*in)[1][0];
  double c = (*in)[2][0];
  double d = (*in)[0][1];
  double e = (*in)[1][1];
  double f = (*in)[2][1];
  double g = (*in)[0][2];
  double h = (*in)[1][2];
  double i = (*in)[2][2];

  double A = e * i - f * h;
  double B = -1 * (d * i - f * g);
  double C = (d * h - e * g);
  double D = -1 * (b * i - h * c);
  double E = (a * i - c * g);
  double F = -1 * (a * h - g * b);
  double G = (b * f - e * c);
  double H = -1 * (a * f - c * d);
  double I = (a * e - b * d);

  (*out)[0][0] = A / det;
  (*out)[1][0] = D / det;
  (*out)[2][0] = G / det;
  (*out)[0][1] = B / det;
  (*out)[1][1] = E / det;
  (*out)[2][1] = H / det;
  (*out)[0][2] = C / det;
  (*out)[1][2] = F / det;
  (*out)[2][2] = I / det;

  return 0;
}

void print_vector(const Vector3_double *A) {
  printf("[%f\n, %f\n, %f\n]", (*A)[0], (*A)[1], (*A)[2]);
}

void print_matrix(const Matrix3_double *A) {
  printf("[%f, %f, %f]\n[%f, %f, %f]\n[%f, %f, %f]\n", (*A)[0][0], (*A)[0][1],
         (*A)[0][2], (*A)[1][0], (*A)[1][1], (*A)[1][2], (*A)[2][0], (*A)[2][1],
         (*A)[2][2]);
}
