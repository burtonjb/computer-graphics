#include <math.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  Pixel background_color = {0, 0, 0, 255};

  Image *image = make_filled_image(100, 100, &background_color);
  Image *fg = make_filled_image(50, 50, &PIXEL_RED);
  Image *fg2 = make_filled_image(50, 50, &PIXEL_GREEN);
  Image *fg3 = make_filled_image(50, 50, &PIXEL_BLUE);
  paste_to_image(fg, image, 0, 0);
  paste_to_image(fg2, image, 50, 50);
  paste_to_image(fg3, image, 0, 50);

  // identity transform the image (do nothing)
  Image *identity =
      kernel_transform(image, &((Matrix3_d){{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}));

  // // box blur the image
  Image *box_blur =
      kernel_transform(image, &((Matrix3_d){{1.0 / 9, 1.0 / 9, 1.0 / 9},
                                            {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                            {1.0 / 9, 1.0 / 9, 1.0 / 9}}));

  // gaussian blur the image
  Image *gauss_blur =
      kernel_transform(image, &((Matrix3_d){{1.0 / 16, 2.0 / 16, 1.0 / 16},
                                            {2.0 / 16, 4.0 / 16, 2.0 / 16},
                                            {1.0 / 16, 2.0 / 16, 1.0 / 16}}));

  // Sharpen an image
  Image *sharpen = kernel_transform(
      box_blur, &((Matrix3_d){{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}));

  // edge detection on the image
  // kind of only works on greyscale images
  Image *edge_before = make_filled_image(100, 100, &(Pixel){0, 0, 0, 255});
  for (int i = 0; i < 10; i++) {
    Image *new =
        make_filled_image(100, 10, &(Pixel){i * 25, i * 25, i * 25, 255});
    paste_to_image(new, edge_before, 0, i * 10);
    free(new);
  }
  write_pam("images/before_edge_detection.pam", edge_before);

  Image *edge_after = kernel_transform(
      edge_before, &((Matrix3_d){{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}));
  write_pam("images/after_edge_detection.pam", edge_after);

  write_pam("images/identity.pam", identity);
  write_pam("images/box_blur.pam", box_blur);
  write_pam("images/gauss_blur.pam", gauss_blur);
  write_pam("images/sharpen.pam", sharpen);

  return EXIT_SUCCESS;
}