#pragma once

#include <stddef.h>
#include <stdint.h>

// 'Generic' macros for creating datatypes for matrixes and vectors of a numeric
// type
#define VECTOR3(type) type Vector3_##type[3]
#define MATRIX3(type) type Matrix3_##type[3][3]

#define UNIT_VECTOR(type) Vector3_##type *unit_vector_##type()
#define IDENTITY_MATRIX(type) Matrix3_##type *identity_matrix_##type()

#define SET_VECTOR_VALUE(type)                                                 \
  void set_vector_value_##type(Vector3_##type *v, const size_t index,          \
                               const type value)
#define SET_MATRIX_VALUE(type)                                                 \
  void set_matrix_value_##type(Matrix3_##type *m, const size_t x,              \
                               const size_t y, const type value)

/*
 * Vectors and matrices for uint8_t data (pixel data)
 */
typedef VECTOR3(uint8_t);
typedef MATRIX3(uint8_t);

UNIT_VECTOR(uint8_t);
IDENTITY_MATRIX(uint8_t);
SET_VECTOR_VALUE(uint8_t);
SET_MATRIX_VALUE(uint8_t);

/*
 * Vectors and matrics for double data (positional data, rotational data)
 */
typedef VECTOR3(double);
typedef MATRIX3(double);

UNIT_VECTOR(double);
IDENTITY_MATRIX(double);
SET_VECTOR_VALUE(double);
SET_MATRIX_VALUE(double);

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
void matrix_vector_multiply_uint8(const Matrix3_uint8_t *A,
                                  const Vector3_uint8_t *v,
                                  Vector3_uint8_t *out);

/*
 * Mutliplies matrix A by vector v, modifying out with the result.
 *
 * Does this for types backed by doubles. C technically has generics now, but I
 * haven't tried them
 */
void matrix_vector_multiply_d(const Matrix3_double *A, const Vector3_double *v,
                              Vector3_double *out);

/*
 * Mutliplies two matrices together, creating a new matrix and returning it in
 * the out position.
 */
void matrix_multiply_d(const Matrix3_double *A, const Matrix3_double *B,
                       Matrix3_double *out);

/*
 * Prints a vector to the console
 */
void print_vector(const Vector3_double *A);

/*
 * Prints a matrix to the console
 */
void print_matrix(const Matrix3_double *A);

#undef VECTOR3
#undef MATRIX3
#undef UNIT_VECTOR
#undef IDENTITY_MATRIX
#undef SET_VECTOR_VALUE
#undef SET_MATRIX_VALUE