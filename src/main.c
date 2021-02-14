#include <math.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  Pixel background_color = {0, 0, 0, 0};
  Pixel foreground_color = {255, 0, 0, 255};

  Image *image = make_filled_image(100, 100, &background_color);
  Image *fg = make_filled_image(10, 20, &foreground_color);
  Image *fg2 = make_filled_image(10, 5, &PIXEL_GREEN);
  paste_to_image(fg, image, 10, 10);
  paste_to_image(fg2, image, 10, 25);

  Image *translated = affine_transform(
      image, &((Matrix3_d){{1, 0, 20}, {0, 1, 20}, {0, 0, 1}}));

  // I need to do some translation to to have the image end up on the screen
  Image *flipped = affine_transform(
      image, &((Matrix3_d){{1, 0, 20}, {0, -1, 50}, {0, 0, 1}}));
  Image *scaled_up =
      affine_transform(image, &((Matrix3_d){{3, 0, 0}, {0, 3, 0}, {0, 0, 1}}));
  Image *scaled_down = affine_transform(
      image, &((Matrix3_d){{0.5, 0, 0}, {0, 0.5, 0}, {0, 0, 1}}));
  const double angle = M_PI / 4;
  Image *rotated =
      affine_transform(image, &((Matrix3_d){{cos(angle), -1 * sin(angle), 0},
                                            {sin(angle), cos(angle), 0},
                                            {0, 0, 1}}));
  Image *sheared =
      affine_transform(image, &((Matrix3_d){{1, 1, 0}, {0, 1, 0}, {0, 0, 1}}));

  write_pam("images/untransformed.pam", image);
  write_pam("images/flipped.pam", flipped);
  write_pam("images/translated.pam", translated);
  write_pam("images/scaled_up.pam", scaled_up);
  write_pam("images/scaled_down.pam", scaled_down);
  write_pam("images/rotated.pam", rotated);
  write_pam("images/sheared.pam", sheared);

  free(image);
  free(fg);
  free(fg2);
  free(flipped);
  free(translated);
  free(scaled_up);
  free(scaled_down);
  free(rotated);
  free(sheared);

  return EXIT_SUCCESS;
}