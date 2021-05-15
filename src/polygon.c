#include "polygon.h"

#include <stdlib.h>

struct polygon {
  uint16_t number_of_lines;
  Line lines[];
};

void draw_polygon(Image *image, const Polygon *polygon, const Pixel *pixel) {
  for (int i = 0; i < polygon->number_of_lines; i++) {
    rasterize_line_bresenham(image, &(polygon->lines[i]), pixel);
  }
}

Polygon *create_triangle(const Point *p1, const Point *p2, const Point *p3) {
  Polygon *out = malloc(sizeof(uint16_t) + 3 * sizeof(Line));
  out->number_of_lines = 3;
  out->lines[0] = (Line){p1->x, p1->y, p2->x, p2->y};
  out->lines[1] = (Line){p2->x, p2->y, p3->x, p3->y};
  out->lines[2] = (Line){p3->x, p3->y, p1->x, p1->y};
  return out;
}

Polygon *create_rectangle(const Point *bottom_left, const Point *top_right) {
  Polygon *out = malloc(sizeof(uint16_t) + 4 * sizeof(Line));
  out->number_of_lines = 4;
  out->lines[0] =
      (Line){bottom_left->x, bottom_left->y, top_right->x, bottom_left->y};
  out->lines[1] =
      (Line){top_right->x, bottom_left->y, top_right->x, top_right->y};
  out->lines[2] =
      (Line){top_right->x, top_right->y, bottom_left->x, top_right->y};
  out->lines[3] =
      (Line){bottom_left->x, top_right->y, bottom_left->x, bottom_left->y};
  return out;
}