#pragma once

#include <stdint.h>

#include "linear_algebra.h"

/*
 * Struct to represent a pixel.
 */
typedef struct pixel {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
} Pixel;

void print_pixel(const Pixel *pixel);

/*
 * Some basic color constants.
 */
static const Pixel PIXEL_RED = {255, 0, 0, 255};
static const Pixel PIXEL_GREEN = {0, 255, 0, 255};
static const Pixel PIXEL_BLUE = {0, 0, 255, 255};
static const Pixel PIXEL_BLACK = {0, 0, 0, 255};
static const Pixel PIXEL_WHITE = {255, 255, 255, 255};
static const Pixel PIXEL_CLEAR = {0, 0, 0, 0};

/*
 * Mutates the pixel, multiplying each color by k. Doesn't modify alpha
 */
void pixel_multi(Pixel *pixel, const uint8_t k);

/*
 * Mutates the pixel, dividing each color by k. Doesn't modify alpha
 */
void pixel_div(Pixel *pixel, const uint8_t k);

/*
 * Mutates the pixel, adding one pixel to the other. Doesn't modify alpha
 */
void pixel_add(Pixel *pixel, const Pixel *other);

/*
 * Subtracts one pixel from the other. Doesn't modify alpha
 */
void pixel_sub(Pixel *pixel, const Pixel *other);

/*
 * Transforms a pixel pixel with the transformation matrix (in place)
 */
void pixel_transform(Pixel *pixel, const Matrix3_uint8 *A);

/*
 * Creates a pixel object from a hsv representation.
 * hue must be in [0, 360]. Saturation and Value must be in [0, 1]. Returns NULL
 * for invalid input
 */
Pixel *from_hsv(double hue, double saturation, double value, uint8_t alpha);