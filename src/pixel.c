#include "custom_math.h"
#include "image.h"

#include <math.h>
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

void pixel_transform(Pixel *pixel, const Matrix3_uint8_t *A) {
  Vector3_uint8_t v = {pixel->red, pixel->green, pixel->blue};
  Vector3_uint8_t new = {0, 0, 0};
  matrix_vector_multiply_uint8(A, &v, &new);
  pixel->red = new[0];
  pixel->green = new[1];
  pixel->blue = new[2];
}

// return pointer so I can return null in bad input cases.
Pixel *from_hsv(double hue, double saturation, double value, uint8_t alpha) {
  // validate inputs
  if (hue < 0 || hue > 360) {
    return NULL;
  }
  if (saturation < 0 || saturation > 1) {
    return NULL;
  }
  if (value < 0 || value > 1) {
    return NULL;
  }

  double chroma = value * saturation;
  int quantized_hue =
      round(hue / 60); // face of the color cube that the color is on
  double x = chroma * (1 - abs(quantized_hue % 2 - 1)); // secondary color

  double red_initial = 0;
  double green_initial = 0;
  double blue_initial = 0;

  double hue_face = hue / 60;
  if (hue_face >= 0 && hue_face <= 1) {
    red_initial = chroma;
    green_initial = x;
  } else if (hue_face > 1 && hue_face <= 2) {
    red_initial = x;
    green_initial = chroma;
  } else if (hue_face > 2 && hue_face <= 3) {
    green_initial = chroma;
    blue_initial = x;
  } else if (hue_face > 3 && hue_face <= 4) {
    green_initial = x;
    blue_initial = chroma;
  } else if (hue_face > 4 && hue_face <= 5) {
    red_initial = x;
    blue_initial = chroma;
  } else if (hue_face > 5 && hue_face <= 6) {
    red_initial = chroma;
    blue_initial = x;
  }

  double overlap = value - chroma;
  double red = red_initial + overlap;
  double green = green_initial + overlap;
  double blue = blue_initial + overlap;

  Pixel *out = malloc(sizeof(Pixel));

  out->red = d_to_uint8_t(red * 255);
  out->green = d_to_uint8_t(green * 255);
  out->blue = d_to_uint8_t(blue * 255);
  out->alpha = alpha;
  return out;
}