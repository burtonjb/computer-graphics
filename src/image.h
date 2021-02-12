#pragma once

#include <stdint.h>

/*
 * Struct to represent a pixel.
 */
typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
} Pixel;

void print_pixel(Pixel *pixel);

/*
 * Some basic color constants.
 */
static const Pixel PIXEL_RED = {255, 0, 0, 255};
static const Pixel PIXEL_GREEN = {0, 255, 0, 255};
static const Pixel PIXEL_BLUE = {0, 0, 255, 255};

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
 * Struct to represent an image. The image has a width, height and an array of
 * pixels.
 */
typedef struct {
  uint16_t width;
  uint16_t height;
  Pixel pixels[];
} Image;

/*
 * Creates an image filled with a single color
 */
Image *make_filled_image(const uint16_t width, const uint16_t height,
                         const Pixel *fill_color);

/*
 * Creates a copy of an image.
 */
Image *copy_image(const Image *src);

/*
 * Fills an image with a rectangle of a certain color.
 * It starts at the start_width/start_height and fills to the end of the
 * image (so filling the bottom right corner with the new color)
 */
void fill_section(Image *image, const uint16_t start_width,
                  const uint16_t start_height, const Pixel *fill_color);