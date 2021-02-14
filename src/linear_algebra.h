#pragma once

#include <stdint.h>

/*
 * Vectors and matrices for uint8_t data (pixel data)
 */
typedef uint8_t Vector3_uint8[3];
typedef uint8_t Matrix3_uint8[3][3];

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
void matrix_vector_multiply_uint8(const Matrix3_uint8 *A,
                                  const Vector3_uint8 *v, Vector3_uint8 *out);

/*
 * Mutliplies matrix A by vector v, modifying out with the result.
 *
 * Does this for types backed by doubles. C technically has generics now, but I
 * haven't tried them
 */
void matrix_vector_multiply_d(const Matrix3_d *A, const Vector3_d *v,
                              Vector3_d *out);

/*
 * Mutliplies two matrices together, creating a new matrix and returning it in
 * the out position.
 */
void matrix_multiply_d(const Matrix3_d *A, const Matrix3_d *B, Matrix3_d *out);

/*
 * Prints a matrix to the console
 */
void print_matrix(const Matrix3_d *A);
