#pragma once

#include <stdint.h>

#include "image.h"
#include "pixel.h"

typedef struct line {
  uint16_t x0;
  uint16_t y0;
  uint16_t x1;
  uint16_t y1;
} Line;

typedef struct circle {
  uint16_t x; // center of the circle - x position
  uint16_t y; // center of the circle - y position
  double radius;
} Circle;

/*
 * Simple algorithm to draw the line onto the image.
 *
 * "Walks" down the line, drawing a pixel on the image for each point on the
 * line
 *
 * Kinda slow, kinda simple.
 */
void rasterize_line_simple(Image *image, const Line *line, const Pixel *pixel);

/*
 * Bresenham's Algorithm is an alternative way to rasterize a line.
 *
 * It only uses integer addition, subtraction and bit shifting instead of the
 * floating point operations in the 'simple' algorithm.
 *
 * The basic idea is that when drawing a line, the coordinate which is changing
 * fractionally either stays the same or changes y +/- 1 pixel coordinate on
 * each iteration.
 */
void rasterize_line_bresenham(Image *image, const Line *line,
                              const Pixel *pixel);

/*
 * Method to draw a circle.
 *
 * It uses (a lot of) floating point math to draw the circle onto the image
 * There's some trivial ways to improve the performance, none which I'll do.
 *
 * There's also some algorithmic changes that can be done to improve the
 * performace - using the midpoint algorithm or bresenham's algorithm is good
 * idea.
 *
 */
void rasterize_circle_simple(Image *image, const Circle *circle,
                             const Pixel *pixel,
                             const double step_size_radians);

/*
 * Uses the midpoint algorithm to draw a circle onto the image
 */
void rasterize_circle_midpoint(Image *image, const Circle *circle,
                               const Pixel *pixel);

/*
 * Uses the bresenham's modifications to the midpoint algorithm to draw a circle
 * onto the image
 */
void rasterize_circle_bresenham(Image *image, const Circle *circle,
                                const Pixel *pixel);

void print_line(const Line *line);
void print_circle(const Circle *circle);