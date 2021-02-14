#include "image.h"
#include "custom_math.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image *make_filled_image(const uint16_t width, const uint16_t height,
                         const Pixel *fill_color) {
  Image *out = malloc(2 * sizeof(uint16_t) + (width * height * sizeof(Pixel)));

  out->width = width;
  out->height = height;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      memcpy(&(out->pixels[i + j * width]), fill_color, sizeof(Pixel));
    }
  }
  return out;
}

Image *copy_image(const Image *src) {
  // I think this implementation is kind of bad. The memcpy should be in an
  // unrolled loop, instead of in a double loop, but I can always fix this later

  // TODO: Is this still needed? I should be able to use copy_from_image(img, 0,
  // 0, img->width, img->height) instead of this function
  Image *out =
      malloc(2 * sizeof(uint16_t) + (src->width * src->height * sizeof(Pixel)));

  out->width = src->width;
  out->height = src->height;
  for (int i = 0; i < src->width; i++) {
    for (int j = 0; j < src->height; j++) {
      memcpy(&(out->pixels[i + j * out->width]),
             &(src->pixels[i + j * src->width]), sizeof(Pixel));
    }
  }
  return out;
}

void paste_to_image(const Image *from, Image *to, const uint16_t x_offset,
                    const uint16_t y_offset) {

  // exit early if inputs are invalid
  if (x_offset > to->width || y_offset > to->height) {
    return;
  }

  const uint16_t max_x = min(from->width, to->width - x_offset);
  const uint16_t max_y = min(from->height, to->height - y_offset);

  for (int i = 0; i < max_x; i++) {
    for (int j = 0; j < max_y; j++) {

      const uint16_t x_from = i;
      const uint16_t x_to = i + x_offset;
      const uint16_t y_from = j;
      const uint16_t y_to = j + y_offset;

      memcpy(&(to->pixels[x_to + (y_to * to->width)]),
             &(from->pixels[x_from + y_from * from->width]), sizeof(Pixel));
    }
  }
}

Image *copy_from_image(Image *src, const uint16_t x_start,
                       const uint16_t y_start, const uint16_t x_stop,
                       const uint16_t y_stop) {

  // Check inputs, return null on invalid input
  if (x_stop < x_start || y_stop < y_start) {
    return NULL;
  }

  const uint16_t max_x = min(src->width, x_stop);
  const uint16_t max_y = min(src->height, y_stop);

  const uint16_t new_width = (x_stop - x_start);
  const uint16_t new_height = (y_stop - y_start);

  Image *out =
      malloc(2 * sizeof(uint16_t) + (new_width * new_height * sizeof(Pixel)));

  out->width = new_width;
  out->height = new_height;
  for (int i = 0; i < max_x - x_start; i++) {
    for (int j = 0; j < max_y - y_start; j++) {

      const uint16_t x_from = i + x_start;
      const uint16_t x_to = i;
      const uint16_t y_from = j + y_start;
      const uint16_t y_to = j;

      memcpy(&(out->pixels[x_to + (y_to * out->width)]),
             &(src->pixels[x_from + (y_from * src->width)]), sizeof(Pixel));
    }
  }
  return out;
}

void transform_pixels_constant(Image *image,
                               const void (*op)(Pixel *, const uint8_t),
                               const uint8_t k) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      op(pixel, k);
    }
  }
}

void transform_pixels_other(Image *image,
                            const void (*op)(Pixel *, const Pixel *pixel),
                            const Pixel *other) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      op(pixel, other);
    }
  }
}

void transform_pixels_matrix(Image *image, const Matrix3 *A) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      pixel_transform(pixel, A);
    }
  }
}

Image *affine_transform(const Image *image, const Matrix3_d *A) {

  Image *out = make_filled_image(
      image->width, image->height,
      &((Pixel){0, 0, 0,
                0})); // make an output image of all 0s (including alpha)

  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {

      Vector3_d untransformed_position_d = {
          i, j, 1}; // affine transforms require the position to be (x, y, 1)

      Vector3_d transformed_position_d = {0, 0, 1};

      matrix_multiply_d(A, &untransformed_position_d, &transformed_position_d);

#define d_to_uint16_t(arg) (uint16_t)(round(arg))
      // FIXME: Vector3 is uint8_t, but I've set it up so that images use
      // uint16_t for indexing
      uint16_t transformed_position[2] = {
          d_to_uint16_t(transformed_position_d[0]),
          d_to_uint16_t(transformed_position_d[1])};
      uint16_t untransformed_position[2] = {
          d_to_uint16_t(untransformed_position_d[0]),
          d_to_uint16_t(untransformed_position_d[1])};
#undef d_to_uint16_t

      // clip transformed pixels that would not end up in the picture
      if (transformed_position[0] >= out->width ||
          transformed_position[1] >= out->height ||
          transformed_position[0] < 0 || transformed_position[1] < 0) {
        continue;
      }

      // copy from the untransformed location to the transformed pixel location
      memcpy(&(out->pixels[transformed_position[0] +
                           (transformed_position[1] * out->width)]),
             &(image->pixels[untransformed_position[0] +
                             (untransformed_position[1] * image->width)]),
             sizeof(Pixel));
    }
  }
  return out;
}