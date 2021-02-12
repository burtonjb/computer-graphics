#include "image.h"
#include "math.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_pixel(Pixel *pixel) {
  printf("(red: %d, green: %d, blue: %d, alpha: %d)\n", pixel->red,
         pixel->green, pixel->blue, pixel->alpha);
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
      memcpy(&(out->pixels[i + j * src->width]),
             &(src->pixels[i + j * src->width]), sizeof(Pixel));
    }
  }
  return out;
}

void fill_section(Image *image, const uint16_t start_width,
                  const uint16_t start_height, const Pixel *fill_color) {
  for (int i = start_width; i < image->width; i++) {
    for (int j = start_height; j < image->height; j++) {
      memcpy(&(image->pixels[i + j * image->width]), fill_color, sizeof(Pixel));
    }
  }
}