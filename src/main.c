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

  // Image *image = make_filled_image(50, 50, &PIXEL_GREEN);
  // Line line = {0, 0, 25, 25};
  // Line line2 = {25, 30, 0, 5};
  // Line line3 = {0, 0, 0, 25};
  // Line line4 = {25, 25, 25, 35};
  // Line line5 = {0, 0, 25, 0};

  // rasterize_line_simple(image, &line, &PIXEL_BLUE);
  // rasterize_line_simple(image, &line2, &PIXEL_RED);
  // rasterize_line_simple(image, &line3, &PIXEL_WHITE);
  // rasterize_line_simple(image, &line4, &PIXEL_BLACK);
  // rasterize_line_simple(image, &line5,
  //                       &(Pixel){255, 255, 0, 255}); // hex for yellow

  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {1, 10, 1, 0};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  write_pam("images/line_simple.pam", image);

  free(image);
  return EXIT_SUCCESS;
}