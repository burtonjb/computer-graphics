#pragma once

#include <stdint.h>

/*
 * Vectors and matrices for uint8_t data (pixel data)
 */
typedef uint8_t Vector3[3];
typedef uint8_t Matrix3[3][3];

/*
 * Vectors and matrics for double data (positional data, rotational data)
 */
typedef double Vector3_d[3];
typedef double Matrix3_d[3][3];

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

void matrix_multiply_d(const Matrix3_d *A, const Vector3_d *v, Vector3_d *out);

void to_int_vector(const Vector3_d *in, Vector3 *out);