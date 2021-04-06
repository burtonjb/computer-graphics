#include "shape.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// private
void swap(uint16_t *a, uint16_t *b) {
  uint16_t temp = *a;
  *a = *b;
  *b = temp;
}

void print_line(const Line *line) {
  printf("x0: %d, y0: %d, x1: %d, y1: %d\n", line->x0, line->y0, line->x1,
         line->y1);
}

void rasterize_line_simple(Image *image, const Line *line, const Pixel *pixel) {
  double dy = line->y1 - line->y0;
  double dx = line->x1 - line->x0;
  double slope = dy / dx;

  if (slope <= 1) {
    uint16_t y = line->y0;
    uint16_t x_start = line->x0;
    uint16_t x_end = line->x1;

    if (x_start > x_end) { // if x_start, x_end are reversed, swap them
      swap(&x_start, &x_end);
      y = line->y1;
    }

    for (int i = x_start; i >= 0 && i < x_end && i < image->width; i++) {
      image->pixels[i + y * image->width] = *pixel;
      y = y + round(slope);
      if (y > image->height)
        break;
    }
  } else { // slope > 1

    uint16_t x = line->x0;
    uint16_t y_start = line->y0;
    uint16_t y_end = line->y1;

    if (y_start > y_end) {
      swap(&y_start, &y_end);
      x = line->x1;
    }

    if (dx == 0) {
      slope = 0; // hacks to handle if its a straight line up/down
    }

    for (int i = y_start; i >= 0 && i < y_end && i < image->height; i++) {

      image->pixels[x + i * image->width] = *pixel;
      x = x + round(slope);
      if (x > image->height)
        break;
    }
  }
}

void bresenhams_algorithm(Image *image, const Line *line, const Pixel *pixel) {
  int16_t dx = line->x1 - line->x0;
  int16_t dy = line->y1 - line->y0;

  int16_t d = dy * 2 - dx;

  int16_t increment_equals = dy * 2;
  int16_t increment_not_equals = (dy - dx) * 2;

  uint16_t x = line->x0;
  uint16_t y = line->y0;

  image->pixels[x + y * image->width] = *pixel;

  while (x < line->x1) {
    if (d <= 0) {
      d += increment_equals;
      x++;
    } else {
      d += increment_not_equals;
      x++;
      y++;
    }
    image->pixels[x + y * image->width] = *pixel;
  }
}