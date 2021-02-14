#pragma once

#include <stdint.h>

#include "linear_algebra.h"
#include "pixel.h"

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
Image *copy_from_image(const Image *src, const uint16_t x_start,
                       const uint16_t y_start, const uint16_t x_stop,
                       const uint16_t y_stop);

/*
 * Transforms an image (in place) by mutating all pixels by function that takes
 * in a constant
 */
void transform_pixels_constant(Image *image,
                               const void (*op)(Pixel *, const uint8_t),
                               const uint8_t k);

/*
 * Transforms an image (in place) by mutation all pixels by a function that
 * takes in another pixel
 */
void transform_pixels_other(Image *image,
                            const void (*op)(Pixel *, const Pixel *),
                            const Pixel *other);

/*
 * Transforms an image (in place) by mutating all pixels in the image by a a
 * matrix
 */
void transform_pixels_matrix(Image *image, const Matrix3_uint8 *A);

/*
 * Transforms an image with an affine transform, returning the transformed image
 * as a copy.
 *
 * (I would have liked to do this in-place, but its kind of tricky, so I return
 * a new image instead).
 */
Image *affine_transform(const Image *image, const Matrix3_d *A);

/*
 * Does a kernel transform to an image
 */
Image *kernel_transform(const Image *image, const Matrix3_d *A);