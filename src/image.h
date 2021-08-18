#pragma once

#include <stdbool.h>
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
 * Checks if the value of two images is equal.
 *
 * Returns 1 if the images are equal, 0 if they aren't
 */
int are_images_equal(const Image *i1, const Image *i2);

/*
 * writes a pixel to the image at position (x, y)
 */
void write_pixel_to_image(Image *image, const uint16_t x, const uint16_t y,
                          const Pixel *pixel);

/*
 * Returns a reference to a pixel at position (x, y) in an image
 */
Pixel *get_pixel_from_image(const Image *image, const uint16_t x,
                            const uint16_t y);

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
void transform_pixels_constant(Image *image, int_op_on_pixel op,
                               const uint8_t k);

/*
 * Transforms an image (in place) by mutation all pixels by a function that
 * takes in another pixel
 */
void transform_pixels_other(Image *image, pixel_op_on_pixel op,
                            const Pixel *other);

/*
 * Transforms an image (in place) by mutating all pixels in the image by a a
 * matrix. Pass in a divisor, because I used uint8_t as the datatype for the
 * matrix, so it doesn't support fractional values.
 */
void transform_pixels_matrix(Image *image, const Matrix3_uint8_t *A,
                             const uint8_t divisor);

/*
 * Transforms an image with an affine transform, returning the transformed image
 * as a copy.
 *
 * (I would have liked to do this in-place, but its kind of tricky, so I return
 * a new image instead).
 */
Image *affine_transform(const Image *image, const Matrix3_double *A);

typedef enum InterpolationMode {
  NEAREST_NEIGHBOR,
  LINEAR,
  BILINEAR,
  BICUBIC
} INTERPOLATION_MODE;

/*
 * Transforms an image with an affine transform, returning the transformed image
 * as a copy.
 *
 * The difference between this and the regular affine_transform function is that
 * this function will use an interpolation mode, which will fix issues with
 * scaling (see the README for the problem with regular affine transformations
 * and scaling)
 */
Image *inverting_affine_transform(const Image *image, const Matrix3_double *A,
                                  const INTERPOLATION_MODE mode);

/*
 * Does a kernel transform to an image
 *
 * It returns a copy of the image after the transform
 */
Image *kernel_transform(const Image *image, const Matrix3_double *A);

/*
 * Alpha blends two images together, returning the result.
 *
 * It will return null if the input dimensions of the images don't match.
 * You'll probably need to do pre-processing with paste_to_image to get
 * everything to line up properly.
 */
Image *alpha_blend(const Image *dest, const Image *src);

/*
 * Printfs an image. Only use for small images as this is going to output A LOT
 * of text
 */
void print_image(const Image *image);
