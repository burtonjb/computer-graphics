#pragma once

#include "shape.h"

/*
 * Opaque struct for a polygon
 */
struct polygon;

typedef struct polygon Polygon;

/*
 * Draws a generic polygon struct. This method assumes the polygon is a
 * collection of line segments and draws the next line segment starting from the
 * end of the previous line segment
 */
void draw_polygon(Image *image, const Polygon *polygon, const Pixel *pixel);

Polygon *create_triangle(const Point *p1, const Point *p2, const Point *p3);

Polygon *create_rectangle(const Point *bottom_left, const Point *top_right);