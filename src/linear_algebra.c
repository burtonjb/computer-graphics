#include "linear_algebra.h"
#include "custom_math.h"

#include <math.h>
#include <stdio.h>

void matrix_vector_multiply_uint8(const Matrix3_uint8 *A,
                                  const Vector3_uint8 *v, Vector3_uint8 *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j, but clamps the values as this is
    // going to be used for pixel operations
    (*out)[i] = clamp_add(clamp_add(clamp_multi((*A)[i][0], (*v)[0]),
                                    clamp_multi((*A)[i][1], (*v)[1])),
                          clamp_multi((*A)[i][2], (*v)[2]));
  }
}

void matrix_vector_multiply_d(const Matrix3_d *A, const Vector3_d *v,
                              Vector3_d *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j
    (*out)[i] = ((*A)[i][0] * (*v)[0]) + ((*A)[i][1] * (*v)[1]) +
                ((*A)[i][2] * (*v)[2]);
  }
}

void matrix_multiply_d(const Matrix3_d *A, const Matrix3_d *B, Matrix3_d *out) {
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

void print_matrix(const Matrix3_d *A) {
  printf("[%f, %f, %f]\n[%f, %f, %f]\n[%f, %f, %f]\n", (*A)[0][0], (*A)[0][1],
         (*A)[0][2], (*A)[1][0], (*A)[1][1], (*A)[1][2], (*A)[2][0], (*A)[2][1],
         (*A)[2][2]);
}