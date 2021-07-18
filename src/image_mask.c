#include <stdio.h>
#include <stdlib.h>

#include "image_mask.h"

ImageMask *create_mask(const Image *image, const pixel_filter filter,
                       void *filter_args, const Point initial) {
  ImageMask *image_mask = malloc(sizeof(uint16_t) * 2 +
                                 sizeof(bool) * image->width * image->height);

  image_mask->width = image->width;
  image_mask->height = image->height;
  for (int i = 0; i < image_mask->width; i++) {
    for (int j = 0; j < image_mask->height; j++) {
      image_mask->is_pixel_masked[i + j * image_mask->width] = false;
    }
  }

  int stack_pointer = 0;
  Point stack[MAX_STACK_SIZE];
  stack[stack_pointer++] = initial;
  while (stack_pointer > 0 && stack_pointer < MAX_STACK_SIZE) {
    // pop from stack. If the "filter" condition is false, skip over it.
    // Otherwise, set the mask flag to true and continue processing
    Point current = stack[--stack_pointer];
    if (current.x > image->width || current.y > image->height) {
      continue;
    }
    Pixel *current_pixel = get_pixel_from_image(image, current.x, current.y);

    if (!(filter(current_pixel, filter_args, current.x, current.y))) {
      continue;
    } else {
      image_mask->is_pixel_masked[current.x + image_mask->width * current.y] =
          true;
    }

    // left pixel
    Point next_pixel = (Point){current.x - 1, current.y};
    if (next_pixel.x > 0 && next_pixel.x < image->width && next_pixel.y > 0 &&
        next_pixel.y < image->height) {
      if (!(image_mask->is_pixel_masked[next_pixel.x +
                                        image_mask->width * next_pixel.y])) {
        stack[stack_pointer++] = next_pixel;
      }
    }

    // right pixel
    next_pixel = (Point){current.x + 1, current.y};
    if (next_pixel.x > 0 && next_pixel.x < image->width && next_pixel.y > 0 &&
        next_pixel.y < image->height) {
      if (!(image_mask->is_pixel_masked[next_pixel.x +
                                        image_mask->width * next_pixel.y])) {
        stack[stack_pointer++] = next_pixel;
      }
    }

    // above pixel
    next_pixel = (Point){current.x, current.y - 1};
    if (next_pixel.x > 0 && next_pixel.x < image->width && next_pixel.y > 0 &&
        next_pixel.y < image->height) {
      if (!(image_mask->is_pixel_masked[next_pixel.x +
                                        image_mask->width * next_pixel.y])) {
        stack[stack_pointer++] = next_pixel;
      }
    }

    // below pixel
    next_pixel = (Point){current.x, current.y + 1};
    if (next_pixel.x > 0 && next_pixel.x < image->width && next_pixel.y > 0 &&
        next_pixel.y < image->height) {
      if (!(image_mask->is_pixel_masked[next_pixel.x +
                                        image_mask->width * next_pixel.y])) {
        stack[stack_pointer++] = next_pixel;
      }
    }
  }
  if (stack_pointer >= MAX_STACK_SIZE) {
    printf("Error: 'stack overflow' in create_mask function, returning null");
    return NULL;
  }
  return image_mask;
}

void apply_to_mask(Image *image, const ImageMask *mask,
                   const pixel_op_on_pixel op, const Pixel *other) {
  for (uint16_t i = 0; i < mask->width && i < image->width; i++) {
    for (uint16_t j = 0; j < mask->height && i < image->height; j++) {
      if (mask->is_pixel_masked[i + mask->width * j]) {
        op(get_pixel_from_image(image, i, j), other);
      }
    }
  }
}

void print_mask(const ImageMask *mask) {
  for (uint16_t i = 0; i < mask->width; i++) {
    for (uint16_t j = 0; j < mask->height; j++) {
      if (mask->is_pixel_masked[i + mask->width * j]) {
        printf("x");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

bool pixel_equals_filter(Pixel *pixel, void *other, uint16_t x,
                         uint16_t y) { // other is of type "pixel" but I need
  (void)x;
  (void)y; // remove unused param warning
  bool out = are_pixels_equal(pixel, (Pixel *)other);
  return out;
}

bool pixel_in_rect_filter(Pixel *pixel,
                          void *other, // other is a rectangle
                          uint16_t x, uint16_t y) {
  Rectangle *rect = (Rectangle *)other;
  return (x > rect->x_top_left && x < rect->x_top_left + rect->width &&
          y > rect->y_top_left && y < rect->y_top_left + rect->height);
}

bool pixel_in_circle_filter(Pixel *pixel, void *other, uint16_t x,
                            uint16_t y) { // other is a circle
  (void)pixel;
#define SQUARE(arg) (arg * arg)
  uint16_t x_dist = SQUARE((((Circle *)other)->x - x));
  uint16_t y_dist = SQUARE((((Circle *)other)->y - y));
  bool dist = SQUARE((((Circle *)other)->radius)) > SQUARE(x_dist + y_dist);
  return dist;
#undef SQUARE
}
