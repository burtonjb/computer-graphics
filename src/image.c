#include "image.h"
#include "math.h"

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
