#include "linear_algebra.h"
#include "custom_math.h"

#include <math.h>

void matrix_multiply(const Matrix3 *A, const Vector3 *v, Vector3 *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j, but clamps the values as this is
    // going to be used for pixel operations
    (*out)[i] = clamp_add(clamp_add(clamp_multi((*A)[i][0], (*v)[0]),
                                    clamp_multi((*A)[i][1], (*v)[1])),
                          clamp_multi((*A)[i][2], (*v)[2]));
  }
}

void matrix_multiply_d(const Matrix3_d *A, const Vector3_d *v, Vector3_d *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j
    (*out)[i] = ((*A)[i][0] * (*v)[0]) + ((*A)[i][1] * (*v)[1]) +
                ((*A)[i][2] * (*v)[2]);
  }
}

void to_int_vector(const Vector3_d *in, Vector3 *out) {
  (*out)[0] = (uint8_t)round((*in)[0]);
  (*out)[1] = (uint8_t)round((*in)[1]);
  (*out)[2] = (uint8_t)round((*in)[2]);
}