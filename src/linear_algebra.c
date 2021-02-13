#include "linear_algebra.h"
#include "custom_math.h"

void matrix_multiply(const Matrix3 *A, const Vector3 *v, Vector3 *out) {
  for (int i = 0; i < 3; i++) {
    // does out[i] = A[i][j]v[j] for all j, but clamps the values as this is
    // going to be used for pixel operations
    (*out)[i] = clamp_add(clamp_add(clamp_multi((*A)[i][0], (*v)[0]),
                                    clamp_multi((*A)[i][1], (*v)[1])),
                          clamp_multi((*A)[i][2], (*v)[2]));
  }
}