#include <math.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"
#include "polygon.h"
#include "shape.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv; // remove "unused parameter" compiler warnings

  Image *image = make_filled_image(50, 50, &PIXEL_GREEN);

  Polygon *triangle =
      create_triangle(&(Point){0, 0}, &(Point){10, 10}, &(Point){0, 10});
  Polygon *square = create_rectangle(&(Point){5, 5}, &(Point){25, 25});

  draw_polygon(image, triangle, &PIXEL_RED);
  draw_polygon(image, square, &PIXEL_BLUE);

  write_pam("images/polygons.pam", image);

  free(triangle);
  free(square);
  free(image);
  return EXIT_SUCCESS;
}
