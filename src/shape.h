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
 * each iteration
 */
void bresenhams_algorithm(Image *image, const Line *line, const Pixel *pixel);

void print_line(const Line *line);