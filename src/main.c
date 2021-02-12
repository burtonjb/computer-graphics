#include <stdlib.h>

#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {

  Pixel base_color = {10, 10, 10, 255};
  Image *image = make_filled_image(100, 100, &base_color);

  pixel_multi(&base_color, 10);
  fill_section(image, 50, 0, &base_color);

  Pixel to_add = {100, 0, 0, 255};
  pixel_add(&base_color, &to_add);
  fill_section(image, 50, 50, &base_color);

  write_pam("images/pixel_operations.pam", image);

  free(image);

  return EXIT_SUCCESS;
}