#include "custom_math.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_pixel(const Pixel *pixel) {
  printf("(red: %d, green: %d, blue: %d, alpha: %d)", pixel->red, pixel->green,
         pixel->blue, pixel->alpha);
}

void pixel_multi(Pixel *pixel, const uint8_t k) {
  pixel->red = clamp_multi(pixel->red, k);
  pixel->green = clamp_multi(pixel->green, k);
  pixel->blue = clamp_multi(pixel->blue, k);
}

void pixel_div(Pixel *pixel, const uint8_t k) {
  pixel->red = clamp_div(pixel->red, k);
  pixel->green = clamp_div(pixel->green, k);
  pixel->blue = clamp_div(pixel->blue, k);
}

void pixel_add(Pixel *pixel, const Pixel *other) {
  pixel->red = clamp_add(pixel->red, other->red);
  pixel->green = clamp_add(pixel->green, other->green);
  pixel->blue = clamp_add(pixel->blue, other->blue);
}

void pixel_sub(Pixel *pixel, const Pixel *other) {
  pixel->red = clamp_sub(pixel->red, other->red);
  pixel->green = clamp_sub(pixel->green, other->green);
  pixel->blue = clamp_sub(pixel->blue, other->blue);
}

void pixel_transform(Pixel *pixel, const Matrix3 *A) {
  Vector3 v = {pixel->red, pixel->green, pixel->blue};
  Vector3 new = {0, 0, 0};
  matrix_multiply(A, &v, &new);
  pixel->red = new[0];
  pixel->green = new[1];
  pixel->blue = new[2];
}