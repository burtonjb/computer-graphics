#include <stdlib.h>

#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  const Matrix3 extract_red_matrix = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  const Matrix3 grey_scale_matrix = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

  Pixel base_color = {128, 128, 255, 255};

  Image *image = make_filled_image(100, 100, &base_color);
  Image *grey = copy_image(image);
  Image *red_channel = copy_image(image);

  transform_pixels_constant(grey, pixel_div, 3);
  transform_pixels_matrix(grey, &grey_scale_matrix);

  transform_pixels_matrix(red_channel, &extract_red_matrix);
  transform_pixels_other(red_channel, pixel_add, &((Pixel){100, 0, 0}));

  write_pam("images/original_color.pam", image);
  write_pam("images/grey_scale.pam", grey);
  write_pam("images/red.pam", red_channel);

  free(image);
  free(grey);
  free(red_channel);

  return EXIT_SUCCESS;
}