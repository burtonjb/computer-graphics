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

void print_pixel(const Pixel *pixel);

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
 * Bitwise paste pixels from the "from" image to the "to" image, starting from
 * the x and y offsets.
 *
 * If copying from the from image would go out of bounds of the "to" image,
 * those pixels are not copied.
 */
void paste_to_image(const Image *from, Image *to, const uint16_t x_offset,
                    const uint16_t y_offset);

/*
 * Copies a section of an image. Will return null if x_stop < x_start ||
 *  y_stop < y_start
 *
 * Returns a copy of an image, starting from (x_start, y_start) and
 * ending at (x_stop, y_stop).
 *
 * This can be used to truncate an image - copy the section you want to keep and
 * then free the previous image
 */
Image *copy_from_image(Image *src, const uint16_t x_start,
                       const uint16_t y_start, const uint16_t x_stop,
                       const uint16_t y_stop);