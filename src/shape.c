#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "custom_math.h"
#include "file_pam.h"
#include "shape.h"

// private
static void swap(uint16_t *a, uint16_t *b) {
  uint16_t temp = *a;
  *a = *b;
  *b = temp;
}

void print_line(const Line *line) {
  printf("x0: %d, y0: %d, x1: %d, y1: %d\n", line->x0, line->y0, line->x1,
         line->y1);
}

void print_circle(const Circle *circle) {
  printf("x: %d, y: %d, r: %f\n", circle->x, circle->y, circle->radius);
}

void rasterize_line_simple(Image *image, const Line *line, const Pixel *pixel) {
  double dy = line->y1 - line->y0;
  double dx = line->x1 - line->x0;
  double slope = dy / dx;

  if (slope <= 1 && slope >= -1) {
    uint16_t y = line->y0;
    uint16_t x_start = line->x0;
    uint16_t x_end = line->x1;

    if (x_start > x_end) { // if x_start, x_end are reversed, swap them
      swap(&x_start, &x_end);
      y = line->y1;
    }

    if (dx == 0) {
      slope = 0; // hacks to handle if its a straight line up/down
    }

    for (int i = x_start; i >= 0 && i <= x_end && i < image->width; i++) {
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

    for (int i = y_start; i >= 0 && i <= y_end && i < image->height; i++) {

      image->pixels[x + i * image->width] = *pixel;
      x = x + round(slope);
      if (x > image->height)
        break;
    }
  }
}

void rasterize_line_bresenham(Image *image, const Line *line,
                              const Pixel *pixel) {
  uint16_t x0 = line->x0;
  uint16_t x1 = line->x1;
  uint16_t y0 = line->y0;
  uint16_t y1 = line->y1;

  int dx = abs(x1 - x0);
  int sign_x = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sign_y = y0 < y1 ? 1 : -1;
  int delta_error = dx + dy;
  int running_error = 0;

  while (true) {
    write_pixel_to_image(image, x0, y0, pixel);

    running_error = 2 * delta_error;
    if (running_error >= dy) {
      if (x0 == x1) {
        break;
      }
      delta_error += dy;
      x0 += sign_x;
    }
    if (running_error <= dx) {
      if (y0 == y1) {
        break;
      }
      delta_error += dx;
      y0 += sign_y;
    }
  }
}

void rasterize_circle_simple(Image *image, const Circle *circle,
                             const Pixel *pixel,
                             const double step_size_radians) {
  if (step_size_radians <= 0) {
    return;
  }

  for (double i = 0; i < 2 * M_PI; i += step_size_radians) {
    uint16_t x_pos = round(circle->x + cos(i) * circle->radius);
    uint16_t y_pos = round(circle->y + sin(i) * circle->radius);
    write_pixel_to_image(image, x_pos, y_pos, pixel);
  }
}

void rasterize_circle_midpoint(Image *image, const Circle *circle,
                               const Pixel *pixel) {
  int16_t x = round(circle->radius);
  int16_t y = 0;
  int16_t err = 0;

  while (x >= y) {
    write_pixel_to_image(image, circle->x + x, circle->y + y, pixel);
    write_pixel_to_image(image, circle->x + y, circle->y + x, pixel);
    write_pixel_to_image(image, circle->x - y, circle->y + x, pixel);
    write_pixel_to_image(image, circle->x - x, circle->y + y, pixel);
    write_pixel_to_image(image, circle->x - x, circle->y - y, pixel);
    write_pixel_to_image(image, circle->x - y, circle->y - x, pixel);
    write_pixel_to_image(image, circle->x + y, circle->y - x, pixel);
    write_pixel_to_image(image, circle->x + x, circle->y - y, pixel);

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    } else {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}

void rasterize_circle_bresenham(Image *image, const Circle *circle,
                                const Pixel *pixel) {
  int16_t xm = circle->x;
  int16_t ym = circle->y;
  int16_t r = circle->radius;

  int x = -r, y = 0, err = 2 - 2 * r;
  do {
    write_pixel_to_image(image, xm - x, ym + y, pixel);
    write_pixel_to_image(image, xm - y, ym - x, pixel);
    write_pixel_to_image(image, xm + x, ym - y, pixel);
    write_pixel_to_image(image, xm + y, ym + x, pixel);

    r = err;
    if (r <= y)
      err += ++y * 2 + 1;
    if (r > x || err > y)
      err += ++x * 2 + 1;
  } while (x < 0);
}
