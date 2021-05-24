#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"
#include "jpeg.h"
#include "polygon.h"
#include "shape.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv; // remove "unused parameter" compiler warnings

  Image *image = make_filled_image(150, 100, &PIXEL_RED);

  write_pam("images/polygons.pam", image);
  write_jpeg("images/test_jpeg.jpg", image, 100);
  Image *read = read_jpeg("images/test_jpeg.jpg");

  printf("Done!\n");

  free(image);
  return EXIT_SUCCESS;
}
