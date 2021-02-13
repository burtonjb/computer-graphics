#pragma once

#include <stdint.h>

typedef uint8_t Vector3[3];
typedef uint8_t Matrix3[3][3];

/*
 * Multiplies the matrix A by the vector v (A*v). modifies the vector
 * out with the result.
 *
 * Its done this way (instead of just returning the object) because you
 * can pass a stack allocated vector in as the out parameter, so you don't need
 * to worry about heap allocation. You can't return a stack allocated array in C
 * (which makes sense) and implemeting it this way allows you to use both heap
 * and stack allocation.
 */
void matrix_multiply(const Matrix3 *A, const Vector3 *v, Vector3 *out);