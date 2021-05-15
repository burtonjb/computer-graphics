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

void write_pixel_to_image(Image *image, const uint16_t x, const uint16_t y,
                          const Pixel *pixel) {
  if (x >= image->width || y >= image->height) {
    return; // no-op if the write is out of bounds. Ideally I would return an
            // error or something, but lazy
  }
  image->pixels[x + y * image->width] = (*pixel);
}

Pixel *get_pixel_from_image(const Image *image, const uint16_t x,
                            const uint16_t y) {
  if (x > image->width || y > image->height) {
    return NULL;
  }
  return &(image->pixels[x + y * image->width]);
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

int are_images_equal(const Image *i1, const Image *i2) {
  if (i1->width != i2->width) {
    return 0;
  }
  if (i1->height != i2->height) {
    return 0;
  }

  for (uint16_t i = 0; i < i1->width; i++) {
    for (uint16_t j = 0; j < i1->height; j++) {
      Pixel *p1 = get_pixel_from_image(i1, i, j);
      Pixel *p2 = get_pixel_from_image(i2, i, j);
      if (!are_pixels_equal(p1, p2)) {
        return FALSE;
      }
    }
  }
  return TRUE;
}

Image *copy_from_image(const Image *src, const uint16_t x_start,
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

void transform_pixels_constant(Image *image, int_op_on_pixel op,
                               const uint8_t k) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      op(pixel, k);
    }
  }
}

void transform_pixels_other(Image *image, pixel_op_on_pixel op,
                            const Pixel *other) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      op(pixel, other);
    }
  }
}

void transform_pixels_matrix(Image *image, const Matrix3_uint8_t *A,
                             const uint8_t divisor) {
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      Pixel *pixel = &(image->pixels[i + j * image->width]);
      pixel_transform(pixel, A, divisor);
    }
  }
}

Image *affine_transform(const Image *image, const Matrix3_double *A) {

  Image *out = make_filled_image(
      image->width, image->height,
      &((Pixel){0, 0, 0,
                0})); // make an output image of all 0s (including alpha)

  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {

      Vector3_double untransformed_position_d = {
          i, j, 1}; // affine transforms require the position to be (x, y, 1)

      Vector3_double transformed_position_d = {0, 0, 1};

      matrix_vector_multiply_d(A, &untransformed_position_d,
                               &transformed_position_d);

// Hacky macro to convert from double to position (uint16_t)
#define d_to_uint16_t(arg) (uint16_t)(round(arg))
      uint16_t transformed_position[2] = {
          d_to_uint16_t(transformed_position_d[0]),
          d_to_uint16_t(transformed_position_d[1])};
      uint16_t untransformed_position[2] = {
          d_to_uint16_t(untransformed_position_d[0]),
          d_to_uint16_t(untransformed_position_d[1])};
#undef d_to_uint16_t

      // clip transformed pixels that would not end up in the picture
      if (transformed_position[0] >= out->width ||
          transformed_position[1] >= out->height) {
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

Image *kernel_transform(const Image *image, const Matrix3_double *kernel) {
  Image *out = copy_image(image);
  for (int i = 1; i < image->width - 1; i++) {
    for (int j = 1; j < image->height - 1; j++) {
      double acc[3] = {0, 0, 0};

      // the kernel indexes are from 0 - 3, but the image would use
      // location -1, current, +1 so need to shift by a little
      for (int k = 0; k < 3; k++) {
        for (int n = 0; n < 3; n++) {
          Pixel p = image->pixels[i + k - 1 + (j + n - 1) * image->width];

          double new[3] = {(double)p.red * (*kernel)[k][n],
                           (double)p.green * (*kernel)[k][n],
                           (double)p.blue * (*kernel)[k][n]};

          acc[0] += new[0];
          acc[1] += new[1];
          acc[2] += new[2];
        }
      }

      Pixel new = {d_to_uint8_t(acc[0]), d_to_uint8_t(acc[1]),
                   d_to_uint8_t(acc[2]),
                   image->pixels[i + j * image->width].alpha};
      out->pixels[i + j * image->width] = new;
    }
  }
  return out;
}

Image *alpha_blend(const Image *dest, const Image *src) {

  // FIXME: allow blending the src image at a location - similar to
  // paste_to_image function
  if (dest->width != src->width || dest->height != src->height) {
    return NULL;
  }

  Image *out = copy_image(dest);

  // in alpha blending, values are [0, 1], but I've been using [0, 255] for
  // stuff, so need to convert
  const int SCALING_FACTOR = 255;

  /* formula is:
   * out_alpha = src_alpha + dest_alpha (1 - src_alpha)
   * out_RGB = (src_RGB * src_alpha + dest_RGB*dest_alpha * (1 - src_alpha)) /
   * out_alpha where alpha, RGB values are in [0, 1]
   */
  for (int i = 0; i < dest->width; i++) {
    for (int j = 0; j < dest->height; j++) {
      uint16_t loc = i + j * out->width;
      // just do all the math as doubles because debugging uint8 issues is
      // annoying

      double src_alpha = ((double)(src->pixels[loc].alpha)) / SCALING_FACTOR;
      double dest_alpha = ((double)(dest->pixels[loc].alpha)) / SCALING_FACTOR;
      double out_alpha = src_alpha + dest_alpha * (1 - src_alpha);

      double src_red = ((double)src->pixels[loc].red) / SCALING_FACTOR;
      double dest_red = ((double)dest->pixels[loc].red) / SCALING_FACTOR;
      double out_red =
          ((src_red * src_alpha + dest_red * dest_alpha * (1 - src_alpha))) /
          out_alpha;

      double src_green = ((double)src->pixels[loc].green) / SCALING_FACTOR;
      double dest_green = ((double)dest->pixels[loc].green) / SCALING_FACTOR;
      double out_green = ((src_green * src_alpha +
                           dest_green * dest_alpha * (1 - src_alpha))) /
                         out_alpha;

      double src_blue = ((double)src->pixels[loc].blue) / SCALING_FACTOR;
      double dest_blue = ((double)dest->pixels[loc].blue) / SCALING_FACTOR;
      double out_blue =
          ((src_blue * src_alpha + dest_blue * dest_alpha * (1 - src_alpha))) /
          out_alpha;

      out->pixels[loc] = (Pixel){d_to_uint8_t(out_red * SCALING_FACTOR),
                                 d_to_uint8_t(out_green * SCALING_FACTOR),
                                 d_to_uint8_t(out_blue * SCALING_FACTOR),
                                 d_to_uint8_t(out_alpha * SCALING_FACTOR)};
    }
  }

  return out;
}

void print_image(const Image *image) {
  printf("%d %d\n", image->width, image->height);
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      print_pixel(get_pixel_from_image(image, i, j));
    }
    printf("\n");
  }
}