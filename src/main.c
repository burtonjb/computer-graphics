#include <stdlib.h>

#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {

  Pixel base_color = {0, 128, 255, 255};
  Image *image = make_filled_image(100, 100, &base_color);
  Image *small_image = make_filled_image(50, 50, &PIXEL_RED);
  paste_to_image(small_image, image, 0, 0);
  paste_to_image(small_image, image, 75, 75);
  Image *out = copy_from_image(image, 50, 50, 100, 100);

  write_pam("images/pasted_to.pam", image);
  write_pam("images/copied.pam", out);

  free(image);
  free(small_image);
  free(out);

  return EXIT_SUCCESS;
}