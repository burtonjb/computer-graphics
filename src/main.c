#include <math.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"
#include "shape.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv; // remove "unused parameter" compiler warnings

  Image *image = make_filled_image(50, 50, &PIXEL_GREEN);
  Line line = {0, 0, 25, 25};
  Line line2 = {25, 30, 0, 5};
  Line line3 = {0, 0, 0, 25};
  Line line4 = {25, 25, 25, 35};
  Line line5 = {0, 0, 25, 0};

  rasterize_line_simple(image, &line, &PIXEL_BLUE);
  rasterize_line_simple(image, &line2, &PIXEL_RED);
  rasterize_line_simple(image, &line3, &PIXEL_WHITE);
  rasterize_line_simple(image, &line4, &PIXEL_BLACK);
  rasterize_line_simple(image, &line5,
                        &(Pixel){255, 255, 0, 255}); // hex for yellow

  write_pam("images/line_simple.pam", image);

  Image *image_2 = make_filled_image(50, 50, &PIXEL_GREEN);
  Circle circle_1 = {25, 25, 10};
  Circle circle_2 = {15, 15, 10};
  Circle circle_3 = {35, 35, 10};

  rasterize_circle_bresenham(image_2, &circle_1, &PIXEL_RED);
  rasterize_circle_bresenham(image_2, &circle_2, &PIXEL_BLUE);
  rasterize_circle_bresenham(image_2, &circle_3, &PIXEL_BLACK);

  write_pam("images/circle.pam", image_2);

  free(image);
  free(image_2);
  return EXIT_SUCCESS;
}
