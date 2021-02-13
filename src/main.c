#include <stdlib.h>

#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  const Matrix3 extract_red_matrix = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  const Matrix3 extract_green_matrix = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  const Matrix3 grey_scale_matrix = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

  Pixel base_color = {128, 128, 255, 255};
  Pixel base_red = {128, 128, 255, 255};
  Pixel base_green = {128, 128, 255, 255};
  Pixel grey_scale_color = {128, 128, 255, 255};

  pixel_div(&grey_scale_color, 3);
  pixel_transform(&grey_scale_color, &grey_scale_matrix);

  pixel_transform(&base_red, &extract_red_matrix);
  pixel_transform(&base_green, &extract_green_matrix);

  Image *image = make_filled_image(100, 100, &base_color);
  Image *grey = make_filled_image(100, 100, &grey_scale_color);
  Image *red_extracted = make_filled_image(100, 100, &base_red);
  Image *green_extracted = make_filled_image(50, 100, &base_green);

  paste_to_image(green_extracted, red_extracted, 50, 0);

  write_pam("images/original_color.pam", image);
  write_pam("images/grey_scale.pam", grey);
  write_pam("images/extracted_red_green.pam", red_extracted);

  free(image);
  free(grey);
  free(red_extracted);

  return EXIT_SUCCESS;
}